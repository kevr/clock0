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
#include "tui/tui.hpp"
using namespace clock0;

application::application(int argc, char **argv)
    : argc(argc)
    , argv(argv)
    , log("application")
{
    add_program_options();
}

int application::run(void)
{
    // Initialize logging details
    logger::init();

    // Deal with program arguments via command-line and configuration
    if (auto rc = handle_program_args())
        return rc;

    // Print out initial log messages
    log.info("started");
    log.debug("verbose logging enabled");

    // Initialize the root window
    tui::init();

    // Refresh `stdscr`
    tui::refresh();

    // End `stdscr`
    return tui::end();
}

void application::add_program_options(void)
{
    opt.add("verbose,v", "enable verbose logging");
    opt.add("log,l",
            boost::program_options::value<std::string>()->composing(),
            "path to logfile");
}

int application::handle_program_args(void)
{
    // Parse command-line arguments
    auto parse_cmdline = [&] {
        opt.parse_args(argc, argv);
    };
    if (!parse_args(parse_cmdline))
        return OPT_CMDLINE_ERROR;

    // Handle --help if provided
    if (opt.exists("help")) {
        std::cout << opt;
        return SUCCESS;
    }

    // Parse any provided config
    if (opt.exists("config")) {
        auto conf = opt.get<std::string>("config");

        auto parse_config = [&] {
            opt.parse_args(conf);
        };
        if (!parse_args(parse_config))
            return OPT_CONFIG_ERROR;
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

    return SUCCESS;
}
