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

namespace xdg
{
  static constexpr const char HOME[]{"HOME"};
  static constexpr const char XDG_DATA_HOME_SUFFIX[]{"/.local/share"};
  static constexpr const char XDG_CONFIG_HOME_SUFFIX[]{"/.config"};
  static constexpr const char XDG_CACHE_HOME_SUFFIX[]{"/.cache"};
  static constexpr const char XDG_DATA_DIRS_DEFAULT[]{"/usr/local/share/:/usr/share/"};
  static constexpr const char XDG_CONFIG_DIRS_DEFAULT[]{"/etc/xdg"};

  namespace env
  {
    static std::string get(const std::string& name, const std::string& default_value);
    static std::string get(const std::string& name);
  }

  namespace string_utils
  {
    template<typename Out>
    static void split(const std::string& s, const std::string& delimiter, Out result)
    {

      size_t start = 0;
      size_t end = s.find(delimiter);

      while (end != std::string::npos)
      {
        *(result++) = s.substr(start, end - start);
        start = end + delimiter.length();
        end = s.find(delimiter, start);
      }

      *(result++) = s.substr(start, end);
    }


    static std::vector<std::string> split(const std::string& s, const std::string& delimiter)
    {
      std::vector<std::string> tokens;
      split(s, delimiter, std::back_inserter(tokens));

      return tokens;
    }
  }

  static void fail_if_not_absolute_path(const std::string& path);

  void fail_if_not_absolute_path(const std::string& path)
  {
    if (path.empty() || path[0] != '/')
    {
      throw std::runtime_error(path + _(": not an absolute path"));
    }
  }

  std::string env::get(const std::string& name)
  {
    if (auto value = std::getenv(name.c_str()))
      return value;

    throw std::runtime_error(name + _(": cannot be found"));
  }

  std::string env::get(const std::string& name, const std::string& default_value)
  {
    if (auto value = std::getenv(name.c_str()))
      return value;
    return default_value;
  }

  std::string data::home()
  {
    auto path = env::get(XDG_DATA_HOME, "");

    if (path.empty())
    {
      path = env::get(HOME) + XDG_DATA_HOME_SUFFIX;
    }

    fail_if_not_absolute_path(path);

    return path;
  }

  std::vector<std::string> data::dirs()
  {
    auto paths = env::get(XDG_DATA_DIRS, "");

    if (paths.empty())
    {
      paths = XDG_DATA_DIRS_DEFAULT;
    }

    return string_utils::split(paths, ":");
  }

  std::string config::home()
  {
    auto path = env::get(XDG_CONFIG_HOME, "");

    if (path.empty())
    {
      path = env::get(HOME) + XDG_CONFIG_HOME_SUFFIX;
    }

    fail_if_not_absolute_path(path);

    return path;
  }

  std::vector<std::string> config::dirs()
  {
    auto paths = env::get(XDG_CONFIG_DIRS, "");

    if (paths.empty())
    {
      paths = XDG_CONFIG_DIRS_DEFAULT;
    }

    return string_utils::split(paths, ":");
  }

  std::string cache::home()
  {
    auto path = env::get(XDG_CACHE_HOME, "");

    if (path.empty())
    {
      path = env::get(HOME) + XDG_CACHE_HOME_SUFFIX;
    }

    fail_if_not_absolute_path(path);

    return path;
  }

  std::string runtime::dir()
  {
    return env::get(XDG_RUNTIME_DIR, "");
  }
}