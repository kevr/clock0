/*
 * Program command-line and configuration file options.
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
#ifndef SRC_OPTIONS_HPP
#define SRC_OPTIONS_HPP

#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include <filesystem>
#include <iostream>
#include <memory>

namespace clock0
{

class options
{
private:
    // A store of parsed program_options
    boost::program_options::variables_map m_store;

    // Option descriptions for both the command-line and configuration
    boost::program_options::options_description m_cmdline;
    std::shared_ptr<boost::program_options::options_description> m_config;

    // Argument data
    int m_argc = 0;
    char **m_argv = nullptr;

private:
    std::ostream &usage(std::ostream &) const;

public:
    static options &ref(void);

    void clear(void);

public:
    //! Default constructor
    options(void);

    //! Add a simple option with no value semantic
    void add(const char *, const char *);

    //! Add a value_semantic-based option
    void add(const char *, const boost::program_options::value_semantic *,
             const char *);

    //! Parse command-line arguments
    void parse_args(int, char *[]);

    //! Parse a configuration file
    void parse_args(const std::filesystem::path &);

    //! Check if an option was given
    bool exists(const char *);

    //! Get the value of an option
    template <typename T>
    const T &get(const char *key)
    {
        return m_store.at(key).as<T>();
    }

    friend std::ostream &operator<<(std::ostream &, const options &);
};

std::ostream &operator<<(std::ostream &, const options &);

template <typename F>
bool parse_args(F f)
{
    try {
        f();
    } catch (boost::program_options::error &e) {
        std::cerr << "error: " << e.what() << std::endl;
        return false;
    }

    return true;
}

}; // namespace clock0

#endif /* SRC_OPTIONS_HPP */
