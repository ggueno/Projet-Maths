#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team   
# CMakeLists.txt created in 2 2009.
# Mail : biri@univ-mlv.fr                    
#                                                     
# This file is part of the OpenKraken-opengl.
#
# The OpenKraken-opengl is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-opengl is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKraken-opengl

#Required version
cmake_minimum_required (VERSION 2.4.0 FATAL_ERROR)

#Check for external librairies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")
set(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES} ".so" ".a" ".dll" ".lib")
set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "lib" "")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/usr/lib64/" "/usr/lib/" "/usr/local/lib64" "/usr/local/lib/" "C:/Program Files/OpenKN/math/lib/" "C:/Program Files/OpenKN/geometry/lib/"  $ENV{LIBRARY_PATH})
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/usr/include/" "/usr/local/include/"  "/usr/include/GL/" "/usr/local/include/GL/" "/usr/local/include/OpenKN/math" "/usr/local/include/OpenKN/geometry" "C:/Program Files/OpenKN/math/include" "C:/Program Files/OpenKN/geometry/include/" $ENV{INCLUDE_PATH})


find_package(GLEW)
if(GLEW_FOUND)
include_directories(${GLEW_INCLUDE_DIRS})
set(LIBS ${LIBS} ${GLEW_LIBRARIES})
endif(GLEW_FOUND)

find_package(OpenKN-math)
if(OpenKN-math_FOUND)
include_directories(${OpenKN-math_INCLUDE_DIRS})
set(LIBS ${LIBS} ${OpenKN-math_LIBRARIES})
endif(OpenKN-math_FOUND)

find_package(OpenKN-geometry)
if(OpenKN-geometry_FOUND)
  include_directories(${OpenKN-geometry_INCLUDE_DIRS})
  set(LIBS ${LIBS} ${OpenKN-geometry_LIBRARIES})
endif(OpenKN-geometry_FOUND)


#Project name
project (OpenKN-opengl)

#Version
set (OpenKN-opengl_MAJOR 1)
set (OpenKN-opengl_MINOR 2)
set (OpenKN-opengl_PATCH 0)
set (OpenKN-opengl_VERSION ${OpenKN-opengl_MAJOR}.${OpenKN-opengl_MINOR}.${OpenKN-opengl_PATCH})
message (STATUS "*** Building OpenKN-opengl ${OpenKN-opengl_VERSION} ***")

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
set (CPACK_SOURCE_PACKAGE_FILE_NAME OpenKN-opengl-${OpenKN-opengl_VERSION})
set (CPACK_SOURCE_IGNORE_FILES "~$" ".bz2$" ".gz$")
include (CPack)
