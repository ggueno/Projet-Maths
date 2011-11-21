#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team
# Makefile created in 8 2009.
# Mail : biri@univ-mlv.fr
#
# This file is part of the OpenKraken-video.
#
# The OpenKraken-video is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-video is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.	If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#CxxTest exec
CXXTESTGEN=perl ../../tools/cxxtestgen.pl

#Test exec
TESTEXEC=testrunner


#Test suite
TESTSUITE=VideoExceptionTest.hpp


all :
	@echo "Generating libOpenKN-video test suite"
	@${CXXTESTGEN}	--error-printer -o ${TESTEXEC}.cpp ${TESTSUITE}
	@echo "Compiling libOpenKN-video test suite"
	@g++ -o ${TESTEXEC}	 ${TESTEXEC}.cpp -I../../tools/ -lOpenKN-video -lavcodec -lavformat -lswscale
	@echo "Running libOpenKN-video test suite"
	@./${TESTEXEC}

.PHONY: clean

clean :
	@echo "Cleaning libOpenKN-video test suite"
	@rm -Rf testrunner testrunner.cpp
