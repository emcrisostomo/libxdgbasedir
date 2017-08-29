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

#ifndef LIBXDGBASEDIR_LIBXDGBASEDIR_H
#define LIBXDGBASEDIR_LIBXDGBASEDIR_H

#include <string>
#include <vector>

namespace xdg
{
  namespace data
  {
    std::string home();
    std::vector<std::string> dirs();
  }

  namespace config
  {
    std::string home();
    std::vector<std::string> dirs();
  }

  namespace cache
  {
    std::string home();
  }

  namespace runtime
  {
    std::string dir();
  }
}


#endif //LIBXDGBASEDIR_LIBXDGBASEDIR_H
