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
#include "data.hpp"
#include <filesystem>
#include <fstream>
#include <set>
using namespace clock0::project;

//! Ensure a predicate is true by throwing a runtime_error when false
static void ensure(bool predicate, const char *error)
{
    if (!predicate) {
        throw data_error(error);
    }
}

data::data(const std::filesystem::path &p)
{
    load(p);
}

void data::load(const std::filesystem::path &p)
{
    { // Scope out access to the file via ifstream
        std::ifstream ifs(p.c_str(), std::ios::binary);
        if (!ifs) {
            throw data_missing_error("unable to load data file");
        }
        ifs >> *this;
    }

    // Iterate over base keys once and collect them into a set for checks
    std::set<std::string> keys;
    for (const auto &k : getMemberNames()) {
        keys.emplace(k);
    }

    // Enforce some details about the data read
    ensure(keys.find("id") != keys.end(), "missing key 'id'");
    ensure(keys.find("name") != keys.end(), "missing key 'name'");
    ensure(keys.find("lists") != keys.end(), "missing key 'lists'");
    ensure(this->operator[]("lists").isArray(), "'lists' must be an Array");
}

std::tuple<bool, std::filesystem::path> clock0::project::discover_data(void)
{
    auto path = std::filesystem::absolute(".");
    bool found = false;

    do {
        auto data_file = path / DATA_FILE;
        if (std::filesystem::exists(data_file)) {
            found = true;
            break;
        }
        path = path.parent_path();
    } while (path != "/");

    return std::make_tuple(found, path / DATA_FILE);
}

Json::Value clock0::project::create_data(const std::string &name,
                                         unsigned int id)
{
    Json::Value root;
    root["id"] = id;
    root["name"] = name;
    root["lists"] = Json::Value(Json::arrayValue);
    return root;
} // LCOV_EXCL_LINE
