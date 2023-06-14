/*
 * Unit test for clock0::options
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
#include "options.hpp"
#include "gtest/gtest.h"
using namespace clock0;

TEST(options, xdg_config_home)
{
    setenv("XDG_CONFIG_HOME", "/non-existent/config", 0);
    options opt;
    unsetenv("XDG_CONFIG_HOME");
}
