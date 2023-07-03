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
#include <filesystem>
#include <fstream>
#include <set>
using namespace clock0::project;

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
