#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team
# CMakeLists.txt created in 09 2008.
# Mail : biri@univ-mlv.fr
#
# This file is part of the OpenKraken-image.
#
# The OpenKraken-image is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-image is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#OpenKN-image src/
cmake_minimum_required(VERSION 2.6)

#Includes
include_directories (${OpenKN-image_SOURCE_DIR}/src ${OpenKN-image_BINARY_DIR}/src)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

#Cpp Files
SET(PORTABLE_CPP_FILES ImageException.cpp Image.cpp Image3D.cpp ImageRGB.cpp ImageGS.cpp ImageProcessing.cpp ConvolutionKernel.cpp ImageConvolution.cpp ConvolutionOperator.cpp ConvolutionAverageOperator.cpp ConvolutionAbsoluteSumOperator.cpp ConvolutionMinOperator.cpp ConvolutionMaxOperator.cpp  ConvolutionExtremaSuppressorOperator.cpp ioPPM.cpp ioTGA.cpp ioHDR.cpp ioEPS.cpp Canny.cpp DrawLine.cpp DrawCircle.cpp)

if(jpeg_FOUND)
SET(CPP_FILES ${PORTABLE_CPP_FILES} ioJPG.cpp)
else(jpeg_FOUND)
SET(CPP_FILES ${PORTABLE_CPP_FILES})
endif(jpeg_FOUND)

if(PNG_FOUND)
SET(CPP_FILES ${CPP_FILES} ioPNG.cpp)
else(PNG_FOUND)
SET(CPP_FILES ${CPP_FILES})
endif(PNG_FOUND)

add_library (OpenKN-image SHARED ${CPP_FILES})
add_library (OpenKN-image-static STATIC ${CPP_FILES})

#Header Files
SET(PORTABLE_HPP_FILES ImageException.hpp Image.hpp Image3D.hpp ImageRGB.hpp ImageGS.hpp ImageProcessing.hpp ConvolutionKernel.hpp ImageConvolution.hpp ConvolutionOperator.hpp ConvolutionAverageOperator.hpp ConvolutionAbsoluteSumOperator.hpp ConvolutionMinOperator.hpp ConvolutionMaxOperator.hpp ConvolutionExtremaSuppressorOperator.hpp ioPPM.hpp ioTGA.hpp ioHDR.hpp ioEPS.hpp Canny.hpp DrawLine.hpp DrawCircle.hpp)

if(jpeg_FOUND)
SET(HPP_FILES ${PORTABLE_HPP_FILES} ioJPG.hpp)
else(jpeg_FOUND)
SET(HPP_FILES ${PORTABLE_HPP_FILES})
endif(jpeg_FOUND)

if(PNG_FOUND)
SET(HPP_FILES ${HPP_FILES} ioPNG.hpp)
else(PNG_FOUND)
SET(HPP_FILES ${HPP_FILES})
endif(PNG_FOUND)

TARGET_LINK_LIBRARIES(OpenKN-image ${LIBS})
TARGET_LINK_LIBRARIES(OpenKN-image-static ${LIBS})

#Install
install (TARGETS OpenKN-image DESTINATION lib)
install (TARGETS OpenKN-image-static DESTINATION lib)
install (FILES ${HPP_FILES} DESTINATION include/OpenKN/image)

#static and dynamic with the same name
SET_TARGET_PROPERTIES(OpenKN-image-static PROPERTIES OUTPUT_NAME "OpenKN-image")
SET_TARGET_PROPERTIES(OpenKN-image PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(OpenKN-image-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

