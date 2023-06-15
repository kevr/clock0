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
#ifndef SRC_APP_HPP
#define SRC_APP_HPP

#include "logging.hpp"
#include "options.hpp"
#include "tui/tui.hpp"

namespace clock0
{

//! Main application class
class application
{
private:
    // Standard number of program arguments
    int argc = 0;

    // Standard character array of program arguments
    char **argv = nullptr;

    // Root application logger
    logger log;

    // Application TUI
    tui::tui ui;

public:
    /**
     * Construct the application
     *
     * @param argc Number of program arguments provided to main()
     * @param argv Array of c-string arguments provided to main()
     */
    application(int, char **);

    /**
     * Run the application
     *
     * This function encapsulates the application loop. Its return value
     * should be returned to the operating system by main().
     *
     * @returns 0 on success, non-zero on error
     */
    int run(void);

private:
    //! Add command-line options to the options parser
    void add_program_options(void);

    /**
     * Handle program arguments provided via argc/argv
     *
     * After this function is called, newly constructed loggers will
     * make use of configured logging details, like --verbose or --log.
     *
     * @returns 0 on success, non-zero on error
     */
    int handle_program_args(void);
};

}; // namespace clock0

#endif /* SRC_APP_HPP */
