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

static const unsigned int NUM = 10;
static std::default_random_engine rng;

int main(int argc, char **argv)
{
  check_data_home();
  check_data_dirs();

  std::cout << xdg::config::home() << "\n";
  for (const auto& p : xdg::config::dirs()) std::cout << p << "\n";

  std::cout << xdg::cache::home() << "\n";

  std::cout << xdg::runtime::dir() << "\n";
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
  for (auto i = 0; i < NUM; ++i) data_dirs.emplace_back("/tmp" + std::to_string(rng()));

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
