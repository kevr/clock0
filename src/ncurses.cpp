/*
 * Base implementation of ncurses usage. The class defined in This
 * file should be derived for mocked implementations.
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

WINDOW *ncurses::initscr(void)
{
    return ::initscr();
}

int ncurses::cbreak(void)
{
    return ::cbreak();
}

int ncurses::noecho(void)
{
    return ::noecho();
}

int ncurses::keypad(WINDOW *win, bool bf)
{
    return ::keypad(win, bf);
}

int ncurses::raw(void)
{
    return ::raw();
}

int ncurses::refresh(void)
{
    return ::refresh();
}

int ncurses::endwin(void)
{
    return ::endwin();
}
