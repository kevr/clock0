/*
 * Implementation of an ncurses root (stdscr) window
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
#include "root_window.hpp"
#include <stdexcept>
using namespace clock0::tui;

bool root_window::m_created = false;

root_window::root_window(void)
    : basic_window(nullptr)
{
    if (m_created) {
        throw std::runtime_error(
            "root_window can only be default constructed once");
    }
    m_created = true;

    // Initialize `stdscr`
    auto &nc = ncurses::ref();
    m_handle = nc.initscr();
    if (!m_handle) {
        m_created = false;
        throw std::runtime_error("unable to initialize ncurses screen");
    }

    // Configure `stdscr`
    nc.cbreak();
    nc.noecho();
    nc.keypad(m_handle, true);
    nc.raw();
}

root_window::~root_window(void)
{
    ncurses::ref().endwin();
    m_handle = nullptr;
    m_created = false;
}

void root_window::draw(bool post_refresh)
{
    // Call draw on children; the root content
    basic_window::draw(post_refresh);

    // Refresh starting from this root window if we should
    if (post_refresh)
        refresh();
}

int root_window::refresh(void)
{
    // Refresh `stdscr` window
    ncurses::ref().refresh();

    // Refresh children windows
    return basic_window::refresh();
}
