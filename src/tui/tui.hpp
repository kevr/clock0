/*
 * Declaration of the application's overarching TUI (text user interface)
 * container.
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
#ifndef SRC_TUI_TUI_HPP
#define SRC_TUI_TUI_HPP

#include "../ncurses.hpp"

namespace clock0
{

/**
 * A text user interface class which serves two purposes:
 * - static: Manage `stdscr`
 * - members: Container for child windows
 */
class tui
{
private:
    static WINDOW *root;

public:
    static WINDOW *root_window(void);
    static WINDOW *init(void);
    static int refresh(void);
    static int end(void);
};

}; // namespace clock0

#endif /* SRC_TUI_TUI_HPP */
