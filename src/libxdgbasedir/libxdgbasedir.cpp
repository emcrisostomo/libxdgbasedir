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

#include "libxdgbasedir.h"
#include "gettext_defs.h"
#include <cstdlib>

static void fail_if_not_absolute_path(const std::string& path);

namespace xdg
{
  static constexpr const char xdg_data_home[]{"XDG_DATA_HOME"};
  static constexpr const char xdg_data_dirs[]{"XDG_DATA_DIRS"};
  static constexpr const char xdg_config_home[]{"XDG_CONFIG_HOME"};
  static constexpr const char xdg_config_dirs[]{"XDG_CONFIG_DIRS"};
  static constexpr const char xdg_cache_home[]{"XDG_CACHE_HOME"};
  static constexpr const char xdg_runtime_dir[]{"XDG_RUNTIME_DIR"};
  static constexpr const char home[]{"HOME"};
  static constexpr const char xdg_data_home_suffix[]{"/.local/share"};

  namespace env
  {
    static std::string get(const std::string& name, const std::string& default_value);
    static std::string get(const std::string& name);
  }
}

void fail_if_not_absolute_path(const std::string& path)
{
  if (path.empty() || path[0] != '/')
  {
    throw std::runtime_error(path + _(": not an absolute path"));
  }
}

std::string xdg::env::get(const std::string& name)
{
  if (auto value = std::getenv(name.c_str()))
    return value;

  throw std::runtime_error(name + _(": cannot be found"));
}

std::string xdg::env::get(const std::string& name, const std::string& default_value)
{
  if (auto value = std::getenv(name.c_str()))
    return value;
  return default_value;
}

std::string xdg::data::home()
{
  auto path = env::get(xdg::xdg_data_home, "");

  if (path.empty())
  {
    path += env::get(xdg::home) + xdg::xdg_data_home_suffix;
  }

  fail_if_not_absolute_path(path);

  return path;
}
