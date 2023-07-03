/*
 * Project data lists key structures and utilities.
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
#ifndef SRC_PROJECT_DATA_LISTS_HPP
#define SRC_PROJECT_DATA_LISTS_HPP

#include "json/json.h"

namespace clock0::project::data
{

class lists : public Json::Value
{
public:
    //! Deleted default constructor
    lists(void) = delete;

    /**
     * Validate a project's lists key
     *
     * @param json JSON array
     * @throws clock0::project::data::data_error
     */
    static void validate(const Json::Value &);
};

}; // namespace clock0::project::data

#endif /* SRC_PROJECT_DATA_LISTS_HPP */
