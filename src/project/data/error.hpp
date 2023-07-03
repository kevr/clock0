/*
 * Project data error structures.
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
#ifndef SRC_PROJECT_DATA_ERROR_HPP
#define SRC_PROJECT_DATA_ERROR_HPP

#include <stdexcept>

namespace clock0::project::data
{

struct data_error : public std::domain_error {
    using std::domain_error::domain_error;
};

struct data_missing_error : public data_error {
    using data_error::data_error;
};

}; // namespace clock0::project::data

#endif /* SRC_PROJECT_DATA_ERROR_HPP */
