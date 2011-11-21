#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team	  
# CMakeLists.txt created in 3 2009.
# Mail : biri@univ-mlv.fr					 
#													  
# This file is part of the OpenKraken-util.
#
# The OpenKraken-util is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-util is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.	If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKraken-util src/


#Includes
include_directories (${OpenKN-util_SOURCE_DIR}/src ${OpenKN-util_BINARY_DIR}/src)

#Header Files
SET(HPP_FILES Profiler.hpp StringEnumerator.hpp CyclicBuffer.hpp)

#Install
install (FILES ${HPP_FILES} DESTINATION include/OpenKN/util)


