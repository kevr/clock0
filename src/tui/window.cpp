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
#include "window.hpp"
#include <stdexcept>
using namespace clock0::tui;

window::window(basic_window &parent, std::optional<std::string> name)
    : basic_window(nullptr)
{
    log.set_name(name.value_or("window"));
    log.debug("window constructed");

    m_parent = &parent;
    m_parent->add_child(this);
}

window::~window(void)
{
    m_parent->pop_child(this);

    if (m_handle) {
        ncurses::ref().delwin(m_handle);
        m_handle = nullptr;
    }

    log.debug("window destructed");
}

basic_window &window::parent(void) const
{
    return *m_parent;
}

const std::string &window::name(void) const
{
    return log.name();
}

void window::set_name(const std::string &name)
{
    log.set_name(name);
}

void window::create(int x, int y, int pos_x, int pos_y)
{
    auto &nc = ncurses::ref();
    m_handle = nc.derwin(m_parent->handle(), y, x, pos_y, pos_x);
    if (!m_handle) {
        throw std::runtime_error("unable to create a child window");
    }
}

void window::on_draw(std::function<int(window &)> action)
{
    m_draw = action;
}

void window::draw(bool post_refresh)
{
    // Draw window details here
    // For this base child window, this is no-op.
    // Derivatives can call window::draw(post_refresh) to deal with
    // post_refresh and graph traversal.
    if (m_draw(*this) != OK) {
        log.error("failed to draw");
        return;
    }

    // Refresh if post_refresh was provided
    if (post_refresh)
        refresh();

    // Use basic_window::draw to travel down the graph
    basic_window::draw(post_refresh);
}

int window::refresh(void)
{
    log.info("refreshed");

    if (int rc = ncurses::ref().wrefresh(m_handle))
        return rc;

    return basic_window::refresh();
}
