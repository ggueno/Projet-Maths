/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * SVDTest.hpp created in 11 2008.
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
#ifndef __OPENKN_MATH__SVDTEST_HPP__
#define __OPENKN_MATH__SVDTEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/math/SVD.hpp>

/*
 * Class definition
 */
class SVDTest: public CxxTest::TestSuite{
  public:

    void testSVDdecompositionRegularSquareMatrix(void){

      // identity 3x3 matrix
      kn::Matrix<double> Id3(3);
      Id3.setIdentity();

      // A :a square regular 3x3 matrix
      kn::Matrix<double> A(3,3);
      A.setIdentity();
      A[0][2] = 10.0;
      A[1][2] = -5.0;
      A[0][0] = 2.0;
      A[1][1] = 5.0;

      // U is a copy of A
      kn::Matrix<double> U(A);

      // SVD decomposition
      kn::Vector<double> w(3);
      kn::Matrix<double> V(3,3);
      kn::decompositionSVD(U,w,V);

      // check whether U is orthogonal
      kn::Matrix<double> checkU(U*U.getTranspose() - Id3);
      for(unsigned int i = 0; i < U.rows(); ++i)
          for(unsigned int j = 0; j < U.columns(); ++j)
              TS_ASSERT_DELTA(checkU[i][j], 0.0, 1.0e-14);

      // check whether V is orthogonal
      kn::Matrix<double> checkV(V*V.getTranspose() - Id3);
      for(unsigned int i = 0; i < V.rows(); ++i)
          for(unsigned int j = 0; j < V.columns(); ++j)
              TS_ASSERT_DELTA(checkV[i][j], 0.0, 1.0e-14);

      // check whether all singular values are non-zero and positive
      for(unsigned int i = 0; i < w.size(); ++i)
          TS_ASSERT_LESS_THAN(1.0e-9, w[i]);

      // Check whether A = UwVt
      kn::Matrix<double> D(3,3,0.0);
      D.setDiagonal(w);

      kn::Matrix<double> checkA(A-U*D*V.getTranspose());
      for(unsigned int i = 0; i < checkA.rows(); ++i)
          for(unsigned int j = 0; j < checkA.columns(); ++j){
              TS_ASSERT_DELTA(checkA[i][j], 0.0, 1.0e-14);
          }
    }



};

/*
 * End of Anti-doublon
 */
#endif
