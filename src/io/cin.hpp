/*
 * An std::cin-like command-line input class.
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
#ifndef SRC_IO_CIN_HPP
#define SRC_IO_CIN_HPP

#include "../singleton.hpp"
#include <ios>
#include <iostream>
#include <sstream>

namespace clock0::io
{

/**
 * A base std::cin wrapper in singleton form.
 *
 * Accesses to std::cin should go through this class's singleton.
 * Therefore, accesses can be mocked within tests.
 */
class cin : public singleton<cin>
{
public:
    virtual ~cin(void) = default;

    virtual std::istream &operator>>(char &);
    virtual std::istream &clear(void);
    virtual std::istream &getline(std::string &);
};

}; // namespace clock0::io

#endif /* SRC_IO_CIN_HPP */
