/*
 * Definitions of return codes.
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
#ifndef SRC_SYSTEM_RETURN_CODES_HPP
#define SRC_SYSTEM_RETURN_CODES_HPP

enum clock0_return_codes : int {
    RET_OK = 0,
    RET_CMDLINE_ERROR = 1,
    RET_CONFIG_ERROR = 2,
    RET_DATA_MISSING = 3,
    RET_DATA_ERROR = 4,
};

#endif /* SRC_SYSTEM_RETURN_CODES_HPP */
