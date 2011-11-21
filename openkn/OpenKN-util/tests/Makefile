#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team	  
# Makefile created in 3 2009.
# Mail : biri@univ-mlv.fr					 
#													  
# This file is part of the OpenKraken-util.
#
# The OpenKraken-util is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-util is distributed in the hope that it will be useful,
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
TESTSUITE= StringEnumeratorTest.hpp \
	       ProfilerTest.hpp


all : 
	@echo "Generating OpenKraken-util test suite"
	@${CXXTESTGEN}	--error-printer -o ${TESTEXEC}.cpp ${TESTSUITE}
	@echo "Compiling OpenKraken-util test suite"
	@g++ -o ${TESTEXEC}	 ${TESTEXEC}.cpp -I../../tools/	 -I../src/ 
	@echo "Running OpenKraken-util test suite"
	@./${TESTEXEC}

.PHONY: clean

clean :
	@echo "Cleaning libIMAC-util test suite"
	@rm -Rf testrunner testrunner.cpp
