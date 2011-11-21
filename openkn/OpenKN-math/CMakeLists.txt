#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team
# CMakeLists.txt created in 09 2008.
# Mail : biri@univ-mlv.fr
#
# This file is part of the OpenKraken-math.
#
# The OpenKraken-math is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-math is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKraken-math

#Required version
cmake_minimum_required (VERSION 2.4.0 FATAL_ERROR)

#Project name
project (OpenKN-math)

#Version
set (OpenKN-math_MAJOR 1)
set (OpenKN-math_MINOR 2)
set (OpenKN-math_PATCH 0)
set (OpenKN-math_VERSION ${OpenKN-math_MAJOR}.${OpenKN-math_MINOR}.${OpenKN-math_PATCH})
message (STATUS "*** Building OpenKN-math ${OpenKN-math_VERSION} ***")

#Checks
include (CheckIncludeFileCXX)

#Sub directories
add_subdirectory (src)
add_subdirectory (doc)


#Archives generator
set (CPACK_GENERATOR "TGZ")
set (CPACK_PACKAGE_FILE_NAME OpenKN-math-${OpenKN-math_VERSION})
set (CPACK_IGNORE_FILES "~$" ".bz2$" ".gz$")
set (CPACK_SOURCE_GENERATOR "TBZ2")
set (CPACK_SOURCE_PACKAGE_FILE_NAME OpenKN-math-${OpenKN-math_VERSION})
set (CPACK_SOURCE_IGNORE_FILES "~$" ".bz2$" ".gz$")
include (CPack)

#Custom directoty installation
if(DEFINED ENV{OPENKN_DIR})
if(NOT "$ENV{OPENKN_DIR}" STREQUAL "")
SET(CMAKE_INSTALL_PREFIX "$ENV{OPENKN_DIR}")
endif(NOT "$ENV{OPENKN_DIR}" STREQUAL "")
endif(DEFINED ENV{OPENKN_DIR})
message (STATUS "*** Install target directory defined as ${CMAKE_INSTALL_PREFIX} ***")
