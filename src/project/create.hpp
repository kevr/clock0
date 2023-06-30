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
#ifndef SRC_PROJECT_CREATE_HPP
#define SRC_PROJECT_CREATE_HPP

#include "../io/cin.hpp"
#include "project.hpp"

namespace clock0::project
{

class dialogue
{
public:
    //! A utf-8 bullet
    static const char *const BULLET;

private:
    //! Internal reference to an io::cin instance
    io::cin &m_cin;

    //! Internal project object used to keep track of project info
    clock0::project::project m_proj;

public:
    /**
     * Default constructor
     *
     * Construction of a `dialogue` binds the current io::cin::ref()
     * internally for class function. Therefore, io::cin::ref() should
     * be set to the desired io::cin derivative before this class is
     * constructed.
     */
    dialogue(void);

    //! Return a reference to the internal project object
    const clock0::project::project &project(void) const;

    //! Start the dialogue
    bool start(void);

    //! Ask for a project name
    bool get_name(void);

    //! Run the entire dialogue
    int ask(void);
};

}; // namespace clock0::project

#endif /* SRC_PROJECT_CREATE_HPP */
