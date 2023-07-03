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
#ifndef SRC_PROJECT_DATA_HPP
#define SRC_PROJECT_DATA_HPP

#include "data/error.hpp"
#include "data/parser.hpp"
#include "data/project.hpp"
#include <filesystem>
#include <string>
#include <tuple>

namespace clock0::project
{

//! Discover a data file starting from the current directory up to root.
std::tuple<bool, std::filesystem::path> discover_data(void);

}; // namespace clock0::project

#endif /* SRC_PROJECT_DATA_HPP */
