#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team   
# CMakeLists.txt created in 09 2008.
# Mail : biri@univ-mlv.fr                    
#                                                     
# This file is part of the OpenKraken-image.
#
# The OpenKraken-image is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-image is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKN-image

#Required version
cmake_minimum_required (VERSION 2.4.0 FATAL_ERROR)

#Project name
project (OpenKN-image)

#Version
set (OpenKN-image_MAJOR 1)
set (OpenKN-image_MINOR 2)
set (OpenKN-image_PATCH 0)
set (OpenKN-image_VERSION ${OpenKN-image_MAJOR}.${OpenKN-image_MINOR}.${OpenKN-image_PATCH})
message (STATUS "*** Building OpenKN-image ${OpenKN-image_VERSION} ***")

#Checks
include (CheckIncludeFileCXX)

# Check for external dependency
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")
set(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES} ".so" ".a" ".dll" ".lib")
set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "lib" "")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Program Files/" "/usr/lib64/" "/usr/lib/" "/usr/local/lib64" "/usr/local/lib/" $ENV{LIBRARY_PATH})
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Program Files/" "/usr/include/" "/usr/local/include/" "/usr/include/GL/" "/usr/local/include/GL/" "/usr/local/include/OpenKN/" "/usr/X11R6/include/" $ENV{INCLUDE_PATH})

find_package(jpeg)
if(jpeg_FOUND)
include_directories(${jpeg_INCLUDE_DIRS})
set(LIBS ${LIBS} ${jpeg_LIBRARIES})
endif(jpeg_FOUND)

find_package(PNG)
if(PNG_FOUND)
include_directories(${PNG_INCLUDE_DIRS})
set(LIBS ${LIBS} ${PNG_LIBRARIES})
endif(PNG_FOUND)

#Flags
if (WIN32) 
else (WIN32)
set(CMAKE_CXX_FLAGS "-Wall -W -pedantic")
endif (WIN32)
SET(CMAKE_BUILD_TYPE debug)

#Sub directories
add_subdirectory (src)
add_subdirectory (doc)

#Archives generator
set (CPACK_GENERATOR "TGZ")
set (CPACK_PACKAGE_FILE_NAME OpenKN-image-${OpenKN-image_VERSION})
set (CPACK_IGNORE_FILES "~$" ".bz2$" ".gz$")
set (CPACK_SOURCE_GENERATOR "TBZ2")
set (CPACK_SOURCE_PACKAGE_FILE_NAME OpenKN-image-${OpenKN-image_VERSION})
set (CPACK_SOURCE_IGNORE_FILES "~$" ".bz2$" ".gz$")
include (CPack)
