/*
 * Copyright (C) 2017 Enrico M. Crisostomo
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libxdgbasedir/libxdgbasedir.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <random>

void check_data_home();
void check_data_dirs();
void check_config_home();
void check_config_dirs();
void check_cache_home();
void check_runtime_dir();
void check_relative_data_dirs();
void check_relative_runtime_dir();

static const unsigned int NUM = 10;
static std::default_random_engine rng;

int main(int /*argc*/, char ** /*argv*/)
{
  check_data_home();
  check_data_dirs();
  check_config_home();
  check_config_dirs();
  check_cache_home();
  check_runtime_dir();

  check_relative_data_dirs();
  check_relative_runtime_dir();
}

void check_data_home()
{
  std::string tmp("/tmp" + std::to_string(rng()));
  setenv(xdg::XDG_DATA_HOME.c_str(), tmp.c_str(), 1);
  assert(xdg::data::home() == tmp);
}

void check_data_dirs()
{
  std::vector<std::string> data_dirs;
  for (auto i = 0u; i < NUM; ++i) data_dirs.emplace_back("/tmp" + std::to_string(rng()));

  std::string s = std::accumulate(std::begin(data_dirs),
                                  std::end(data_dirs),
                                  std::string(),
                                  [](std::string& previous, std::string& next)
                                  {
                                    return previous.empty() ? next : previous + ":" + next;
                                  });

  setenv(xdg::XDG_DATA_DIRS.c_str(), s.c_str(), 1);
  assert(xdg::data::dirs() == data_dirs);
}

void check_config_home()
{
  std::string tmp("/tmp" + std::to_string(rng()));
  setenv(xdg::XDG_CONFIG_HOME.c_str(), tmp.c_str(), 1);
  assert(xdg::config::home() == tmp);
}

void check_config_dirs()
{
  std::vector<std::string> data_dirs;
  for (auto i = 0u; i < NUM; ++i) data_dirs.emplace_back("/tmp" + std::to_string(rng()));

  std::string s = std::accumulate(std::begin(data_dirs),
                                  std::end(data_dirs),
                                  std::string(),
                                  [](std::string& previous, std::string& next)
                                  {
                                    return previous.empty() ? next : previous + ":" + next;
                                  });

  setenv(xdg::XDG_CONFIG_DIRS.c_str(), s.c_str(), 1);
  assert(xdg::config::dirs() == data_dirs);
}

void check_cache_home()
{
  std::string tmp("/tmp" + std::to_string(rng()));
  setenv(xdg::XDG_CACHE_HOME.c_str(), tmp.c_str(), 1);
  assert(xdg::cache::home() == tmp);
}

void check_runtime_dir()
{
  std::string tmp("/tmp" + std::to_string(rng()));
  setenv(xdg::XDG_RUNTIME_DIR.c_str(), tmp.c_str(), 1);
  assert(xdg::runtime::dir() == tmp);
}

void check_relative_data_dirs()
{
  std::vector<std::string> abs_data_dirs;
  std::vector<std::string> relative_data_dirs;
  for (auto i = 0u; i < NUM; ++i) abs_data_dirs.emplace_back("/tmp" + std::to_string(rng()));
  for (auto i = 0u; i < NUM; ++i) relative_data_dirs.emplace_back("relative/tmp" + std::to_string(rng()));

  std::string s = std::accumulate(std::begin(abs_data_dirs),
                                  std::end(abs_data_dirs),
                                  std::string(),
                                  [](std::string& previous, std::string& next)
                                  {
                                    return previous.empty() ? next : previous + ":" + next;
                                  });

  s = std::accumulate(std::begin(relative_data_dirs),
                      std::end(relative_data_dirs),
                      s,
                      [](std::string& previous, std::string& next)
                      {
                        return previous.empty() ? next : previous + ":" + next;
                      });

  setenv(xdg::XDG_CONFIG_DIRS.c_str(), s.c_str(), 1);
  assert(xdg::config::dirs() == abs_data_dirs);
}

void check_relative_runtime_dir()
{
  std::string tmp("relative/tmp" + std::to_string(rng()));
  setenv(xdg::XDG_RUNTIME_DIR.c_str(), tmp.c_str(), 1);
  assert(xdg::runtime::dir().empty());
}
