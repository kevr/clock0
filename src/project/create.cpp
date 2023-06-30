/*
 * Create a project.
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
#include "create.hpp"
#include "../io/cin.hpp"
#include "../options.hpp"
#include "../string.hpp"
#include "data.hpp"
#include "fmt/format.h"
#include <cctype>
#include <iostream>
using namespace clock0::project;

const char *const dialogue::BULLET = "\u2022";

dialogue::dialogue(void)
    : m_cin(io::cin::ref())
{
}

const clock0::project::project &dialogue::project(void) const
{
    return m_proj;
}

bool dialogue::start(void)
{
    std::filesystem::path data_file(options::ref().get<std::string>("file"));

    std::cout << fmt::format(
        "Doesn't look like {} exists, want to create it? (Y/n): ",
        data_file.c_str());

    char ch = 0;
    bool good = bool(m_cin >> ch);
    m_cin.clear();
    return good && tolower(ch) == 'y';
}

bool dialogue::get_name(void)
{
    std::cout << fmt::format("\n {} Project name: ", BULLET);

    std::string name;
    bool good = bool(m_cin.getline(name));

    // Otherwise, strip the name that was given and return true
    name = rstrip(name);
    m_proj.set_name(std::move(name));

    return good;
}

int dialogue::ask(void)
{
    if (!start())
        return 1;

    if (!get_name())
        return 2;

    return 0;
}
