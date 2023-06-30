/*
 * Structures and utilities which aid with project data collection.
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
#ifndef SRC_PROJECT_DATA_HPP
#define SRC_PROJECT_DATA_HPP

#include "json/json.h"
#include <filesystem>
#include <stdexcept>
#include <tuple>

namespace clock0::project
{

const std::string DATA_FILE = ".clock0.json";

class data : public Json::Value
{
public:
    //! Default constructor
    data(void) = default;

    //! Load a data file by construction
    data(const std::filesystem::path &);

    //! Load a data file
    void load(const std::filesystem::path &);
};

//! Discover a data file starting from the current directory up to root.
std::tuple<bool, std::filesystem::path> discover_data(void);

//! An exception object representing an error in data formatting.
struct data_error : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct data_missing_error : public data_error {
    using data_error::data_error;
};

}; // namespace clock0::project

#endif /* SRC_PROJECT_DATA_HPP */
