#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team	  
# CMakeLists.txt created in 8 2009.
# Mail : biri@univ-mlv.fr					 
#													  
# This file is part of the OpenKraken-video.
#
# The OpenKraken-video is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-video is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.	If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKraken-video

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
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/usr/include/" "/usr/include/ffmpeg/" "/usr/local/include/" "/usr/local/include/ffmpeg/" "/usr/local/include/libavutil/" "/usr/include/libavutil/" "/usr/local/include/libavcodec/" "/usr/include/libavcodec/" "/usr/local/include/libavformat/" "/usr/include/libavformat/" "/usr/local/include/libswscale/" "/usr/include/libswscale/" "${TMP_INCLUDE_PATH}" )

#Project name
project (OpenKN-video)

#Version
set (OpenKN-video_MAJOR 0)
set (OpenKN-video_MINOR 0)
set (OpenKN-video_PATCH 0)
set (OpenKN-video_VERSION ${OpenKN-video_MAJOR}.${OpenKN-video_MINOR}.${OpenKN-video_PATCH})
message (STATUS "*** Building OpenKN-video ${OpenKN-video_VERSION} ***")

find_package(avutil)
if(avutil_FOUND)
include_directories(${avutil_INCLUDE_DIRS})
set(LIBS ${LIBS} ${avutil_LIBRARIES})
endif(avutil_FOUND)

find_package(avformat)
if(avformat_FOUND)
include_directories(${avformat_INCLUDE_DIRS})
set(LIBS ${LIBS} ${avformat_LIBRARIES})
endif(avformat_FOUND)

find_package(avcodec)
if(avcodec_FOUND)
include_directories(${avcodec_INCLUDE_DIR})
set(LIBS ${LIBS} ${avcodec_LIBRARIES})
endif(avcodec_FOUND)

find_package(swscale)
if(swscale_FOUND)
include_directories(${swscale_INCLUDE_DIR})
set(LIBS ${LIBS} ${swscale_LIBRARIES})
endif(swscale_FOUND)

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
set (CPACK_SOURCE_PACKAGE_FILE_NAME libOpenKN-video-${OpenKN-video_VERSION})
set (CPACK_SOURCE_IGNORE_FILES "~$" ".bz2$" ".gz$")
include (CPack)
