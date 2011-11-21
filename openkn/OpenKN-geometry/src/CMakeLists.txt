#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team
# CMakeLists.txt created in 3 2009.
# Mail : biri@univ-mlv.fr
#
# This file is part of the OpenKraken-geometry.
#
# The OpenKraken-geometry is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-geometry is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.	If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKraken-geometry src/


#Includes
include_directories (${OpenKN-geometry_SOURCE_DIR}/src ${OpenKN-geometry_BINARY_DIR}/src)


#Cpp Files
SET(CPP_FILES GeometryException.cpp Intersection.cpp)
add_library (OpenKN-geometry SHARED ${CPP_FILES})
add_library (OpenKN-geometry-static STATIC ${CPP_FILES})

#Header Files
SET(HPP_FILES GeometryException.hpp Intersection.hpp GeometryTools.hpp)

#Install
install (TARGETS OpenKN-geometry DESTINATION lib)
install (TARGETS OpenKN-geometry-static DESTINATION lib)
install (FILES ${HPP_FILES} DESTINATION include/OpenKN/geometry)


#static and dynamic with the same name
SET_TARGET_PROPERTIES(OpenKN-geometry-static PROPERTIES OUTPUT_NAME "OpenKN-geometry")
SET_TARGET_PROPERTIES(OpenKN-geometry PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(OpenKN-geometry-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
