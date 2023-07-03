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
#ifndef SRC_PROJECT_DATA_LIST_HPP
#define SRC_PROJECT_DATA_LIST_HPP

#include "json/json.h"

namespace clock0::project::data
{

class list : public Json::Value
{
public:
    /**
     * A single list of tasks.
     *
     * @param title Title of the list
     * @param index Index of the list in the lists array
     */
    list(const std::string &, unsigned int);

    /**
     * Validate a project list object
     *
     * @param json JSON list object
     * @throws clock0::project::data::data_error
     */
    static void validate(const Json::Value &);
};

}; // namespace clock0::project::data

#endif /* SRC_PROJECT_DATA_LIST_HPP */
