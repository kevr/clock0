/*
 * Structures and utilities which aid with the 'lists' field of
 * project data.
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
#include "validate.hpp"
#include "data.hpp"
#include <set>
using namespace clock0;

void project::ensure(bool predicate, const char *error)
{
    if (!predicate) {
        throw data_error(error);
    }
}

void project::validate_project(const Json::Value &proj)
{
    // Iterate over base keys once and collect them into a set for checks
    std::set<std::string> keys;
    for (const auto &k : proj.getMemberNames()) {
        keys.emplace(k);
    }

    // Enforce some details about the data read
    ensure(keys.find("id") != keys.end(), "missing key 'id'");
    ensure(keys.find("name") != keys.end(), "missing key 'name'");
    ensure(keys.find("lists") != keys.end(), "missing key 'lists'");
}

void project::validate_lists(const Json::Value &lists)
{
    ensure(lists.isArray(), "lists must be an Array");

    for (const auto &list : lists) {
        validate_list(list);
    }
}

void project::validate_list(const Json::Value &list)
{
    ensure(list.isObject(), "list element must be an Object");

    std::set<std::string> keys;
    for (const auto &key : list.getMemberNames()) {
        keys.emplace(key);
    }

    ensure(keys.find("title") != keys.end(),
           "list object must contain a 'title' string");
    ensure(keys.find("tasks") != keys.end() && list["tasks"].isArray(),
           "list object must contain a 'tasks' Array");
}
