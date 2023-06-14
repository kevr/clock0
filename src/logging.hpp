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
#include <iomanip>
#include <iostream>
#include <sstream>

namespace clock0
{

class logger
{
private:
    static bool debug_enabled;
    bool m_debug = debug_enabled;

public:
    template <typename... Args>
    void info(const char *fmt, Args &&...args)
    {
        print(std::cout, "INFO", fmt, std::forward<Args>(args)...);
    }

    static void set_global_debug(bool);

    void set_debug(bool);

    template <typename... Args>
    void debug(const char *fmt, Args &&...args)
    {
        if (m_debug) {
            print(std::cout, "DBG ", fmt, std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    void error(const char *fmt, Args &&...args)
    {
        print(std::cerr, "ERR ", fmt, std::forward<Args>(args)...);
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
           << "] "
           << fmt::vformat(fmt::string_view(format),
                           fmt::make_format_args(std::forward<Args>(args)...))
           << std::endl;

        // Write the stringstream's content to `os`
        os << ss.str();
    }
};

}; // namespace clock0

#endif /* SRC_LOGGING_HPP */
