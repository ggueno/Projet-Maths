
#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team   
# Makefile created in 10 2008.
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

#CxxTest exec
CXXTESTGEN=perl ../../tools/cxxtestgen.pl

#Test exec
TESTEXEC=testrunner


#Test suite
TESTSUITE= LIN_V4L2WebcamTest.hpp\
		   ControllerExceptionTest.hpp

#Test suite DVCam
TESTSUITEDVCAM= LIN_DVCamTest.hpp

#Test suite Wiimote
TESTSUITEWIIMOTE= WiimoteTest.hpp


all : 
	@echo "Generating OpenKraken-controller test suite"
	@${CXXTESTGEN} --error-printer -o ${TESTEXEC}.cpp ${TESTSUITE}
	@echo "Compiling OpenKraken-controller test suite"
	@g++ -g -o ${TESTEXEC}  ${TESTEXEC}.cpp -I../../tools/  -I../src/ -I../src/webcamstools/ -L../build/src/ -lOpenKN-controller
	@echo "Running OpenKraken-controller test suite"
	@./${TESTEXEC}

dvcam :
	@echo "Generating OpenKraken-controller test suite for DVCam"
	@${CXXTESTGEN} --error-printer -o ${TESTEXEC}.cpp ${TESTSUITEDVCAM}
	@echo "Compiling OpenKraken-controller test suite for DVCam"
	@g++ -g -o ${TESTEXEC}  ${TESTEXEC}.cpp -I../../tools/  -I../src/ -L../build/src/ -lOpenKN-controller -lOpenKN-controller-dvcam -lboost_thread
	@echo "Running OpenKraken-controller test suite"
	@./${TESTEXEC}

wiimote :
	@echo "Generating OpenKraken-controller test suite for Wiimote"
	@${CXXTESTGEN} --error-printer -o ${TESTEXEC}.cpp ${TESTSUITEWIIMOTE}
	@echo "Compiling OpenKraken-controller test suite for Wiimote"
	@g++ -g -o ${TESTEXEC}  ${TESTEXEC}.cpp -I../../tools/  -I../src/ -L../build/src/ -lOpenKN-controller -lOpenKN-controller-wiimote -lwiiuse -lboost_thread
	@echo "Running OpenKraken-controller test suite"
	@./${TESTEXEC}

.PHONY: clean

clean :
	@echo "Cleaning OpenKraken-controller test suite"
	@rm -Rf testrunner testrunner.cpp 
