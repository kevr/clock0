/*
 * Tests for the project::project class.
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
#include "project.hpp"
#include "gtest/gtest.h"
using namespace clock0::project;

TEST(project, id)
{
    project p("test", 5);
    EXPECT_EQ(p.id(), 5);
}

TEST(project, set_id)
{
    project p("test");
    EXPECT_EQ(p.id(), 0);
    p.set_id(10);
    EXPECT_EQ(p.id(), 10);
}

TEST(project, name)
{
    project p("test");
    EXPECT_EQ(p.id(), 0);
    EXPECT_EQ(p.name(), "test");
}

TEST(project, set_name)
{
    project p("test");
    EXPECT_EQ(p.name(), "test");
    p.set_name("changed");
    EXPECT_EQ(p.name(), "changed");
}
