/*
 * Stubbed function signatures for the ncurses library.
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
#ifndef SRC_STUBS_NCURSES_HPP
#define SRC_STUBS_NCURSES_HPP

const bool TRUE = true;
const bool FALSE = false;
const int OK = 0;
const int ERR = -1;

typedef wchar_t chtype;
const chtype CLOCK0_LINE_DEFAULT = '*';
const chtype ACS_VLINE = CLOCK0_LINE_DEFAULT;
const chtype ACS_HLINE = CLOCK0_LINE_DEFAULT;
const chtype ACS_ULCORNER = CLOCK0_LINE_DEFAULT;
const chtype ACS_URCORNER = CLOCK0_LINE_DEFAULT;
const chtype ACS_LLCORNER = CLOCK0_LINE_DEFAULT;
const chtype ACS_LRCORNER = CLOCK0_LINE_DEFAULT;

struct WINDOW {
};

// Default values for screen sizes (x = 20, y = 60)
const int TEST_COLS = 20;
const int TEST_LINES = 60;

WINDOW *initscr(void);
int cbreak(void);
int noecho(void);
int keypad(WINDOW *, bool);
int raw(void);
int refresh(void);
int getch(void);
WINDOW *derwin(WINDOW *, int, int, int, int);
int wrefresh(WINDOW *);
void getmaxyx(WINDOW *, int &, int &);
void getbegyx(WINDOW *, int &, int &);
int delwin(WINDOW *);
int endwin(void);

// Styling
int wborder(WINDOW *, chtype, chtype, chtype, chtype, chtype, chtype, chtype,
            chtype);

#endif /* SRC_STUBS_NCURSES_HPP */
