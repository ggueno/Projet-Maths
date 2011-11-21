#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team	  
# CMakeLists.txt created in 9 2009.
# Mail : biri@univ-mlv.fr					 
#													  
# This file is part of the OpenKraken-morphotopo.
#
# The OpenKraken-morphotopo is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-morphotopo is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.	If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKraken-morphotopo

#Required version
cmake_minimum_required (VERSION 2.4.0 FATAL_ERROR)

#Check for external librairies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/cmakefindfiles")
set(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES} ".so" ".a")
set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "lib" "")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/usr/lib/" "/usr/local/lib/" $ENV{LIBRARY_PATH})
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/usr/include/" "/usr/local/include/" $ENV{INCLUDE_PATH})

# Check dependencies
find_package(OpenKN-graph)
if(OpenKN-graph_FOUND)
include_directories(${OpenKN-graph_INCLUDE_DIRS})
set(LIBS ${LIBS} ${OpenKN-graph_LIBRARIES})
else()
message(FATAL_ERROR "You must install OpenKN-graph first." )
endif(OpenKN-graph_FOUND)

find_package(OpenKN-image)
if(OpenKN-image_FOUND)
include_directories(${OpenKN-image_INCLUDE_DIRS})
set(LIBS ${LIBS} ${OpenKN-image_LIBRARIES})
else()
message(FATAL_ERROR "You must install OpenKN-image first." )
endif(OpenKN-image_FOUND)

#Project name
project (OpenKN-morphotopo)

#Version
set (OpenKN-morphotopo_MAJOR 0)
set (OpenKN-morphotopo_MINOR 0)
set (OpenKN-morphotopo_PATCH 0)
set (OpenKN-morphotopo_VERSION ${OpenKN-morphotopo_MAJOR}.${OpenKN-morphotopo_MINOR}.${OpenKN-morphotopo_PATCH})
message (STATUS "*** Building OpenKN-morphotopo ${OpenKN-morphotopo_VERSION} ***")

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
set (CPACK_SOURCE_PACKAGE_FILE_NAME libOpenKN-morphotopo-${OpenKN-morphotopo_VERSION})
set (CPACK_SOURCE_IGNORE_FILES "~$" ".bz2$" ".gz$")
include (CPack)
