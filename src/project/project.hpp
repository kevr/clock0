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
#ifndef SRC_PROJECT_PROJECT_HPP
#define SRC_PROJECT_PROJECT_HPP

#include <string>

namespace clock0::project
{

class project
{
private:
    //! Internal project identifier
    unsigned long m_id = 0;

    //! Internal project name
    std::string m_name;

public:
    project(void) = default;

    /**
     * Name constructor
     *
     * A constructor to be used when a fresh project is created. The identifier
     * can be filled after construction.
     *
     * @param name Project name
     */
    project(std::string);

    /**
     * Name + identifier constructor
     *
     * A constructor to be used when initializing an existing project, for
     * which we have the identifier to.
     *
     * @param name Project name
     * @param id Project identifier
     */
    project(std::string, unsigned long id);

    //! Project identifier
    unsigned long id(void) const;

    //! Set the project identifier
    project &set_id(unsigned long);

    //! Project name
    const std::string &name(void) const;

    //! Set the project name
    project &set_name(std::string);
};

}; // namespace clock0::project

#endif /* SRC_PROJECT_PROJECT_HPP */
