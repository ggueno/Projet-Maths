/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * CholeskyDecompostionTest.hpp created in 02 2010.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-math.
 *
 * The OpenKraken-math is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-math is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_MATH__CHOLESKY_DECOMPOSITIONTEST_HPP__
#define __OPENKN_MATH__CHOLESKY_DECOMPOSITIONTEST_HPP__

/*
 * External Includes
 */
#include <cmath>
#include <iostream>
#include <string>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/math/CholeskyDecomposition.hpp>
#include <OpenKN/math/Matrix.hpp>

/*
 * Class definition
 */
class CholeskyDecompositionTest: public CxxTest::TestSuite{
  public:

	// K is a square symetric matric
	void ckeckDecompostion(kn::Matrix<double> &K)
	{
	  double epsilon = 10e-10;

	  // symetric matrix
	  kn::Matrix<double> A(K * K.getTranspose());

	  // cholesky decomposition
	  kn::Matrix<double> L = choleskyDecomposition(A);

	  // check decomposition
	  A = A - L * L.getTranspose();
	  for(unsigned int i=0; i<A.rows(); i++)
	    for(unsigned int j=0; j<A.columns(); j++)
		TS_ASSERT_DELTA(A[i][j], 0.0, epsilon);

	  // check L is lower triangular matrix
	  for(unsigned int i=0; i<A.rows(); i++)
	    for(unsigned int j=i+1; j<A.columns(); j++)
		TS_ASSERT_DELTA(L[i][j], 0.0, epsilon);
	}


	void testCholeskyDecomposition()
	{
	  // input triangular matrix
	  kn::Matrix<double> K1;
	  kn::loadMatrix(K1,"input/matrix_3x3_lowerTriangular.mat");
	  ckeckDecompostion(K1);

	  // input triangular matrix
	  kn::Matrix<double> K2;
	  kn::loadMatrix(K2,"input/matrix_10x10_lowerTriangular.mat");
	  ckeckDecompostion(K2);

	  // input triangular matrix
	  kn::Matrix<double> K3;
	  kn::loadMatrix(K3,"input/matrix_50x50_lowerTriangular.mat");
	  ckeckDecompostion(K3);
	}

        void testCholeskyNonSquareMatrix (void){
	  // input matrix
	  kn::Matrix<double> A;
	  kn::loadMatrix(A,"input/matrix_rank6.mat");
	  TS_ASSERT_THROWS(kn::choleskyDecomposition(A),kn::MathException);
	}

        void testCholeskyNonSymetricMatrix (void){
	  // input matrix
	  kn::Matrix<double> A;
	  kn::loadMatrix(A,"input/matrix_det_77.mat");
	  TS_ASSERT_THROWS(kn::choleskyDecomposition(A),kn::MathException);
	}

};

/*
 * End of Anti-doublon
 */
#endif
