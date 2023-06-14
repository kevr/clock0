/*
 * Unit tests for logging.
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
#include "logging.hpp"
#include "filesystem.hpp"
#include "string.hpp"
#include "gtest/gtest.h"
using namespace clock0;

using testing::internal::CaptureStderr;
using testing::internal::CaptureStdout;
using testing::internal::GetCapturedStderr;
using testing::internal::GetCapturedStdout;

class logger_test : public testing::Test
{
protected:
    logger log;
    std::filesystem::path tmpdir;

public:
    static void SetUpTestSuite(void)
    {
        logger::init();
    }

    void SetUp(void) override
    {
        tmpdir = filesystem::make_tmpdir();
    }

    void TearDown(void) override
    {
        std::filesystem::remove_all(tmpdir);
    }
};

TEST_F(logger_test, info)
{
    CaptureStdout();
    log.info("test {}", "format");

    bool found =
        search(GetCapturedStdout(), R"(.{10} .{8} .+ \[INFO\] test format)");
    EXPECT_TRUE(found);
}

TEST_F(logger_test, timestamp)
{
    CaptureStdout();
    log.info("test {}", "format");

    bool found = search(
        GetCapturedStdout(),
        R"(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2} \w+ \[INFO\] test format)");
    EXPECT_TRUE(found);
}

TEST_F(logger_test, debug)
{
    // Enable debug for this particular logger
    log.set_debug(true);

    CaptureStdout();
    log.debug("test {}", "format");

    bool found =
        search(GetCapturedStdout(), R"(.{10} .{8} .+ \[DBG \] test format)");
    EXPECT_TRUE(found);

    // But not for this one
    logger not_debug_log;

    CaptureStdout();
    not_debug_log.debug("test {}", "format");

    found =
        search(GetCapturedStdout(), R"(.{10} .{8} .+ \[DBG \] test format)");
    EXPECT_FALSE(found);

    // But, if we set global debug, a new logger should debug log
    logger::set_global_debug(true);
    logger default_debug_log;

    CaptureStdout();
    default_debug_log.debug("test {}", "format");

    found =
        search(GetCapturedStdout(), R"(.{10} .{8} .+ \[DBG \] test format)");
    EXPECT_TRUE(found);
}

TEST_F(logger_test, error)
{
    CaptureStderr();
    log.error("test {}", "format");

    bool found =
        search(GetCapturedStderr(), R"(.{10} .{8} .+ \[ERR \] test format)");
    EXPECT_TRUE(found);
}

TEST_F(logger_test, logfile)
{
    std::filesystem::path path(tmpdir / "test.log");
    log.set_logfile(path);
    log.info("test");

    std::ifstream ifs(path, std::ios::in);
    std::string line;
    std::getline(ifs, line);
    ifs.close();
    bool found = search(line, R"(.{10} .{8} .+ \[INFO\] test)");
    EXPECT_TRUE(found);

    log.reset_streams();
    CaptureStdout();
    log.info("test");
    found = search(GetCapturedStdout(), R"(.{10} .{8} .+ \[INFO\] test)");
    EXPECT_TRUE(found);
}

TEST_F(logger_test, global_logfile)
{
    // Set a global logfile
    std::filesystem::path path(tmpdir / "test.log");
    logger::set_global_logfile(path);

    // Construct a new logger which should use the global logfile
    logger log;

    // Log out to the global logfile
    log.info("test");

    // Check the contents of the global logfile after info logging
    std::ifstream ifs(path, std::ios::in);
    std::string line;
    std::getline(ifs, line);
    ifs.close();
    bool found = search(line, R"(.{10} .{8} .+ \[INFO\] test)");
    EXPECT_TRUE(found);

    // Unset the global logfile
    logger::set_global_logfile("");
}

TEST_F(logger_test, logstream_fails)
{
    ASSERT_THROW(log.set_logfile("/does-not-exist/and/should/fail"),
                 std::runtime_error);
}
