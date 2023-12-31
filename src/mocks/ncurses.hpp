/*
 * Mocked implementation of ncurses.
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
#include "../ncurses.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace clock0
{

class ncurses_mock : public ncurses
{
public:
    virtual ~ncurses_mock(void) = default;
    MOCK_METHOD(WINDOW *, initscr, (), (override));
    MOCK_METHOD(int, refresh, (), (override));
    MOCK_METHOD(int, getchar, (), (override));
    MOCK_METHOD(WINDOW *, derwin, (WINDOW *, int, int, int, int), (override));
    MOCK_METHOD(int, wrefresh, (WINDOW *), (override));
    MOCK_METHOD(int, delwin, (WINDOW *), (override));
};

}; // namespace clock0
