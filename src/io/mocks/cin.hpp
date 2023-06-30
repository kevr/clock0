/*
 * Implementation of a fake version of 'io::cin' used for testing
 * purposes. This "mock" of a cin allows a tester to control the
 * internal data of the stream.
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
#ifndef SRC_IO_MOCKS_CIN_HPP
#define SRC_IO_MOCKS_CIN_HPP

#include "../cin.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace clock0::io
{

/**
 * This class is not really a mock, but is a fake version of io::cin,
 * where we utilize std::istringstream instead of std::cin.
 */
class cin_mock : public cin
{
private: // cin_mock-specific member vars
    std::istringstream m_is;

public: // cin_mock-specific member functions
    std::istringstream &stream(void);

public: // Virtual overrides
    std::istream &operator>>(char &) override;
    std::istream &clear(void) override;
    std::istream &getline(std::string &) override;
};

}; // namespace clock0::io

#endif /* SRC_IO_MOCKS_CIN_HPP */
