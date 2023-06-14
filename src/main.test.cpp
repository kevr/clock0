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
#include "mocks/ncurses.hpp"
#include "string.hpp"
#include "gtest/gtest.h"
using namespace clock0;

using testing::Return;
using testing::internal::CaptureStdout;
using testing::internal::GetCapturedStdout;

class main_test : public testing::Test
{
protected:
    ncurses_mock nc;
    std::filesystem::path tmpdir;

public:
    void SetUp(void) override
    {
        ncurses::swap(nc);

        tmpdir = clock0::filesystem::make_tmpdir();
        auto fakedir = tmpdir / ".home";
        setenv("XDG_CONFIG_HOME", fakedir.c_str(), 0);
    }

    void TearDown(void) override
    {
        std::filesystem::remove_all(tmpdir);
        logger::set_global_logfile("");
        logger::set_global_debug(false);

        options::ref().clear();

        unsetenv("XDG_CONFIG_HOME");

        ncurses::reset();
    }

protected:
    void mock_getchar()
    {
        EXPECT_CALL(nc, getchar()).WillOnce(Return('0')).WillOnce(Return('q'));
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

TEST_F(main_test, runs)
{
    mock_getchar();
    MAKE_SIMPLE_ARGS();
    EXPECT_EQ(_main(argc, argv), SUCCESS);
}

TEST_F(main_test, invalid_option)
{
    MAKE_ARGS(1, "--fakeoption");
    EXPECT_EQ(_main(argc, argv), OPT_CMDLINE_ERROR);
}

TEST_F(main_test, help)
{
    MAKE_ARGS(1, "--help");
    EXPECT_EQ(_main(argc, argv), SUCCESS);
}

TEST_F(main_test, missing_config)
{
    mock_getchar();
    const char *conf_path = "/does-not-exist/clock0.conf";
    MAKE_ARGS(2, "--config", conf_path);
    EXPECT_EQ(_main(argc, argv), 0);
}

TEST_F(main_test, config)
{
    mock_getchar();
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
    ofs << "fake-option = 1\n";
    ofs.close();

    MAKE_ARGS(2, "--config", conf_path.c_str());
    EXPECT_EQ(_main(argc, argv), OPT_CONFIG_ERROR);
}

TEST_F(main_test, log)
{
    mock_getchar();
    auto log_path = tmpdir / "clock0.log";

    MAKE_ARGS(2, "--log", log_path.c_str());
    EXPECT_EQ(_main(argc, argv), SUCCESS);

    std::ifstream ifs(log_path.c_str(), std::ios::in);
    std::string line;
    std::getline(ifs, line);
    ifs.close();
    EXPECT_TRUE(search(line, "started"));
}

TEST_F(main_test, verbose)
{
    mock_getchar();
    CaptureStdout();

    MAKE_ARGS(1, "--verbose");
    EXPECT_EQ(_main(argc, argv), SUCCESS);

    auto output = GetCapturedStdout();
    EXPECT_TRUE(search(output, "verbose logging enabled"));
}
