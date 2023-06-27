/*
 * A standard ncurses child window wrapper.
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
#ifndef SRC_TUI_WINDOW_HPP
#define SRC_TUI_WINDOW_HPP

#include "../logging.hpp"
#include "basic_window.hpp"
#include <optional>

namespace clock0::tui
{

class window : public basic_window
{
private:
    basic_window *m_parent = nullptr;

    // window logger
    logger log { "window" };

public:
    /**
     * Construct a child window
     *
     * @param parent Parent window
     */
    window(basic_window &, std::optional<std::string> name = std::nullopt);

    //! Destruct this window
    virtual ~window(void);

    //! Return the internal parent
    basic_window &parent(void) const;

    //! Get the window logger's name
    const std::string &name(void) const;

    //! Set the window logger's name
    void set_name(const std::string &);

    //! Initialize this window
    void create(int, int, int, int);

    //! Draw this window's buffer
    void draw(bool post_refresh = false) override;

    //! Refresh this window
    int refresh(void) override;
};

}; // namespace clock0::tui

#endif /* SRC_TUI_WINDOW_HPP */
