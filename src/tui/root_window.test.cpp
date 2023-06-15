/*
 * Unit tests ncurses window base.
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
#include "../mocks/ncurses.hpp"
#include "gtest/gtest.h"
using namespace clock0;

using testing::Return;

class root_window_test : public testing::Test
{
protected:
    WINDOW root;
    ncurses_mock nc;

public:
    void SetUp(void) override
    {
        ncurses::swap(nc);
    }

    void TearDown(void) override
    {
        ncurses::reset();
    }

protected:
    void mock_initscr(WINDOW *handle)
    {
        EXPECT_CALL(nc, initscr()).WillRepeatedly(Return(handle));
    }
};

TEST(root_window, handle)
{
    tui::root_window root;
    EXPECT_TRUE(root.handle() != nullptr);
}

TEST(root_window, only_one_root)
{
    tui::root_window root;
    EXPECT_THROW(tui::root_window(), std::runtime_error);
}

TEST_F(root_window_test, draw)
{
    mock_initscr(&root);
    tui::root_window root;

    // Draw without a post_refresh
    root.draw();

    // Draw with a post_refresh
    EXPECT_CALL(nc, refresh()).Times(1).WillOnce(Return(OK));
    root.draw(true);
}

TEST_F(root_window_test, initscr_error)
{
    mock_initscr(nullptr);
    EXPECT_THROW(tui::root_window(), std::runtime_error);
}
