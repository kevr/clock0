/*
 * Structures and utilities which aid with validation of project data.
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
#include "validate.hpp"
#include "error.hpp"
#include "list.hpp"
#include "lists.hpp"
#include "gtest/gtest.h"
using namespace clock0::project::data;

TEST(validate, list_output)
{
    auto l = list("test", 0);
    EXPECT_NO_THROW(list::validate(l));
}

TEST(validate, missing_list_title)
{
    Json::Value list(Json::objectValue);
    Json::Value lists(Json::arrayValue);
    lists.append(list);

    EXPECT_THROW(lists::validate(lists), data_error);
}

TEST(validate, invalid_title)
{
    Json::Value list(Json::objectValue);
    list["title"] = 0;

    Json::Value lists(Json::arrayValue);
    lists.append(list);

    EXPECT_THROW(lists::validate(lists), data_error);
}

TEST(validate, missing_list_tasks)
{
    Json::Value list(Json::objectValue);
    list["title"] = "test";

    Json::Value lists(Json::arrayValue);
    lists.append(list);

    EXPECT_THROW(lists::validate(lists), data_error);
}

TEST(validate, invalid_list_tasks)
{
    Json::Value list(Json::objectValue);
    list["title"] = "test";
    list["tasks"] = 0; // tasks should be an Array

    Json::Value lists(Json::arrayValue);
    lists.append(list);

    EXPECT_THROW(lists::validate(lists), data_error);
}
