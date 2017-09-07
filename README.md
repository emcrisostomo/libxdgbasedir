[![License](https://img.shields.io/badge/license-GPL--3.0-blue.svg?style=flat)](https://github.com/emcrisostomo/libxdgbasedir/blob/master/LICENSE)

README
======

`libxdgbasedir` is a C++ library to retrieve the paths defined by the
[XDG Base Directory Specification][xdgbasedir].  There are other projects
providing similar functionality (for example, [libxdg-basedir][libxdg-basedir]
and [xdg][xdg]) but I decided to create my one for several reasons:

  * I wanted a _simple_ interface and a simple implementation.
  * It does _one thing_: it just retrieves the paths described in the
    specification.
  * It has _no dependencies_.

[xdgbasedir]: https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html
[libxdg-basedir]: https://github.com/devnev/libxdg-basedir
[xdg]: https://github.com/vosst/xdg

Table of Contents
-----------------

  * [Features](#features)
  * [Getting libxdgbasedir](#getting-libxdgbasedir)
  * [Building from Source](#building-from-source)
  * [Installation](#installation)
  * [Localization](#localization)
  * [Usage](#usage)
  * [Contributing](#contributing)
  * [Bug Reports](#bug-reports)

Features
--------

`libxdgbasedir` provides the following functionality:

  * It resolves the paths specified by the _XDG Base Directory Specification_.

Getting libxdgbasedir
---------------------

The sources of `libxdgbasedir` can be obtained from the
[GitHub repository][libxdgbasedir].

[libxdgbasedir]: https://github.com/emcrisostomo/libxdgbasedir

Building from Source
--------------------

Users who wish to build `libxdgbasedir` should get a [release tarball][release].
A release tarball contains everything a user needs to build `libxdgbasedir` on
their system, following the instructions detailed in the
[Installation](#installation) section below and the `INSTALL` file.

A developer who wishes to modify `libxdgbasedir` should get the sources (either
from a source tarball or by cloning the repository) and have the GNU Build
System installed on their machine.  Please read `README.gnu-build-system` to get
further details about how to bootstrap `libxdgbasedir` from sources on your
machine.

[release]: https://github.com/emcrisostomo/libxdgbasedir/releases

Installation
------------

See the `INSTALL` file for detailed information about how to configure and
install `fswatch`.  Since `libxdgbasedir` builds dynamic libraries, in some
platforms you may need to perform additional tasks before you can use them:

  * Make sure the installation directory of dynamic libraries (`$PREFIX/lib`) is
    included in the lookup paths of the dynamic linker of your operating system.
    The default path, `/usr/local/lib`, will work in nearly every operating
    system.
  * Refreshing the links and cache to the dynamic libraries may be required.  In
    GNU/Linux systems you may need to run `ldconfig`:

        $ ldconfig

`libxdgbasedir` is a C++ program and a C++ compiler compliant with the C++11
standard is required to compile it.  Check your OS documentation for information
about how to install the C++ toolchain and the C++ runtime.

No other software packages or dependencies are required to configure and install
`libxdgbasedir` but the aforementioned APIs used by the file system monitors.

Localization
------------

`libxdgbasedir` is localizable and internally uses GNU `gettext` to decouple
localizable string from their translation.  The currently available locales are:

  * English (`en`).
  * Italian (`it`).
  * Spanish (`es`).

To build `libxdgbasedir` with localization support, you need to have `gettext`
installed on your system.  If `configure` cannot find `<libintl.h>` or the
linker cannot find `libintl`, then you may need to manually provide their
location to `configure`, usually using the `CPPFLAGS` and the `LDFLAGS`
variables:

    $ CPPFLAGS="-I/opt/local/include" LDFLAGS="-L/opt/local/lib" ./configure

If `gettext` is not available on your system, `libxdgbasedir` shall build
correctly, but it will lack localization support and the only available locale
will be English.

Usage
-----

The interface of `libxdgbasedir` is described in `libxdgbasedir.h`.  The library
provides a function for each for the variables specified in the _XDG Base
Directory Specification_.  Functions return an instance of `std::string` or
`std::vector<std::string>` depending on whether a path or a list of paths are
returned.  Functions are named after the name of the variable they process:
underscore (`_`) separeted fragments of the variable name are translated into
lowercase namespaces.  For example, the `XDG_DATA_HOME` variable is read by the
`xdg::data::home` function.  The complete list of functions is the following:

    std::string              xdg::data::home();
    std::vector<std::string> xdg::data::dirs();

    std::string              xdg::config::home();
    std::vector<std::string> xdg::config::dirs();

    std::string              xdg::cache::home();

    std::string              xdg::runtime::dir();

Contributing
------------

Everybody is welcome to contribute to `libxdgbasedir`.  Please, see
[`CONTRIBUTING`][contrib] for further information.

[contrib]: CONTRIBUTING.md

Bug Reports
-----------

Bug reports can be sent directly to the authors.

-----

Copyright (c) 2017 Enrico M. Crisostomo

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 3, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>.
