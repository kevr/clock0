/*
 * A base singleton class.
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
#ifndef SRC_SINGLETON_HPP
#define SRC_SINGLETON_HPP

namespace clock0
{

/**
 * A singleton base for derivative usage.
 *
 * @tparam D Derivative
 */
template <typename D>
class singleton
{
private:
    // Default variable for the D derivative singleton.
    // This requires that D is default constructible.
    inline static D root;

    // Default pointer to D address. This is dereferenced
    // to provide singleton's user with a reference to the
    // stored D.
    inline static D *ptr = &root;

public:
    /** Return internally referenced D */
    static D &ref(void)
    {
        return *ptr;
    }

    /** Swap internally referenced D to another D */
    static D &swap(D &other)
    {
        ptr = &other;
        return ref();
    }

    /** Reset internally referenced D to default */
    static D &reset(void)
    {
        ptr = &root;
        return ref();
    }
};

}; // namespace clock0

#endif /* SRC_SINGLETON_HPP */
