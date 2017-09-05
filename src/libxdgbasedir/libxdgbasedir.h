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
  static const std::string XDG_DATA_HOME{"XDG_DATA_HOME"};
  static const std::string XDG_DATA_DIRS{"XDG_DATA_DIRS"};
  static const std::string XDG_CONFIG_HOME{"XDG_CONFIG_HOME"};
  static const std::string XDG_CONFIG_DIRS{"XDG_CONFIG_DIRS"};
  static const std::string XDG_CACHE_HOME{"XDG_CACHE_HOME"};
  static const std::string XDG_RUNTIME_DIR{"XDG_RUNTIME_DIR"};

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
