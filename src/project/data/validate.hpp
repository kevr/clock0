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
#ifndef SRC_PROJECT_VALIDATE_HPP
#define SRC_PROJECT_VALIDATE_HPP

#include "json/json.h"

namespace clock0::project::data
{

void ensure(bool, const char *);
void validate_project(const Json::Value &);
void validate_lists(const Json::Value &);
void validate_list(const Json::Value &);

}; // namespace clock0::project::data

#endif /* SRC_PROJECT_LISTS_HPP */
