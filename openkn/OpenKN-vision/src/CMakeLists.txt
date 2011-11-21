#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team
# CMakeLists.txt created in 12 2008.
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

#OpenKN-vision src/
cmake_minimum_required(VERSION 2.6)

#Includes
include_directories (${OpenKN-vision_SOURCE_DIR}/src ${OpenKN-vision_BINARY_DIR}/src)

#Cpp Files
SET(CPP_FILES VisionException.cpp Homography.cpp Homography3d.cpp ProjectiveCamera.cpp CameraCalibrationZhang.cpp CameraCalibrationDLT.cpp CameraCalibrationIAC.cpp Triangulation.cpp EpipolarGeometry.cpp TrifocalTensor.cpp ImageRectification.cpp RadialDistortionCorrector.cpp MultiCam3D2DCorrespondences.cpp ExtrinsicMultiCameraAdjustment.cpp RelativeCameraPoseEstimation.cpp Harris.cpp CrossCorrelation.cpp ARtoolkitTools.cpp)
add_library (OpenKN-vision SHARED ${CPP_FILES})
add_library (OpenKN-vision-static STATIC ${CPP_FILES})

#Header Files
SET(HPP_FILES VisionException.hpp Homography.hpp Homography3d.hpp ProjectiveCamera.hpp CameraCalibrationZhang.hpp CameraCalibrationDLT.hpp CameraCalibrationIAC.hpp Triangulation.hpp EpipolarGeometry.hpp TrifocalTensor.hpp ImageRectification.hpp RadialDistortionCorrector.hpp MultiCam3D2DCorrespondences.hpp ExtrinsicMultiCameraAdjustment.hpp RelativeCameraPoseEstimation.hpp Harris.hpp CrossCorrelation.hpp ARtoolkitTools.hpp)

#Install
install (TARGETS OpenKN-vision DESTINATION lib)
install (TARGETS OpenKN-vision-static DESTINATION lib)
install (FILES ${HPP_FILES} DESTINATION include/OpenKN/vision)

#static and dynamic with the same name
SET_TARGET_PROPERTIES(OpenKN-vision-static PROPERTIES OUTPUT_NAME "OpenKN-vision")
SET_TARGET_PROPERTIES(OpenKN-vision PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(OpenKN-vision-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# opencv
if(cv_FOUND)
SET(LIN_CPP_FILES)
SET(PORTABLE_CPP_FILES OpencvCalibrationTools.cpp OpencvTools.cpp)
SET(WIN_CPP_FILES)
SET(MAC_CPP_FILES)
if (WIN32)
	SET(CPP_FILES ${PORTABLE_CPP_FILES} ${WIN_CPP_FILES})
else (WIN32)
	if (APPLE)
	SET(CPP_FILES ${PORTABLE_CPP_FILES} ${MAC_CPP_FILES})
	else (APPLE)
	SET(CPP_FILES ${PORTABLE_CPP_FILES} ${LIN_CPP_FILES})
	endif (APPLE)
endif (WIN32)

add_library (OpenKN-vision-opencv SHARED ${CPP_FILES})
add_library (OpenKN-vision-opencv-static STATIC ${CPP_FILES})

SET(PORTABLE_HPP_FILES OpencvCalibrationTools.hpp OpencvTools.hpp)
SET(WIN_HPP_FILES)
SET(LIN_HPP_FILES)
SET(MAC_HPP_FILES)
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
install (TARGETS OpenKN-vision-opencv DESTINATION lib)
install (TARGETS OpenKN-vision-opencv-static DESTINATION lib)
install (FILES ${HPP_FILES} DESTINATION include/OpenKN/vision)

#static and dynamic with the same name
SET_TARGET_PROPERTIES(OpenKN-vision-opencv-static PROPERTIES OUTPUT_NAME "OpenKN-vision-opencv")
SET_TARGET_PROPERTIES(OpenKN-vision-opencv PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(OpenKN-vision-opencv-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
endif(cv_FOUND)





