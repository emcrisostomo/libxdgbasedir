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

int main(int /*argc*/, char ** /*argv*/)
{
  std::cout << xdg::data::home() << "\n";
  for (const auto& p : xdg::data::dirs()) std::cout << p << "\n";

  std::cout << xdg::config::home() << "\n";
  for (const auto& p : xdg::config::dirs()) std::cout << p << "\n";

  std::cout << xdg::cache::home() << "\n";

  std::cout << xdg::runtime::dir() << "\n";
}
