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
#include "options.hpp"
#include "config.hpp"
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
using namespace clock0;

std::ostream &options::usage(std::ostream &os) const
{
    boost::program_options::options_description desc;
    desc.add(m_cmdline).add(*m_config);
    const auto &opts = desc.options();

    std::vector<char> simple;
    std::vector<std::string> params;

    for (auto &opt : opts) {
        char short_name = opt->long_name()[0];
        auto param = opt->format_parameter();
        if (param.size()) {
            params.emplace_back("[-" + std::string(1, short_name) + " " +
                                param + "]");
        } else {
            simple.emplace_back(opt->long_name()[0]);
        }
    }

    os << "usage: " << PROG << " [-";
    for (auto short_name : simple) {
        os << short_name;
    }
    os << "]";

    if (params.size()) {
        for (auto &param : params) {
            os << " " << param;
        }
    }
    os << std::endl;

    return os;
}

options &options::ref(void)
{
    static options opt;
    return opt;
}

void options::clear(void)
{
    m_store.clear();
    m_config = std::make_shared<boost::program_options::options_description>();
}

options::options(void)
    : m_config(std::make_shared<boost::program_options::options_description>())
{
    std::filesystem::path conf_path;

    auto *xdg_config_home = std::getenv("XDG_CONFIG_HOME");
    if (xdg_config_home) {
        conf_path = std::filesystem::path(xdg_config_home) / PROG / "config";
    } else {
        auto *home = std::getenv("HOME");
        conf_path = std::filesystem::path(home) / ".config" / PROG / "config";
    }

    m_cmdline.add_options()("help,h", "print a help summary")(
        "config,c",
        boost::program_options::value<std::string>()->default_value(conf_path),
        "specify a configuration file");
}

void options::add(const char *arg, const char *help)
{
    m_config->add_options()(arg, help);
}

void options::add(const char *arg,
                  const boost::program_options::value_semantic *value,
                  const char *help)
{
    m_config->add_options()(arg, value, help);
}

void options::parse_args(int argc, char *argv[])
{
    m_argc = argc;
    m_argv = const_cast<char **>(argv);

    boost::program_options::options_description desc;
    desc.add(m_cmdline).add(*m_config);

    // Parse the command-line with both m_cmdline and m_config options.
    boost::program_options::store(
        boost::program_options::parse_command_line(m_argc, m_argv, desc),
        m_store);
}

void options::parse_args(const std::filesystem::path &path)
{
    boost::program_options::options_description desc;
    desc.add(*m_config);

    // Parse the configuration file provided.
    boost::program_options::store(
        boost::program_options::parse_config_file(path.c_str(), desc),
        m_store);

    // Parse the command-line again; this is done to prioritize
    // CLI arguments over configuration.
    parse_args(m_argc, m_argv);
}

bool options::exists(const char *key)
{
    return m_store.count(key);
}

std::ostream &clock0::operator<<(std::ostream &os, const options &opt)
{
    opt.usage(os);

    os << "\ncommand-line options:\n" << opt.m_cmdline;

    if (opt.m_config->options().size()) {
        os << "\nconfig options:\n" << opt.m_config;
    }

    return os;
}
