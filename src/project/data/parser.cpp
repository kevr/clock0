/*
 * Declarations of a project parser parser class.
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
#include "parser.hpp"
#include "error.hpp"
#include "lists.hpp"
#include "project.hpp"
#include "validate.hpp"
#include <fstream>
using namespace clock0::project::data;

parser::parser(const std::filesystem::path &p)
{
    load(p);
}

void parser::load(const std::filesystem::path &p)
{
    { // Scope out access to the file via ifstream
        std::ifstream ifs(p.c_str(), std::ios::binary);
        if (!ifs) {
            throw data_missing_error("unable to load parser file");
        }
        ifs >> *this;
    }

    // Validate project JSON data
    project::validate(*this);
}
