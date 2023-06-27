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

#include "root_window.hpp"
#include "window.hpp"
#include <memory>

namespace clock0::tui
{

/**
 * A text user interface class which serves two purposes:
 * - static: Manage `stdscr`
 * - members: Container for child windows
 */
class tui
{
private:
    std::unique_ptr<root_window> root;
    std::shared_ptr<window> container;

public:
    //! Initialize the root window of the TUI
    void create(void);

    //! Refresh the TUI
    int refresh(void);

    //! Runs the TUI loop
    int loop(void);
};

}; // namespace clock0::tui

#endif /* SRC_TUI_TUI_HPP */
