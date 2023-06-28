/*
 * Unit tests for the tui::tui class
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
#include "../mocks/ncurses.hpp"
#include "gtest/gtest.h"
using namespace clock0;

using testing::_;
using testing::Return;

class tui_test : public testing::Test
{
protected:
    ncurses_mock nc;

    WINDOW root;
    WINDOW *container = new WINDOW;

    tui::tui ui;

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
    void mock_initscr(WINDOW *win)
    {
        EXPECT_CALL(nc, initscr()).WillOnce(Return(win));
    }
};

TEST_F(tui_test, root_refresh_error)
{
    mock_initscr(&root);

    EXPECT_CALL(nc, refresh()).WillOnce(Return(ERR));
    EXPECT_EQ(ui.create(), ERR);
}

TEST_F(tui_test, container_create_error)
{
    mock_initscr(&root);

    EXPECT_CALL(nc, refresh()).WillOnce(Return(OK));
    EXPECT_CALL(nc, derwin(_, _, _, _, _)).WillOnce(Return(nullptr));
    EXPECT_EQ(ui.create(), ERR);
}
