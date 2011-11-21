#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team   
# CMakeLists.txt created in 2 2009.
# Mail : biri@univ-mlv.fr                    
#                                                     
# This file is part of the OpenKraken-vision.
#
# The OpenKraken-vision is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-vision is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKraken-vision

#Required version
cmake_minimum_required (VERSION 2.4.0 FATAL_ERROR)

#Project name
project (OpenKN-vision)

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


# find opencv
find_package(opencv)
if(cv_FOUND)
include_directories(${cv_INCLUDE_DIRS})
set(LIBS ${LIBS} ${cv_LIBRARIES})
endif(cv_FOUND)

# find OpenKN-math
find_package(OpenKN-math)
if(OpenKN-math_FOUND)
include_directories(${OpenKN-math_INCLUDE_DIRS})
set(LIBS ${LIBS} ${OpenKN-math_LIBRARIES})
endif(OpenKN-math_FOUND)

# find OpenKN-image
find_package(OpenKN-image)
if(OpenKN-image_FOUND)
include_directories(${OpenKN-image_INCLUDE_DIRS})
set(LIBS ${LIBS} ${OpenKN-image_LIBRARIES})
endif(OpenKN-image_FOUND)

#Version
set (OpenKN-vision_MAJOR 1)
set (OpenKN-vision_MINOR 2)
set (OpenKN-vision_PATCH 0)
set (OpenKN-vision_VERSION ${OpenKN-vision_MAJOR}.${OpenKN-vision_MINOR}.${OpenKN-vision_PATCH})
message (STATUS "*** Building OpenKN-vision ${OpenKN-vision_VERSION} ***")

#Checks
include (CheckIncludeFileCXX)

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
set (CPACK_SOURCE_GENERATOR "TBZ2")
set (CPACK_SOURCE_PACKAGE_FILE_NAME OpenKraken-vision-${OpenKN-vision_VERSION})
set (CPACK_SOURCE_IGNORE_FILES "~$" ".bz2$" ".gz$")
include (CPack)

#Custom directoty installation
if(DEFINED ENV{OPENKN_DIR})
if(NOT "$ENV{OPENKN_DIR}" STREQUAL "")
SET(CMAKE_INSTALL_PREFIX "$ENV{OPENKN_DIR}")
endif(NOT "$ENV{OPENKN_DIR}" STREQUAL "")
endif(DEFINED ENV{OPENKN_DIR})
message (STATUS "*** Install target directory defined as ${CMAKE_INSTALL_PREFIX} ***") 
