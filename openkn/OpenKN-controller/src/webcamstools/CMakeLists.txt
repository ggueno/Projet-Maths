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

#OpenKraken-controller src/webcamstools

#Includes
include_directories (${OpenKN-controller_SOURCE_DIR}/src ${OpenKN-controller_BINARY_DIR}/src ${OpenKN-controller_SOURCE_DIR}/src/webcamstools/ ${OpenKN-controller_BINARY_DIR}/src/webcamstools/)

#Header Files
SET(PORTABLE_HPP_FILES )
SET(WIN_HPP_FILES )
  SET(LIN_HPP_FILES color.hpp  huffman.hpp  utils.hpp  uvc_compat.h  uvcvideo.h)
SET(MAC_HPP_FILES )
if (WIN32) 
  SET(HPP_FILES ${PORTABLE_HPP_FILES} ${WIN_HPP_FILES})
else (WIN32)
  if (APPLE)
	SET(HPP_FILES ${PORTABLE_HPP_FILES} ${MAC_HPP_FILES})
  else (APPLE)	
	SET(HPP_FILES ${PORTABLE_HPP_FILES} ${LIN_HPP_FILES})
  endif (APPLE)  
endif (WIN32)


#Install
install (FILES ${HPP_FILES} DESTINATION include/OpenKN/controller/webcamstools)



