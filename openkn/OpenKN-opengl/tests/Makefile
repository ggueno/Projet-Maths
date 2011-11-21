#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team
# Makefile created in 2 2009.
# Mail : biri@univ-mlv.fr
#
# This file is part of the libIMAC-opengl.
#
# The libIMAC-opengl is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The libIMAC-opengl is distributed in the hope that it will be useful,
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
TESTSUITE=OpenglExceptionTest.hpp FPSCameraTest.hpp


all :
	@echo "Generating OpenKN-opengl test suite"
	@${CXXTESTGEN}  --error-printer -o ${TESTEXEC}.cpp ${TESTSUITE}
	@echo "Compiling OpenKN-opengl test suite"
	@g++ -o ${TESTEXEC}  ${TESTEXEC}.cpp -I../../tools/  -I../src/ -lOpenKN-opengl -lOpenKN-math -lGLEW
	@echo "Running OpenKN-opengl test suite"
	@./${TESTEXEC}

.PHONY: clean

clean :
	@echo "Cleaning OpenKN-opengl test suite"
	@rm -Rf testrunner testrunner.cpp
