/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * GaussianEliminationTest.hpp created in 10 2009.
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
#ifndef __OPENKN_MATH__GAUSIAN_ELIMINATION_TEST_HPP__
#define __OPENKN_MATH__GAUSIAN_ELIMINATION_TEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/math/GaussianElimination.hpp>
#include <OpenKN/math/Matrix.hpp>
#include <OpenKN/math/MathIO.hpp>
#include <OpenKN/math/MathException.hpp>

/*
 * Class definition
 */
class GaussianEliminationTest: public CxxTest::TestSuite{
  public:




    void assertIdentity(kn::Matrix<double> &M, const double &zero){
      for(unsigned int i=0; i<M.rows(); ++i)
	for(unsigned int j=0; j<M.columns(); ++j)
	  {
	    if(i==j){
	      TS_ASSERT_DELTA(M[i][j],(double)1.0, zero);
	    }
	    else TS_ASSERT_DELTA(M[i][j],(double)0.0, zero);
	  }
    }


    /* This is a test on a gaussian elimination inverse computation.
       It implicitely tests the standard gaussian elimination.
    */
    void testInverseTotal(void){
      bool total = true;
      int succeed = 0;

      kn::Matrix<double> A1;
      kn::loadMatrix(A1,"input/matrix_det_77.mat");
      kn::Matrix<double> A1inv(A1.rows(),A1.columns());
      succeed = kn::gaussianEliminationInverseMatrix(A1,A1inv,total);
      A1 = A1 * A1inv;
      assertIdentity(A1,1.0e-10);
      TS_ASSERT_EQUALS(succeed,1);


      kn::Matrix<double> A2;
      kn::loadMatrix(A2,"input/matrix_50x50.mat");
      kn::Matrix<double> A2inv(A2.rows(),A2.columns());
      succeed = kn::gaussianEliminationInverseMatrix(A2,A2inv,total);
      A2 = A2 * A2inv;
      assertIdentity(A2,1.0e-10);
      TS_ASSERT_EQUALS(succeed,1);

      kn::Matrix<double> A3;
      kn::loadMatrix(A3,"input/matrix_100x100.mat");
      kn::Matrix<double> A3inv(A3.rows(),A3.columns());
      succeed = kn::gaussianEliminationInverseMatrix(A3,A3inv,total);
      A3 = A3 * A3inv;
      assertIdentity(A3,1.0e-10);
      TS_ASSERT_EQUALS(succeed,1);

      kn::Matrix<double> A4;
      kn::loadMatrix(A4,"input/matrix_rank3.mat");
      kn::Matrix<double> A4inv(A4.rows(),A4.columns());
      succeed = kn::gaussianEliminationInverseMatrix(A4,A4inv,total);
      TS_ASSERT_EQUALS(succeed,0);

      kn::Matrix<double> A5;
      kn::loadMatrix(A5,"input/matrix_rank6.mat");
      kn::Matrix<double> A5inv(A5.rows(),A5.columns());
      TS_ASSERT_THROWS(kn::gaussianEliminationInverseMatrix(A5,A5inv,total), kn::MathException);
    }



    /* This is a test on a gaussian elimination inverse computation.
       It implicitely tests the standard gaussian elimination.
    */
    void testInversePartial(void){
      bool total = false;
      int succeed = 0;

      kn::Matrix<double> A1;
      kn::loadMatrix(A1,"input/matrix_det_77.mat");
      kn::Matrix<double> A1inv(A1.rows(),A1.columns());
      succeed = kn::gaussianEliminationInverseMatrix(A1,A1inv,total);
      A1 = A1 * A1inv;
      assertIdentity(A1,1.0e-10);
      TS_ASSERT_EQUALS(succeed,1);


      kn::Matrix<double> A2;
      kn::loadMatrix(A2,"input/matrix_50x50.mat");
      kn::Matrix<double> A2inv(A2.rows(),A2.columns());
      succeed = kn::gaussianEliminationInverseMatrix(A2,A2inv,total);
      A2 = A2 * A2inv;
      assertIdentity(A2,1.0e-10);
      TS_ASSERT_EQUALS(succeed,1);

      kn::Matrix<double> A3;
      kn::loadMatrix(A3,"input/matrix_100x100.mat");
      kn::Matrix<double> A3inv(A3.rows(),A3.columns());
      succeed = kn::gaussianEliminationInverseMatrix(A3,A3inv,total);
      A3 = A3 * A3inv;
      assertIdentity(A3,1.0e-10);
      TS_ASSERT_EQUALS(succeed,1);

      kn::Matrix<double> A4;
      kn::loadMatrix(A4,"input/matrix_rank3.mat");
      kn::Matrix<double> A4inv(A4.rows(),A4.columns());
      succeed = kn::gaussianEliminationInverseMatrix(A4,A4inv,total);
      TS_ASSERT_EQUALS(succeed,0);

      kn::Matrix<double> A5;
      kn::loadMatrix(A5,"input/matrix_rank6.mat");
      kn::Matrix<double> A5inv(A5.rows(),A5.columns());
      TS_ASSERT_THROWS(kn::gaussianEliminationInverseMatrix(A5,A5inv,total), kn::MathException);
    }

};


/*
 * End of Anti-doublon
 */
#endif
