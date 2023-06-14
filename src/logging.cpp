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
#include "logging.hpp"
#include <filesystem>
#include <stdexcept>
using namespace clock0;

std::filesystem::path logger::logfile;
bool logger::debug_enabled = false;

void logger::set_global_logfile(const std::filesystem::path &path)
{
    logfile = path;
}

void logger::set_global_debug(bool enabled)
{
    debug_enabled = enabled;
}

void logger::init(void)
{
    std::cout.rdbuf()->pubsetbuf(0, 0);
    std::cerr.rdbuf()->pubsetbuf(0, 0);
}

logger::logger(void)
{
    if (!logfile.empty()) {
        set_logfile(logfile);
    }
}

void logger::reset_streams(void)
{
    logstream.close();

    cout = &std::cout;
    cerr = &std::cerr;
}

void logger::set_logfile(const std::filesystem::path &path)
{
    logstream.close();
    logstream.rdbuf()->pubsetbuf(0, 0);
    logstream.open(path, std::ios::out | std::ios::app);

    if (!logstream) {
        throw std::runtime_error("unable to write to " + path.string());
    }

    cout = &logstream;
    cerr = &logstream;
}

void logger::set_debug(bool enabled)
{
    m_debug = enabled;
}
