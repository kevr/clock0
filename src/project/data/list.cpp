/*
 * Project data list structures and utilities.
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
#include "list.hpp"
#include "validate.hpp"
#include <set>
using namespace clock0::project::data;

list::list(const std::string &title, unsigned int index)
    : Json::Value(Json::objectValue)
{
    // `index` key is needed to perserve user-configured list order
    this->operator[]("index") = index;

    // `name` key is used to identify a list
    this->operator[]("title") = title;

    // `tasks` key is used to house an array of tasks
    this->operator[]("tasks") = Json::Value(Json::arrayValue);
}

void list::validate(const Json::Value &json)
{
    ensure(json.isObject(), "list element must be an Object");

    std::set<std::string> keys;
    for (const auto &key : json.getMemberNames()) {
        keys.emplace(key);
    }

    ensure(keys.find("title") != keys.end(),
           "list object must contain a 'title' string");
    ensure(keys.find("tasks") != keys.end() && json["tasks"].isArray(),
           "list object must contain a 'tasks' Array");
}
