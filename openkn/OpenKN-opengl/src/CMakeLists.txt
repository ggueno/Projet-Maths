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

#OpenKraken-opengl src/


#Includes
include_directories (${OpenKN-opengl_SOURCE_DIR}/src ${OpenKN-opengl_BINARY_DIR}/src)

#Cpp Files
SET(CPP_FILES OpenglException.cpp)
if(GLEW_FOUND)
SET(CPP_FILES ${CPP_FILES} GLSLShader.cpp GPUArrayBuffer.cpp FBO.cpp FPSCamera.cpp MatrixManager.cpp)
endif(GLEW_FOUND)
add_library (OpenKN-opengl SHARED ${CPP_FILES})
add_library (OpenKN-opengl-static STATIC ${CPP_FILES})

#Header Files
SET(HPP_FILES  OpenglException.hpp)
if(GLEW_FOUND)
SET(HPP_FILES ${HPP_FILES} GLSLShader.hpp GPUArrayBuffer.hpp FBO.hpp FPSCamera.hpp MatrixManager.hpp)
endif(GLEW_FOUND)

#Install
install (TARGETS OpenKN-opengl DESTINATION lib)
install (TARGETS OpenKN-opengl-static DESTINATION lib)
install (FILES ${HPP_FILES} DESTINATION include/OpenKN/opengl)


#static and dynamic with the same name
SET_TARGET_PROPERTIES(OpenKN-opengl-static PROPERTIES OUTPUT_NAME "OpenKN-opengl")
SET_TARGET_PROPERTIES(OpenKN-opengl PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(OpenKN-opengl-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
