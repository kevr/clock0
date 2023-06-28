/*
 * Implementation of an ncurses root (stdscr) window
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
#ifndef SRC_TUI_ROOT_WINDOW_HPP
#define SRC_TUI_ROOT_WINDOW_HPP

#include "../logging.hpp"
#include "basic_window.hpp"

namespace clock0::tui
{

class root_window : public basic_window
{
private:
    static bool m_created;

    // root_window log
    logger log { "root_window" };

public:
    /**
     * Handle constructor
     *
     * @param h External root ncurses (stdscr) window.
     */
    root_window(void);

    //! Virtual destructor
    virtual ~root_window(void);

    //! Draw the root_window
    int draw(bool post_refresh = false) override;

    //! Refresh the root_window
    int refresh(void) override;
};

}; // namespace clock0::tui

#endif /* SRC_TUI_ROOT_WINDOW_HPP */
