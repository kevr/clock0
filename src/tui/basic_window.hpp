/*
 * Implementation of an objective ncurses window base.
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
#ifndef SRC_TUI_BASIC_WINDOW_HPP
#define SRC_TUI_BASIC_WINDOW_HPP

#include "../ncurses.hpp"

namespace clock0::tui
{

class basic_window
{
protected:
    WINDOW *m_handle = nullptr;

public:
    /**
     * Handle constructor
     *
     * @param h External handle to stdscr
     */
    basic_window(WINDOW *);

    //! Virtual destructor for polymorphic purposes
    virtual ~basic_window(void) = default;

    //! Returns a pointer to internal ncurses window handle
    WINDOW *handle(void) const;

    //! Pure virtual drawing of this window
    virtual void draw(bool) = 0;

    //! Refresh this basic_window
    virtual int refresh(void) = 0;
};

}; // namespace clock0::tui

#endif /* SRC_TUI_BASIC_WINDOW_HPP */
