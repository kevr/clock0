/*
 * Utilities related to project data.
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
#include "project.hpp"
#include "lists.hpp"
#include "validate.hpp"
#include <set>
using namespace clock0::project::data;

project::project(const std::string &name, unsigned int id)
    : Json::Value(Json::objectValue)
{
    this->operator[]("name") = name;
    this->operator[]("id") = id;
    this->operator[]("lists") = Json::Value(Json::arrayValue);
}

void project::validate(const Json::Value &json)
{
    // Iterate over base keys once and collect them into a set for checks
    std::set<std::string> keys;
    for (const auto &k : json.getMemberNames()) {
        keys.emplace(k);
    }

    // Enforce some details about the data read
    ensure(keys.find("id") != keys.end(), "missing key 'id'");
    ensure(keys.find("name") != keys.end(), "missing key 'name'");
    ensure(keys.find("lists") != keys.end(), "missing key 'lists'");

    lists::validate(json["lists"]);
}
