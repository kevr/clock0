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
#include <filesystem>
#define main _main
#include "main.cpp"
#undef main

#include "filesystem.hpp"
#include "io/mocks/cin.hpp"
#include "mocks/ncurses.hpp"
#include "string.hpp"
#include "system/return_codes.hpp"
#include "gtest/gtest.h"
using namespace clock0;

using testing::_;
using testing::Return;
using testing::internal::CaptureStdout;
using testing::internal::GetCapturedStdout;

class main_test : public testing::Test
{
protected:
    WINDOW root;
    WINDOW *container = new WINDOW;

    ncurses_mock nc;
    std::filesystem::path tmpdir;

    std::string cwd;

public:
    void SetUp(void) override
    {
        ncurses::swap(nc);

        tmpdir = clock0::filesystem::make_tmpdir();
        auto fakedir = tmpdir / ".home";
        setenv("XDG_CONFIG_HOME", fakedir.c_str(), 0);

        this->cwd = std::filesystem::current_path();
        chdir(tmpdir.c_str());
    }

    void TearDown(void) override
    {
        chdir(this->cwd.c_str());

        std::filesystem::remove_all(tmpdir);
        logger::set_global_logfile("");
        logger::set_global_debug(false);

        options::ref().clear();

        unsetenv("XDG_CONFIG_HOME");

        ncurses::reset();
    }

protected:
    void mock_initscr(void)
    {
        EXPECT_CALL(nc, initscr()).WillRepeatedly(Return(&root));
        EXPECT_CALL(nc, derwin(_, _, _, _, _))
            .WillRepeatedly(Return(container));
    }

    void mock_getchar(void)
    {
        EXPECT_CALL(nc, getchar()).WillOnce(Return('0')).WillOnce(Return('q'));
    }

    void mock_tui(void)
    {
        mock_initscr();
        mock_getchar();
    }
};

class cin_main_test : public main_test
{
protected:
    io::cin_mock cin;

public:
    void SetUp(void) override
    {
        main_test::SetUp();
        io::cin::swap(cin);
    }

    void TearDown(void) override
    {
        io::cin::reset();
        main_test::TearDown();
    }
};

template <typename Function>
void write_stdin(const char *data, Function f)
{
    int files[2];
    int status = pipe(files);
    ASSERT_NE(status, -1);

    status = dup2(files[0], STDIN_FILENO);
    ASSERT_NE(status, -1);

    std::size_t size = strlen(data);
    std::size_t bytes = write(files[1], data, size);
    close(files[1]);
    ASSERT_EQ(bytes, size);

    f();
    close(files[0]);
}

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
    mock_tui();
    MAKE_SIMPLE_ARGS();
    write_stdin("Y\ntest\n", [&] {
        EXPECT_EQ(_main(argc, argv), RET_OK);
    });
}

TEST(main, missing_data_file)
{
    MAKE_SIMPLE_ARGS();
    write_stdin("n\n", [&] {
        EXPECT_EQ(_main(argc, argv), RET_DATA_MISSING);
    });
}

TEST_F(main_test, invalid_option)
{
    MAKE_ARGS(1, "--fakeoption");
    EXPECT_EQ(_main(argc, argv), RET_CMDLINE_ERROR);
}

TEST_F(main_test, help)
{
    MAKE_ARGS(1, "--help");
    EXPECT_EQ(_main(argc, argv), RET_OK);
}

TEST_F(main_test, missing_config)
{
    mock_tui();
    const char *conf_path = "/does-not-exist/clock0.conf";
    MAKE_ARGS(2, "--config", conf_path);
    write_stdin("Y\ntest\n", [&] {
        EXPECT_EQ(_main(argc, argv), RET_OK);
    });
}

TEST_F(main_test, config)
{
    mock_tui();
    auto conf_path = tmpdir / "clock0.conf";

    std::ofstream ofs(conf_path.c_str(), std::ios::out);
    ofs << "verbose = 1\n";
    ofs.close();

    MAKE_ARGS(2, "--config", conf_path.c_str());
    write_stdin("Y\ntest\n", [&] {
        EXPECT_EQ(_main(argc, argv), RET_OK);
    });
}

TEST_F(main_test, config_error)
{
    auto conf_path = tmpdir / "clock0.conf";

    std::ofstream ofs(conf_path.c_str(), std::ios::out);
    ofs << "fake-option = 1\n";
    ofs.close();

    MAKE_ARGS(2, "--config", conf_path.c_str());
    EXPECT_EQ(_main(argc, argv), RET_CONFIG_ERROR);
}

TEST_F(main_test, log)
{
    mock_tui();
    auto log_path = tmpdir / "clock0.log";

    MAKE_ARGS(2, "--log", log_path.c_str());
    write_stdin("Y\ntest\n", [&] {
        EXPECT_EQ(_main(argc, argv), RET_OK);
    });

    std::ifstream ifs(log_path.c_str(), std::ios::in);
    std::string line;
    std::getline(ifs, line);
    ifs.close();
    EXPECT_TRUE(search(line, "started"));
}

TEST_F(main_test, verbose)
{
    mock_tui();
    CaptureStdout();

    MAKE_ARGS(1, "--verbose");
    write_stdin("Y\ntest\n", [&] {
        EXPECT_EQ(_main(argc, argv), RET_OK);
    });

    auto output = GetCapturedStdout();
    EXPECT_TRUE(search(output, "verbose logging enabled"));
}

TEST_F(main_test, file_option)
{
    auto path = tmpdir / "custom.json";
    mock_tui();

    MAKE_ARGS(2, "--file", path.c_str());
    write_stdin("Y\ntest\n", [&] {
        EXPECT_EQ(_main(argc, argv), RET_OK);
    });

    Json::Value root;
    {
        std::ifstream ifs(path.c_str(), std::ios::in | std::ios::binary);
        ifs >> root;
    }

    EXPECT_EQ(root["id"].asInt(), 0);
    EXPECT_EQ(root["name"].asString(), "test");
    EXPECT_TRUE(root["lists"].isArray());
}

TEST_F(cin_main_test, cin_fails)
{
    auto &is = cin.stream();
    is.str("Y\n");

    MAKE_SIMPLE_ARGS();
    EXPECT_EQ(_main(argc, argv), RET_DATA_MISSING);
}

TEST_F(cin_main_test, cin_empty)
{
    MAKE_SIMPLE_ARGS();
    EXPECT_EQ(_main(argc, argv), RET_DATA_MISSING);
}

TEST_F(cin_main_test, discover_data_succeeds)
{
    auto data = tmpdir / ".clock0.json";

    {
        std::ofstream ofs(data, std::ios::out);
        ofs << project::create_data("test");
    }

    mock_tui();
    MAKE_SIMPLE_ARGS();
    EXPECT_EQ(_main(argc, argv), RET_OK);
}

TEST_F(cin_main_test, unable_to_create_data_file)
{
    chdir("/");

    auto &is = cin.stream();
    is.str("Y\ntest\n");

    MAKE_SIMPLE_ARGS();
    EXPECT_EQ(_main(argc, argv), RET_DATA_MISSING);
}

TEST_F(main_test, data_error)
{
    auto data_path = tmpdir / project::data::DEFAULT_DATA_FILE;

    {
        Json::Value root;

        std::ofstream ofs(data_path.c_str(), std::ios::out);
        ofs << root;
    }

    MAKE_SIMPLE_ARGS();
    EXPECT_EQ(_main(argc, argv), RET_DATA_ERROR);
}
