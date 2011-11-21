#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team	  
# CMakeLists.txt created in 7 2009.
# Mail : biri@univ-mlv.fr					 
#													  
# This file is part of the OpenKraken-cuda.
#
# The OpenKraken-cuda is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-cuda is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.	If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKraken-cuda src/


#Includes
include_directories (${OpenKN-cuda_SOURCE_DIR}/src ${OpenKN-cuda_BINARY_DIR}/src)


#Cpp Files
SET(CPP_FILES CudaException.cpp CudaManager.cpp CudaProgram.cpp)
add_library (OpenKN-cuda SHARED ${CPP_FILES})
add_library (OpenKN-cuda-static STATIC ${CPP_FILES})

#Header Files
SET(HPP_FILES CudaException.hpp CudaManager.hpp CudaProgram.hpp) 

#Install
install (TARGETS OpenKN-cuda DESTINATION lib)
install (TARGETS OpenKN-cuda-static DESTINATION lib)
install (FILES ${HPP_FILES} DESTINATION include/OpenKN/cuda)


#static and dynamic with the same name
SET_TARGET_PROPERTIES(OpenKN-cuda-static PROPERTIES OUTPUT_NAME "OpenKN-cuda")
SET_TARGET_PROPERTIES(OpenKN-cuda PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(OpenKN-cuda-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
