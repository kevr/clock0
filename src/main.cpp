/*
 * Main entrypoint for the clock0 program, a task management command-line
 * utility.
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
#include "config.hpp"
#include "enums.hpp"
#include "logging.hpp"
#include "options.hpp"
#include "tui/tui.hpp"
#include <boost/program_options/errors.hpp>
#include <iostream>
#include <string>
using namespace clock0;

void add_program_options(options &opt)
{
    opt.add("verbose,v", "enable verbose logging");
    opt.add("log,l",
            boost::program_options::value<std::string>()->composing(),
            "path to logfile");
}

int main(int argc, char *argv[])
{
    options opt;
    add_program_options(opt);

    auto parse_cmdline = [&opt, argc, &argv] {
        opt.parse_args(argc, argv);
    };
    if (!parse_args(parse_cmdline)) {
        return OPT_CMDLINE_ERROR;
    }

    if (opt.exists("help")) {
        std::cout << opt << std::endl;
        return SUCCESS;
    }

    if (opt.exists("config")) {
        auto conf_path = opt.get<std::string>("config");

        auto parse_config = [&opt, &conf_path] {
            opt.parse_args(conf_path);
        };
        if (!parse_args(parse_config)) {
            return OPT_CONFIG_ERROR;
        }
    }

    if (opt.exists("log")) {
        auto log_path = opt.get<std::string>("log");
        logger::set_global_logfile(log_path);
    }

    if (opt.exists("verbose")) {
        logger::set_global_debug(true);
    }

    logger log;
    log.info("started");
    log.debug("verbose logging enabled");

    // Initialize the root window
    tui::init();

    // Refresh `stdscr`
    tui::refresh();

    // End `stdscr`
    return tui::end();
}
