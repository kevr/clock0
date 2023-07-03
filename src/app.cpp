/*
 * Main application code.
 *
 * Copyright (C) 2023 Kevin Morris <kevr@0cost.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "app.hpp"
#include "enums.hpp"
#include "logging.hpp"
#include "project/create.hpp"
#include "project/data.hpp"
#include "system/return_codes.hpp"
#include "tui/tui.hpp"
#include "json/value.h"
#include <cstdlib>
#include <filesystem>
#include <system_error>
using namespace clock0;

application::application(int argc, char **argv)
    : argc(argc)
    , argv(argv)
    , log("app")
{
    add_program_options();
}

int application::run(void)
{
    // Initialize logging details
    logger::init();

    if (auto rc = handle_program_args(); rc || options::ref().exists("help"))
        return rc;

    if (auto rc = gather_project_data())
        return rc;

    // Initialize the TUI
    ui.create();

    // Refresh `stdscr`
    ui.refresh();

    // Run the TUI loop
    return ui.loop();
}

void application::add_program_options(void)
{
    auto &opt = options::ref();

    opt.add("verbose,v", "enable verbose logging");
    opt.add("log,l",
            boost::program_options::value<std::string>()->composing(),
            "path to logfile");
}

int application::handle_program_args(void)
{
    auto &opt = options::ref();

    // Parse command-line arguments
    auto parse_cmdline = [&] {
        opt.parse_args(argc, argv);
    };
    if (!parse_args(parse_cmdline))
        return RET_CMDLINE_ERROR;

    // Handle --help if provided
    if (opt.exists("help")) {
        std::cout << opt << std::endl;
        return RET_OK;
    }

    // Parse any provided config if it can be found
    auto conf = opt.get<std::string>("config");
    bool config_loaded = false;
    if (std::filesystem::exists(conf)) {
        auto parse_config = [&] {
            opt.parse_args(conf);
        };
        if (!parse_args(parse_config))
            return RET_CONFIG_ERROR;
        config_loaded = true;
    }

    // Configure logger static and local logfile
    if (opt.exists("log")) {
        auto logpath = opt.get<std::string>("log");
        logger::set_global_logfile(logpath);
        log.set_logfile(logpath);
    }

    // Configure logger static and local verbosity
    auto verbose = opt.exists("verbose");
    logger::set_global_debug(verbose);
    log.set_debug(verbose);

    // Print out initial log messages with startup details
    log.info("started");
    if (config_loaded)
        log.info("configuration loaded at '{}'", conf);
    log.debug("verbose logging enabled");

    return RET_OK;
}

int application::gather_project_data(void)
{
    project::data::parser data;

    auto [found, path] = create_project_data();
    if (!found) {
        std::cerr << "error: unable to locate data file" << std::endl;
        return RET_DATA_MISSING;
    }

    log.info("found '{}'", path.c_str());
    try {
        data.load(path);
    } catch (project::data::data_error &e) {
        auto rel = std::filesystem::relative(path);
        std::cout << fmt::format("data error ('{}'): ", rel.c_str())
                  << e.what() << std::endl;
        return RET_DATA_ERROR;
    }

    log.info("loaded project '{}'", data["name"].asString());
    return RET_OK;
}

std::ofstream application::open(const char *path)
{
    std::ofstream ofs(path, std::ios::out | std::ios::binary);

    if (!ofs) {
        auto ec = std::make_error_code(std::errc::permission_denied);
        throw std::filesystem::filesystem_error(
            fmt::format("unable to open {} for writing", path), ec);
    }

    return ofs;
}

std::tuple<bool, std::filesystem::path> application::create_project_data(void)
{
    // Attempt to discover project data
    auto [found, path] = project::discover_data();
    if (found)
        return std::make_tuple(found, path);

    // Prompt the user for some information about the new project,
    // since we couldn't find one above.
    project::dialogue dia;
    if (dia.ask())
        return std::make_tuple(false, path);

    // Use `dia` to create a fresh project data file.
    std::filesystem::path new_path(options::ref().get<std::string>("file"));
    new_path = std::filesystem::absolute(new_path);

    auto root = project::create_data(dia.project().name(), dia.project().id());
    {
        std::ofstream ofs;
        try {
            ofs = open(new_path.c_str());
        } catch (std::filesystem::filesystem_error &ec) {
            return std::make_tuple(false, new_path);
        }

        // Write out json to `path`
        ofs << root;
    }

    return std::make_tuple(true, new_path);
}
