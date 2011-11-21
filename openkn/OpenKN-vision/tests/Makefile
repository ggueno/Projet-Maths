#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team
# Makefile created in 12 2008.
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

#CxxTest exec
CXXTESTGEN=perl ../../tools/cxxtestgen.pl

#Test exec
TESTEXEC=testrunner


#Test suite
TESTSUITE=VisionExceptionTest.hpp \
	HomographyTest.hpp \
	Homography3dTest.hpp \
	ProjectiveCameraTest.hpp \
	CameraCalibrationTest.hpp \
	TriangulationTest.hpp \
	OpencvCalibrationToolsTest.hpp \
	RelativeCameraPoseEstimationTest.hpp\
	CrossCorrelationTest.hpp


all :
	@echo "Generating OpenKraken-vision test suite"
	@${CXXTESTGEN}  --error-printer -o ${TESTEXEC}.cpp ${TESTSUITE}
	@echo "Compiling OpenKraken-vision test suite"
	@g++ -o ${TESTEXEC} ${TESTEXEC}.cpp -I../../tools/ -I../src/ -L../build/src/ -lOpenKN-vision -lOpenKN-vision-opencv -lOpenKN-math -lOpenKN-image -lcv -ljpeg -lpng
	@echo "Running OpenKraken-vision test suite"
	@./${TESTEXEC}

.PHONY: clean

clean :
	@echo "Cleaning OpenKraken-vision test suite"
	@rm -Rf testrunner testrunner.cpp
