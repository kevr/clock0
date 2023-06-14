/*
 * Logging tools.
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
#ifndef SRC_LOGGING_HPP
#define SRC_LOGGING_HPP

#include "fmt/format.h"
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace clock0
{

class logger
{
private:
    static std::filesystem::path logfile; // Path to log file
    static bool debug_enabled;

private:
    std::ostream *cout = &std::cout; // Stdout stream
    std::ostream *cerr = &std::cerr; // Stderr stream

    std::ofstream logstream; // Optional log stream

    bool m_debug = debug_enabled;

    std::string m_name;

public:
    //! Set a global logfile; new loggers will open a stream to it
    static void set_global_logfile(const std::filesystem::path &);

    //! Set a global debug flag; new loggers will match their debug flag
    static void set_global_debug(bool);

    static void init(void);

public:
    //! Construct a new logger
    logger(void);

    //! Construct a new logger with a particular name
    logger(const std::string &);

    //! Reset stdout/stderr streams
    void reset_streams(void);

    //! Set the logger-specific stream to a log file
    void set_logfile(const std::filesystem::path &);

    //! Set the logger-specific debug flag
    void set_debug(bool);

    //! Set the logger's name
    void set_name(const std::string &);

    template <typename... Args>
    void info(const char *fmt, Args &&...args)
    {
        print(*cout, "INFO", fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void debug(const char *fmt, Args &&...args)
    {
        if (m_debug) {
            print(*cout, "DBG ", fmt, std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    void error(const char *fmt, Args &&...args)
    {
        print(*cerr, "ERR ", fmt, std::forward<Args>(args)...);
    }

private:
    template <typename... Args>
    void print(std::ostream &os, const char *label, const char *format,
               Args &&...args)
    {
        // Build a local time point
        auto now = std::chrono::system_clock::now();
        auto time_point = std::chrono::system_clock::to_time_t(now);
        auto *localtime = std::localtime(&time_point);

        // Fill a stringstream with an fmt-formatted message
        std::stringstream ss;
        ss << std::put_time(localtime, "%Y-%m-%d %H:%M:%S %Z") << " [" << label
           << "] ";

        if (m_name.size()) {
            ss << '<' << m_name << "> ";
        }

        ss << fmt::vformat(fmt::string_view(format),
                           fmt::make_format_args(std::forward<Args>(args)...))
           << std::endl;

        // Write the stringstream's content to `os`
        os << ss.str();
    }
};

}; // namespace clock0

#endif /* SRC_LOGGING_HPP */
