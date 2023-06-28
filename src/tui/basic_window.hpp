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

#include "../logging.hpp"
#include "../ncurses.hpp"
#include <list>
#include <tuple>

namespace clock0::tui
{

class basic_window
{
protected:
    // Ncurses window handle
    WINDOW *m_handle = nullptr;

    // Children
    std::list<basic_window *> m_children;

    // basic_window logger
    logger log { "basic_window" };

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

    //! Add a child window to the list of children
    void add_child(basic_window *);

    //! Remove a child window from the list of children
    void pop_child(basic_window *);

    //! Return a copy of the list of children
    std::list<basic_window *> children(void) const;

    //! Pure virtual drawing of this window
    virtual int draw(bool post_refresh = false);

    //! Refresh this basic_window
    virtual int refresh(void);

    //! Returns an (x, y) tuple of the size of this window
    std::tuple<int, int> size(void) const;

    //! Returns an (x, y) tuple of the position of this window
    std::tuple<int, int> position(void) const;
};

template <typename T>
std::list<T *> list_to(const std::list<basic_window *> &children)
{
    std::list<T *> converted;
    for (auto *w : children) {
        converted.push_back(reinterpret_cast<T *>(w));
    }
    return converted;
}

}; // namespace clock0::tui

#endif /* SRC_TUI_BASIC_WINDOW_HPP */
