/*
 * Standard header to be included to gain access to ncurses.
 * This header switches between the real ncurses and our
 * stub located in stubs/ncurses.{h,c}pp.
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
#ifndef SRC_NCURSES_HPP
#define SRC_NCURSES_HPP

#ifndef BUILD_TESTS
#include <ncurses.h>
#else
#include "stubs/ncurses.hpp"
#endif

#include "singleton.hpp"

namespace clock0
{

class ncurses : public singleton<ncurses>
{
public:
    virtual ~ncurses(void) = default;

public:
    virtual WINDOW *initscr(void);
    virtual int cbreak(void);
    virtual int noecho(void);
    virtual int keypad(WINDOW *, bool);
    virtual int raw(void);
    virtual int refresh(void);
    virtual int endwin(void);
};

}; // namespace clock0

#endif /* SRC_NCURSES_HPP */
