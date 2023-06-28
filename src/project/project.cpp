/*
 * Declaration of a class implementing a "project".
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
#include "project.hpp"
using namespace clock0::project;

project::project(std::string name)
    : m_name(std::move(name))
{
}

project::project(std::string name, unsigned long id)
    : m_id(id)
    , m_name(std::move(name))

{
}

unsigned long project::id(void) const
{
    return m_id;
}

project &project::set_id(unsigned long id)
{
    m_id = id;
    return *this;
}

const std::string &project::name(void) const
{
    return m_name;
}

project &project::set_name(std::string name)
{
    m_name = std::move(name);
    return *this;
}
