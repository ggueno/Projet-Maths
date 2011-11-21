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

#OpenKraken-video src/


#Includes
include_directories (${OpenKN-video_SOURCE_DIR}/src ${OpenKN-video_BINARY_DIR}/src)


#Cpp Files
SET(CPP_FILES VideoException.cpp)
if(avformat_FOUND AND avutil_FOUND AND avcodec_FOUND AND swscale_FOUND)
SET(CPP_FILES ${CPP_FILES} VideoStream.cpp)
endif(avformat_FOUND AND avutil_FOUND AND avcodec_FOUND AND swscale_FOUND)

add_library (OpenKN-video SHARED ${CPP_FILES})
add_library (OpenKN-video-static STATIC ${CPP_FILES})

#Header Files
SET(HPP_FILES VideoException.hpp)
if(avformat_FOUND AND avutil_FOUND AND avcodec_FOUND AND swscale_FOUND)
SET(HPP_FILES ${HPP_FILES} VideoStream.hpp)
endif(avformat_FOUND AND avutil_FOUND AND avcodec_FOUND AND swscale_FOUND)

#Install
install (TARGETS OpenKN-video DESTINATION lib)
install (TARGETS OpenKN-video-static DESTINATION lib)
install (FILES ${HPP_FILES} DESTINATION include/OpenKN/video)


#static and dynamic with the same name
SET_TARGET_PROPERTIES(OpenKN-video-static PROPERTIES OUTPUT_NAME "OpenKN-video")
SET_TARGET_PROPERTIES(OpenKN-video PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(OpenKN-video-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
