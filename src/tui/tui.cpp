/*
 * Definition of the application's overarching TUI (text user interface)
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
#include "tui.hpp"
#include "../enums.hpp"
#include <thread>
#include <utility>
using namespace clock0::tui;

int tui::refresh(void)
{
    return root->refresh();
}

void tui::create(void)
{
    root.reset();

    // Create and refresh the root window
    root = std::make_unique<root_window>();
    root->refresh();

    // Spawn a container in the root window
    container = std::make_shared<window>(*root, "container");
    auto [x, y] = root->size();
    container->create(x, y, 0, 0);

    container->on_draw([](window &w) -> int {
        return ncurses::ref().wborder(w.handle(), 0, 0, 0, 0, 0, 0, 0, 0);
    });

    // Draw from the root
    root->draw(true);
}

int tui::loop(void)
{
    auto &nc = ncurses::ref();

    // Main loop
    for (int ch = nc.getchar(); ch != 'q'; ch = nc.getchar()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return SUCCESS;
}
