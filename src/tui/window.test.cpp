/*
 * Unit tests for the tui::window class
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
#include "window.hpp"
#include "../mocks/ncurses.hpp"
#include "../string.hpp"
#include "root_window.hpp"
#include "gtest/gtest.h"
using namespace clock0;
using namespace clock0::tui;

using testing::_;
using testing::Return;

class window_test : public testing::Test
{
protected:
    ncurses_mock nc;

    WINDOW root_handle;
    WINDOW *container = new WINDOW;
    std::unique_ptr<root_window> root;

public:
    void SetUp(void) override
    {
        ncurses::swap(nc);
        logger::set_global_debug(true); // Toggle debug on

        EXPECT_CALL(nc, initscr()).WillRepeatedly(Return(&root_handle));
        root = std::make_unique<root_window>();
    }

    void TearDown(void) override
    {
        logger::set_global_debug(false); // Toggle debug off
        ncurses::reset();
    }
};

TEST_F(window_test, runs)
{
    window child(*root);
    EXPECT_EQ(&child.parent(), root.get());
}

TEST_F(window_test, name)
{
    // Default construction
    window child(*root);
    EXPECT_EQ(child.name(), "window");

    // Custom name construction
    window child2(*root, "custom");
    EXPECT_EQ(child2.name(), "custom");

    // Change an existing window name
    child.set_name("changed");
    EXPECT_EQ(child.name(), "changed");
}

TEST_F(window_test, refreshes_from_root)
{
    EXPECT_CALL(nc, refresh()).WillRepeatedly(Return(OK));
    EXPECT_CALL(nc, derwin(_, _, _, _, _)).WillOnce(Return(container));

    window child(*root);

    auto [x, y] = root->size();
    child.create(x, y, 0, 0);

    root->refresh();
}

TEST_F(window_test, children)
{
    window child(*root);

    auto children = root->children();
    EXPECT_EQ(children.size(), 1);
}

TEST_F(window_test, default_draw)
{
    testing::internal::CaptureStdout();

    window child(*root);
    EXPECT_NO_THROW(child.draw());

    auto output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(search(output, "no-op"));
}

TEST_F(window_test, draw_error)
{
    testing::internal::CaptureStderr();

    window child(*root);
    child.on_draw([](window &) -> int {
        return ERR;
    });
    child.draw();

    auto output = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(search(output, "[ERR ]"));
}

TEST_F(window_test, derwin_error)
{
    EXPECT_CALL(nc, derwin(_, _, _, _, _)).WillOnce(Return(nullptr));

    window child(*root);
    EXPECT_THROW(child.create(0, 0, 0, 0), std::runtime_error);
}

TEST_F(window_test, refresh_error)
{
    EXPECT_CALL(nc, derwin(_, _, _, _, _)).WillOnce(Return(container));

    window child(*root);
    EXPECT_NO_THROW(child.create(0, 0, 0, 0));

    EXPECT_CALL(nc, wrefresh(_)).WillOnce(Return(ERR));
    EXPECT_EQ(child.refresh(), ERR);
}
