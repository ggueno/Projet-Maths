#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team   
# doc/CMakeLists.txt created in 2 2009.
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

find_package (Doxygen)

if(DOXYGEN_FOUND)
  configure_file (${OpenKN-vision_SOURCE_DIR}/doc/Doxyfile-html.cmake ${OpenKN-vision_BINARY_DIR}/doc/Doxyfile-html)
  add_custom_target (html ${DOXYGEN_EXECUTABLE} ${OpenKN-vision_BINARY_DIR}/doc/Doxyfile-html)
endif (DOXYGEN_FOUND)
