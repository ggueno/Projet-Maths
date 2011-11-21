#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team
# Makefile created in 09 2008.
# Mail : biri@univ-mlv.fr
#
# This file is part of the OpenKraken-math.
#
# The OpenKraken-math is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken-math is distributed in the hope that it will be useful,
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
TESTSUITE=SVDTest.hpp\
	  MathExceptionTest.hpp \
	  MatrixTest.hpp \
	  Matrix4x4Test.hpp \
	  Matrix3x3Test.hpp \
	  VectorTest.hpp \
	  MathToolsTest.hpp \
	  DeterminantTest.hpp \
	  RankTest.hpp \
	  RQDecompositionTest.hpp \
	  CholeskyDecompositionTest.hpp \
	  MathIoTest.hpp \
	  GaussianEliminationTest.hpp

all :
	  @echo "Generating OpenKN-math test suite"
	  @${CXXTESTGEN}  --error-printer -o ${TESTEXEC}.cpp ${TESTSUITE}
	  @echo "Compiling OpenKN-math test suite"
	  @g++ -g -o ${TESTEXEC}  ${TESTEXEC}.cpp -I../../tools/ -lOpenKN-math
	  @echo "Running OpenKN-math test suite"
	  @./${TESTEXEC}

.PHONY: clean

clean :
	  @echo "Cleaning OpenKN-math test suite"
	  @rm -Rf testrunner testrunner.cpp
