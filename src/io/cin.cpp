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
#include "cin.hpp"
#include "../string.hpp"
#include <iostream>
using namespace clock0::io;

std::istream &cin::operator>>(char &ch)
{
    std::cin >> ch;
    return std::cin;
}

std::istream &cin::clear(void)
{
    std::cin.clear();
    std::cin.ignore();
    return std::cin;
}

std::istream &cin::getline(std::string &line)
{
    return std::getline(std::cin, line);
}
