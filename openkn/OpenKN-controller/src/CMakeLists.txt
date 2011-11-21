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

#OpenKraken-controller src/

add_subdirectory (webcamstools)


#Includes
include_directories (${OpenKN-controller_SOURCE_DIR}/src ${OpenKN-controller_BINARY_DIR}/src ${OpenKN-controller_SOURCE_DIR}/src/webcamstools/ ${OpenKN-controller_BINARY_DIR}/src/webcamstools/)

#Cpp Files
SET(PORTABLE_CPP_FILES ControllerException.cpp)
SET(WIN_CPP_FILES )

SET(LIN_CPP_FILES webcamstools/utils.cpp webcamstools/color.cpp LIN_V4L2Webcam.cpp)

SET(MAC_CPP_FILES )
if (WIN32)
  SET(CPP_FILES ${PORTABLE_CPP_FILES} ${WIN_CPP_FILES})
else (WIN32)
  if (APPLE)
	SET(CPP_FILES ${PORTABLE_CPP_FILES} ${MAC_CPP_FILES})
  else (APPLE)
	SET(CPP_FILES ${PORTABLE_CPP_FILES} ${LIN_CPP_FILES})
  endif (APPLE)
endif (WIN32)
add_library (OpenKN-controller SHARED ${CPP_FILES})
add_library (OpenKN-controller-static STATIC ${CPP_FILES})

#Header Files
SET(PORTABLE_HPP_FILES CameraController.hpp InputController.hpp ControllerException.hpp)
SET(WIN_HPP_FILES )

SET(LIN_HPP_FILES webcamstools/utils.hpp webcamstools/color.hpp webcamstools/huffman.hpp LIN_V4L2Webcam.hpp)

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

TARGET_LINK_LIBRARIES(OpenKN-controller ${LIBS})
TARGET_LINK_LIBRARIES(OpenKN-controller-static ${LIBS})

#Install
install (TARGETS OpenKN-controller DESTINATION lib)
install (TARGETS OpenKN-controller-static DESTINATION lib)
install (FILES ${HPP_FILES} DESTINATION include/OpenKN/controller)


#static and dynamic with the same name
SET_TARGET_PROPERTIES(OpenKN-controller-static PROPERTIES OUTPUT_NAME "OpenKN-controller")
SET_TARGET_PROPERTIES(OpenKN-controller PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(OpenKN-controller-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

#Build Wiimote
if(boost_thread-mt_FOUND AND wiiuse_FOUND)
SET(CPP_FILES WiimoteManager.cpp Wiimote.cpp WiimoteNunchuk.cpp)
add_library (OpenKN-controller-wiimote SHARED ${CPP_FILES})
add_library (OpenKN-controller-wiimote-static STATIC ${CPP_FILES})

SET(HPP_FILES WiimoteManager.hpp Wiimote.hpp WiimoteNunchuk.hpp)

install (TARGETS OpenKN-controller-wiimote DESTINATION lib)
install (TARGETS OpenKN-controller-wiimote-static DESTINATION lib)
install (FILES ${HPP_FILES} DESTINATION include/OpenKN/controller)

SET_TARGET_PROPERTIES(OpenKN-controller-wiimote-static PROPERTIES OUTPUT_NAME "OpenKN-controller-wiimote")
SET_TARGET_PROPERTIES(OpenKN-controller-wiimote PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(OpenKN-controller-wiimote-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

endif(boost_thread-mt_FOUND AND wiiuse_FOUND)

#Build LIN_DVCam
if(boost_thread-mt_FOUND AND dv_FOUND AND iec61883_FOUND)
SET(CPP_FILES LIN_DVCam.cpp)
add_library (OpenKN-controller-dvcam SHARED ${CPP_FILES})
add_library (OpenKN-controller-dvcam-static STATIC ${CPP_FILES})

SET(HPP_FILES LIN_DVCam.hpp)

install (TARGETS OpenKN-controller-dvcam DESTINATION lib)
install (TARGETS OpenKN-controller-dvcam-static DESTINATION lib)
install (FILES ${HPP_FILES} DESTINATION include/OpenKN/controller)

SET_TARGET_PROPERTIES(OpenKN-controller-dvcam-static PROPERTIES OUTPUT_NAME "OpenKN-controller-dvcam")
SET_TARGET_PROPERTIES(OpenKN-controller-dvcam PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(OpenKN-controller-dvcam-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

endif(boost_thread-mt_FOUND AND dv_FOUND AND iec61883_FOUND)


