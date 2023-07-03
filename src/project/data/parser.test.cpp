/*
 * Unit tests for project data utilities.
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
#include "parser.hpp"
#include "../../filesystem.hpp"
#include "error.hpp"
#include "gtest/gtest.h"
#include <fstream>
using namespace clock0;
using namespace project::data;

class data_test : public testing::Test
{
protected:
    std::filesystem::path tmpdir;
    std::filesystem::path data_path;

public:
    void SetUp(void) override
    {
        tmpdir = filesystem::make_tmpdir();
        data_path = tmpdir / DEFAULT_DATA_FILE;
    }

    void TearDown(void) override
    {
        std::filesystem::remove_all(tmpdir);
    }
};

TEST_F(data_test, data_error)
{
    {
        Json::Value root;

        std::ofstream ofs(data_path, std::ios::out);
        ofs << root;
    }

    EXPECT_THROW((parser(data_path)), data_error);
}

TEST_F(data_test, name_missing)
{
    {
        Json::Value root;
        root["id"] = 0;

        std::ofstream ofs(data_path, std::ios::out);
        ofs << root;
    }

    EXPECT_THROW((parser(data_path)), data_error);
}

TEST_F(data_test, id_missing)
{
    {
        Json::Value root;
        root["name"] = "test";

        std::ofstream ofs(data_path, std::ios::out);
        ofs << root;
    }

    EXPECT_THROW((parser(data_path)), data_error);
}

TEST_F(data_test, lists_missing)
{
    {
        Json::Value root;
        root["id"] = 0;
        root["name"] = "test";

        std::ofstream ofs(data_path, std::ios::out);
        ofs << root;
    }

    EXPECT_THROW((parser(data_path)), data_error);
}

TEST_F(data_test, lists_is_not_array)
{
    {
        Json::Value root;
        root["id"] = 0;
        root["name"] = "test";
        root["lists"] = 0;

        std::ofstream ofs(data_path, std::ios::out);
        ofs << root;
    }

    EXPECT_THROW((parser(data_path)), data_error);
}

TEST_F(data_test, data_missing)
{
    EXPECT_THROW((parser(data_path)), data_missing_error);
}
