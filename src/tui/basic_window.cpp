/*
 * Implementation of an objective ncurses window base.
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
#include "basic_window.hpp"
using namespace clock0::tui;

basic_window::basic_window(WINDOW *h)
    : m_handle(h)
{
}

WINDOW *basic_window::handle(void) const
{
    return m_handle;
}

std::tuple<int, int> basic_window::size(void) const
{
    int x, y;
    auto &nc = ncurses::ref();
    nc.get_maxyx(m_handle, y, x);
    return std::make_tuple(x, y);
}

std::tuple<int, int> basic_window::position(void) const
{
    int x, y;
    auto &nc = ncurses::ref();
    nc.get_begyx(m_handle, y, x);
    return std::make_tuple(x, y);
}
