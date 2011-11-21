#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team   
# CMakeLists.txt created in 10 2008.
# Mail : biri@univ-mlv.fr                    
#                                                     
# This file is part of the OpenKraken-controller.
#
# The OpenKraken-controller is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-controller is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKN-controller

#Required version
cmake_minimum_required (VERSION 2.4.0 FATAL_ERROR)

#Project name
project (OpenKN-controller)

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

if(UNIX)
find_package(boost_thread-mt)
if(boost_thread_FOUND)
include_directories(${boost_thread-mt_INCLUDE_DIRS})
set(LIBS ${LIBS} ${boost_thread-mt_LIBRARIES})
endif(boost_thread_FOUND)
endif(UNIX)

find_package(wiiuse)
if(wiiuse_FOUND)
include_directories(${wiiuse_INCLUDE_DIRS})
set(LIBS ${LIBS} ${wiiuse_LIBRARIES})
endif(wiiuse_FOUND)

if(UNIX)
find_package(dv)
find_package(iec61883)
if(dv_FOUND AND iec61883_FOUND AND boost_thread_FOUND)
include_directories(${dv_INCLUDE_DIRS} ${iec61883_INCLUDE_DIRS} ${boost_thread_INCLUDE_DIRS})
set(LIBS ${LIBS} ${dv_LIBRARIES} ${iec61883_LIBRARIES} ${boost_thread_LIBRARIES})
endif(dv_FOUND AND iec61883_FOUND AND boost_thread_FOUND)
endif(UNIX)

#Project name
project (OpenKN-controller)

#Version
set (OpenKN-controller_MAJOR 1)
set (OpenKN-controller_MINOR 2)
set (OpenKN-controller_PATCH 0)
set (OpenKN-controller_VERSION ${OpenKN-controller_MAJOR}.${OpenKN-controller_MINOR}.${OpenKN-controller_PATCH})
message (STATUS "*** Building OpenKN-controller ${OpenKN-controller_VERSION} ***")

#Checks
include (CheckIncludeFileCXX)

#Flags
set(CMAKE_CXX_FLAGS "-Wall -W")
SET(CMAKE_BUILD_TYPE debug)

#Sub directories
add_subdirectory (src)
add_subdirectory (doc)


#Archives generator
set (CPACK_GENERATOR "TGZ")
set (CPACK_PACKAGE_FILE_NAME OpenKN-controller-${OpenKN-controller_VERSION})
set (CPACK_IGNORE_FILES "~$" ".bz2$" ".gz$")
set (CPACK_SOURCE_GENERATOR "TBZ2")
set (CPACK_SOURCE_PACKAGE_FILE_NAME OpenKN-controller-${OpenKN-controller_VERSION})
set (CPACK_SOURCE_IGNORE_FILES "~$" ".bz2$" ".gz$")
include (CPack)

if(DEFINED ENV{OPENKN_DIR})
if(NOT "$ENV{OPENKN_DIR}" STREQUAL "")
SET(CMAKE_INSTALL_PREFIX "$ENV{OPENKN_DIR}")
endif(NOT "$ENV{OPENKN_DIR}" STREQUAL "")
endif(DEFINED ENV{OPENKN_DIR})
message (STATUS "*** Install target directory defined as ${CMAKE_INSTALL_PREFIX} ***")
