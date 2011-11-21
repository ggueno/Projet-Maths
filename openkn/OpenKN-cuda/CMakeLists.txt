#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team
# CMakeLists.txt created in 7 2009.
# Mail : biri@univ-mlv.fr
#
# This file is part of the OpenKraken-cuda.
#
# The OpenKraken-cuda is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-cuda is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.	If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKraken-cuda

#Required version
cmake_minimum_required (VERSION 2.4.0 FATAL_ERROR)

#Check for external librairies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/cmakefindfiles")
set(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES} ".so" ".a" ".lib" ".dll")
set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "lib" "")

STRING(REGEX REPLACE ":" ";" TMP_INCLUDE_PATH "$ENV{LIBRARY_PATH}")
STRING(REGEX REPLACE ":" ";" TMP_LD_LIBRARY_PATH "$ENV{LD_LIBRARY_PATH}")
STRING(REGEX REPLACE ":" ";" TMP_OPENKN_FIND_LIBRARY_PATH "$ENV{OPENKN_FIND_LIBRARY_PATH}")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/usr/lib64/" "/usr/lib/" "/usr/local/lib64" "/usr/local/lib/" "C:/windows/system32" "C:/windows/system64" "${TMP_LIBRARY_PATH}" "${TMP_LD_LIBRARY_PATH}" "${TMP_OPENKN_FIND_LIBRARY_PATH}")

STRING(REGEX REPLACE ":" ";"  TMP_INCLUDE_PATH  "$ENV{INCLUDE_PATH}")
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/usr/include/" "/usr/local/include/" "${TMP_INCLUDE_PATH}" )

find_package(boost_thread-mt)
if(boost_thread-mt_FOUND)
include_directories(${boost_thread-mt_INCLUDE_DIRS})
set(LIBS ${LIBS} ${boost_thread-mt_LIBRARIES})
else()
message(FATAL_ERROR "You must install boost_thread-mt first." )
endif(boost_thread-mt_FOUND)

#Project name
project (OpenKN-cuda)

#Version
set (OpenKN-cuda_MAJOR 1)
set (OpenKN-cuda_MINOR 2)
set (OpenKN-cuda_PATCH 0)
set (OpenKN-cuda_VERSION ${OpenKN-cuda_MAJOR}.${OpenKN-cuda_MINOR}.${OpenKN-cuda_PATCH})
message (STATUS "*** Building OpenKN-cuda ${OpenKN-cuda_VERSION} ***")

#Checks
include (CheckIncludeFileCXX)

#Flags
set(CMAKE_CXX_FLAGS "-Wall -W -pedantic")
SET(CMAKE_BUILD_TYPE debug)

#Sub directories
add_subdirectory (src)
add_subdirectory (doc)


#Archives generator
set (CPACK_GENERATOR "TGZ")
set (CPACK_SOURCE_GENERATOR "TBZ2")
set (CPACK_SOURCE_PACKAGE_FILE_NAME libOpenKN-cuda-${OpenKN-cuda_VERSION})
set (CPACK_SOURCE_IGNORE_FILES "~$" ".bz2$" ".gz$")
include (CPack)
