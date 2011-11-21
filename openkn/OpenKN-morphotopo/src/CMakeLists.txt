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

#OpenKraken-morphotopo src/


#Includes
include_directories (${OpenKN-morphotopo_SOURCE_DIR}/src ${OpenKN-morphotopo_BINARY_DIR}/src)


#Cpp Files
SET(CPP_FILES LambdaTree.cpp Maxtree.cpp MorphotopoException.cpp)
add_library (OpenKN-morphotopo SHARED ${CPP_FILES})
add_library (OpenKN-morphotopo-static STATIC ${CPP_FILES})

#Header Files
SET(HPP_FILES LambdaTree.hpp Maxtree.hpp MorphotopoException.hpp)

#Install
install (TARGETS OpenKN-morphotopo DESTINATION lib)
install (TARGETS OpenKN-morphotopo-static DESTINATION lib)
install (FILES ${HPP_FILES} DESTINATION include/OpenKN/morphotopo)


#static and dynamic with the same name
SET_TARGET_PROPERTIES(OpenKN-morphotopo-static PROPERTIES OUTPUT_NAME "OpenKN-morphotopo")
SET_TARGET_PROPERTIES(OpenKN-morphotopo PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(OpenKN-morphotopo-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
