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
#ifndef SRC_PROJECT_DATA_PROJECT_HPP
#define SRC_PROJECT_DATA_PROJECT_HPP

#include "json/json.h"

namespace clock0::project::data
{

class project : public Json::Value
{
public:
    /**
     * A project.
     *
     * @param name Project name
     * @param id Project id (defaulted to 0)
     */
    project(const std::string &, unsigned int = 0);

    /**
     * Validate a project's JSON data
     *
     * @param json JSON list data
     * @throws data_error
     */
    static void validate(const Json::Value &);
};

}; // namespace clock0::project::data

#endif /* SRC_PROJECT_DATA_PROJECT_HPP */
