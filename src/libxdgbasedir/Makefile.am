#
# Copyright (c) 2017 Enrico M. Crisostomo
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; either version 3, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# this program.  If not, see <http://www.gnu.org/licenses/>.
#
LIBXDGBASEDIR_API_VERSION = @AM_LIBXDGBASEDIR_API_VERSION@

# Prepare gettext-related symbols used by programs
AM_CPPFLAGS = -DLOCALEDIR=\"$(localedir)\"

lib_LTLIBRARIES = libxdgbasedir.la

libxdgbasedir_la_SOURCES  = library.h library.cpp
libxdgbasedir_la_SOURCES += gettext.h
libxdgbasedir_la_SOURCES += gettext_defs.h

libxdgbasedir_la_LDFLAGS  = -version-info $(LIBXDGBASEDIR_API_VERSION)
libxdgbasedir_la_LDFLAGS += @LTLIBINTL@

if OS_CYGWIN
  libxdgbasedir_la_LDFLAGS += -no-undefined
endif

# Define separate include directories for C and C++ headers.
libxdgbasedir_cppdir = $(pkgincludedir)/c++

libxdgbasedir_cpp_HEADERS  = library.h
