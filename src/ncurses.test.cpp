/*
 * Test base implementation of ncurses usage. The class defined in This
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
#include "gtest/gtest.h"
using namespace clock0;

TEST(ncurses, refresh)
{
    EXPECT_EQ(ncurses::ref().refresh(), OK);
}

TEST(ncurses, getchar)
{
    EXPECT_EQ(ncurses::ref().getchar(), 0);
}

TEST(ncurses, derwin)
{
    auto &nc = ncurses::ref();

    // Initialize a fake WINDOW to be used as a parent
    WINDOW root;

    // Exercise derwin
    auto win = nc.derwin(&root, 0, 0, 0, 0);
    EXPECT_NE(win, nullptr);

    // Exercise wrefresh
    EXPECT_EQ(nc.wrefresh(win), OK);

    // Exercise delwin
    EXPECT_EQ(nc.delwin(win), OK);
}

TEST(ncurses, wborder)
{
    WINDOW root;
    EXPECT_EQ(ncurses::ref().wborder(&root,
                                     ACS_VLINE,
                                     ACS_VLINE,
                                     ACS_HLINE,
                                     ACS_HLINE,
                                     ACS_ULCORNER,
                                     ACS_URCORNER,
                                     ACS_LLCORNER,
                                     ACS_LRCORNER),
              OK);
}
