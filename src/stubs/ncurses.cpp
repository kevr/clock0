/*
 * Stubbed function definitions for the ncurses library.
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

static WINDOW root;

WINDOW *initscr(void)
{
    return &root;
}

int cbreak(void)
{
    return OK;
}

int noecho(void)
{
    return OK;
}

int keypad(WINDOW *, bool)
{
    return OK;
}

int raw(void)
{
    return OK;
}

int refresh(void)
{
    return OK;
}

int getch(void)
{
    return 0;
}

WINDOW *derwin(WINDOW *, int, int, int, int)
{
    return new WINDOW;
}

int wrefresh(WINDOW *)
{
    return OK;
}

void getmaxyx(WINDOW *, int &y, int &x)
{
    x = TEST_COLS;
    y = TEST_LINES;
}

void getbegyx(WINDOW *, int &y, int &x)
{
    x = y = 0;
}

int delwin(WINDOW *win)
{
    delete win;
    return OK;
}

int endwin(void)
{
    return OK;
}

int wborder(WINDOW *, chtype, chtype, chtype, chtype, chtype, chtype, chtype,
            chtype)
{
    return OK;
}
