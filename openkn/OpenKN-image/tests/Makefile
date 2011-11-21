#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team   
# Makefile created in 09 2008.
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

#CxxTest exec
CXXTESTGEN=perl ../../tools/cxxtestgen.pl

#Test exec
TESTEXEC=testrunner

#Test suite
TESTSUITE=ImageExceptionTest.hpp \
					ImageTest.hpp \
					Image3DTest.hpp \
					ImageRGBTest.hpp \
					ImageGSTest.hpp \
					ConvolutionKernelTest.hpp \
					ConvolutionAverageOperatorTest.hpp \
					ConvolutionMinOperatorTest.hpp \
					ConvolutionMaxOperatorTest.hpp \
					ImageConvolutionTest.hpp \
					ioPPMTest.hpp \
					ioJPGTest.hpp \
					ioTGATest.hpp \
					ioPNGTest.hpp \
					ioHDRTest.hpp

all : 
	@echo "Generating OpenKraken-image test suite"
	@${CXXTESTGEN}  --error-printer -o ${TESTEXEC}.cpp ${TESTSUITE}
	@echo "Compiling OpenKraken-image test suite"
	@g++ -g -o ${TESTEXEC}  ${TESTEXEC}.cpp -I../../tools/ -ljpeg -lpng -lOpenKN-image
	@echo "Running OpenKraken-image test suite"
	@./${TESTEXEC}

.PHONY: clean

clean :
	@echo "Cleaning OpenKraken-image test suite"
	@rm -Rf testrunner testrunner.cpp

