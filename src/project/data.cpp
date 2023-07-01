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
#include "../options.hpp"
#include "validate.hpp"
#include <filesystem>
#include <fstream>
#include <set>
using namespace clock0::project;

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

    // Validate project fields
    validate_project(*this);

    // Validate lists format, which recursively validates lists keys
    Json::Value lists(this->operator[]("lists"));
    validate_lists(lists);
}

std::tuple<bool, std::filesystem::path> clock0::project::discover_data(void)
{
    auto path = std::filesystem::absolute(".");
    bool found = false;

    const auto base = options::ref().get<std::string>("file");
    do {
        auto data_file = path / base;
        if (std::filesystem::exists(data_file)) {
            found = true;
            break;
        }
        path = path.parent_path();
    } while (path != "/");

    return std::make_tuple(found, path / base);
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
