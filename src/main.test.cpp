/*
 * Main entrypoint unit tests for the clock0 executable.
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
#define main _main
#include "main.cpp"
#undef main

#include "filesystem.hpp"
#include "gtest/gtest.h"
using namespace clock0;

class main_test : public testing::Test
{
protected:
    std::filesystem::path tmpdir;

public:
    void SetUp(void) override
    {
        tmpdir = clock0::filesystem::make_tmpdir();
    }

    void TearDown(void) override
    {
        std::filesystem::remove_all(tmpdir);
    }
};

#define MAKE_SIMPLE_ARGS()                                                    \
    int argc = 1;                                                             \
    const char *c_argv[] = { "clock0" };                                      \
    char **argv = const_cast<char **>(c_argv);

#define MAKE_ARGS(n, ...)                                                     \
    int argc = n + 1;                                                         \
    const char *c_argv[] = { "clock0", __VA_ARGS__ };                         \
    char **argv = const_cast<char **>(c_argv);

TEST(main, runs)
{
    MAKE_SIMPLE_ARGS();
    EXPECT_EQ(_main(argc, argv), SUCCESS);
}

TEST(main, invalid_option)
{
    MAKE_ARGS(1, "--fakeoption");
    EXPECT_EQ(_main(argc, argv), OPT_CMDLINE_ERROR);
}

TEST(main, help)
{
    MAKE_ARGS(1, "--help");
    EXPECT_EQ(_main(argc, argv), SUCCESS);
}

TEST_F(main_test, missing_config)
{
    const char *conf_path = "/does-not-exist/clock0.conf";
    MAKE_ARGS(2, "--config", conf_path);
    EXPECT_EQ(_main(argc, argv), OPT_CONFIG_ERROR);
}

TEST_F(main_test, config)
{
    auto conf_path = tmpdir / "clock0.conf";

    std::ofstream ofs(conf_path.c_str(), std::ios::out);
    ofs << "verbose = 1\n";
    ofs.close();

    MAKE_ARGS(2, "--config", conf_path.c_str());
    EXPECT_EQ(_main(argc, argv), SUCCESS);
}

TEST_F(main_test, config_error)
{
    auto conf_path = tmpdir / "clock0.conf";

    std::ofstream ofs(conf_path.c_str(), std::ios::out);
    ofs << "verbose = 1\n";
    ofs.close();

    MAKE_ARGS(2, "--config", conf_path.c_str());
    EXPECT_EQ(_main(argc, argv), SUCCESS);
}
