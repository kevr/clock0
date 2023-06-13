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
#include "ncurses.hpp"
using namespace clock0;

int main()
{
    // Take a reference to the ncurses singleton.
    auto &nc = ncurses::ref();

    // Initialize `stdscr`
    auto *root = nc.initscr();

    // Initialize various things about `stdscr`
    nc.cbreak();
    nc.noecho();
    nc.keypad(root, true);
    nc.raw();

    // Refresh `stdscr`
    nc.refresh();

    // End `stdscr`
    return nc.endwin();
}
