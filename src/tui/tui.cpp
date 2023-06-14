/*
 * Definition of the application's overarching TUI (text user interface)
 * container.
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
#include "tui.hpp"
#include <thread>
using namespace clock0;

WINDOW *tui::root = nullptr;

WINDOW *tui::root_window(void)
{
    return root;
}

WINDOW *tui::init(void)
{
    auto &nc = ncurses::ref();
    root = nc.initscr();

    nc.cbreak();
    nc.noecho();
    nc.keypad(root, true);
    nc.raw();

    return root_window();
}

int tui::refresh(void)
{
    return ncurses::ref().refresh();
}

int tui::end(void)
{
    auto rc = ncurses::ref().endwin();
    root = nullptr;
    return rc;
}

void tui::loop(void)
{
    auto &nc = ncurses::ref();
    for (int ch = nc.getchar(); ch != 'q'; ch = nc.getchar()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
