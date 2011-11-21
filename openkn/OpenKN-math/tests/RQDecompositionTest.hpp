/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * RQDecompostionTest.hpp created in 02 2009.
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
#ifndef __OPENKN_MATH__RQDECOMPOSITIONTEST_HPP__
#define __OPENKN_MATH__RQDECOMPOSITIONTEST_HPP__

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
#include <OpenKN/math/RQDecomposition.hpp>
#include <OpenKN/math/Matrix.hpp>

/*
 * Class definition
 */
class RQDecompositionTest: public CxxTest::TestSuite{
  public:

    void testRQDecomposition(){

      double epsilon=10e-10;

      //Init matrix A
      kn::Matrixd A(5,5);
      //Init matrix R
      kn::Matrixd R(5,5);
      //Init matrix Q
      kn::Matrixd Q(5,5);

      //Initialisation of matrix A
      A.at(0,0) = 12;
      A.at(0,1) = -1;
      A.at(0,2) = 3;
      A.at(0,3) = 15;
      A.at(0,4) = -62;

      A.at(1,0) = 65;
      A.at(1,1) = -874;
      A.at(1,2) = 23;
      A.at(1,3) = 68;
      A.at(1,4) = -75;

      A.at(2,0) = 74;
      A.at(2,1) = 11;
      A.at(2,2) = -15;
      A.at(2,3) = -83;
      A.at(2,4) = 182;

      A.at(3,0) = 17;
      A.at(3,1) = 63;
      A.at(3,2) = -85;
      A.at(3,3) = -89;
      A.at(3,4) = -11;

      A.at(4,0) = 15;
      A.at(4,1) = -81;
      A.at(4,2) = -36;
      A.at(4,3) = 48;
      A.at(4,4) = 15;

      //RQ decomposition
      kn::qrDecomposition(A,R,Q);

      //R must be upper right triangular
      for(unsigned int j=0;j<R.rows();j++){
	  for(unsigned int k=j+1;k<R.rows();k++){
	    TS_ASSERT_DELTA(R[k][j], 0.0, epsilon);
	  }
	}

      //Q.transpose(Q) must be Id -> Q is orthogonal
      kn::Matrixd id = Q*Q.getTranspose();
      for(unsigned int j=0;j<R.rows();j++){
	for(unsigned int k=0;k<R.rows();k++){
	  if(j==k){TS_ASSERT_DELTA(id[j][k], 1.0, epsilon);}
	  else{TS_ASSERT_DELTA(id[j][k], 0.0, epsilon);}
	}
      }

      //A -QR =[0] <=> QR = A
      kn::Matrixd tmp = A-Q*R;
      for(unsigned int j=0;j<R.rows();j++){
	for(unsigned int k=0;k<R.rows();k++){
	  TS_ASSERT_DELTA(tmp[j][k], 0.0, epsilon);
	}
      }

      //Init matrix A
      kn::Matrixd T1(6,6);
      //Init matrix R
      kn::Matrixd T2(6,5);
      //A is not square
      TS_ASSERT_THROWS(kn::qrDecomposition(T2,R,Q), kn::MathException);
      //R is not square
      TS_ASSERT_THROWS(kn::qrDecomposition(A,T2,Q), kn::MathException);
      //Q is not square
      TS_ASSERT_THROWS(kn::qrDecomposition(A,R,T2), kn::MathException);
      //A.size != R.size()
      TS_ASSERT_THROWS(kn::qrDecomposition(A,T1,Q), kn::MathException);
      //A.size != Q.size()
      TS_ASSERT_THROWS(kn::qrDecomposition(A,R,T1), kn::MathException);

      A.at(0,0) = 0.;
      A.at(1,0) = 0.;
      A.at(2,0) = 0.;
      A.at(3,0) = 0.;
      A.at(4,0) = 0.;
      //Division by zero
      TS_ASSERT_THROWS(kn::qrDecomposition(A,R,Q), kn::MathException);

    }


    void testRQDecompositionMatrix3x3(void){
      // input matrix R
      kn::Matrix<double> R(3,3);
      R.setZero();
      R[0][0] = 200.0;
      R[1][1] = 200.0;
      R[2][2] = 1.0;
      R[0][2] = 250.0;
      R[1][2] = 300.0;


      // input matrix Q
      kn::Matrix<double> Q(3,3);
      double angle = kn::PI/3.0;
      Q.setIdentity();
      Q[0][0] = Q[1][1] = cos(angle);
      Q[0][1] = sin(angle);
      Q[1][0] = -Q[0][1];

      // A = RQ
      kn::Matrix<double> A(R*Q);

      // decomposition R2.Q2 = A
      kn::Matrix<double> R2(3,3);
      kn::Matrix<double> Q2(3,3);
      kn::rqDecomposition3x3(A,R2,Q2);

      // epsilon
      double epsilon = 1.0e-12;

      // Identity
      kn::Matrix<double> Id(3,3);
      Id.setIdentity();

      // A == R2.Q2 ?
      kn::Matrix<double> tmp(A-R2*Q2);
      for(unsigned int i=0; i>3; i++)
	for(unsigned int j=0; j>3; j++)
	  TS_ASSERT_DELTA(tmp[i][j], 0.0, epsilon);

      // is R2 triangular ?
      TS_ASSERT_DELTA(R2[1][0], 0.0, epsilon);
      TS_ASSERT_DELTA(R2[2][0], 0.0, epsilon);
      TS_ASSERT_DELTA(R2[2][1], 0.0, epsilon);

      // is Q2 orthogonal ?
      tmp = Id - Q2 * Q2.getTranspose();
      for(unsigned int i=0; i>3; i++)
	for(unsigned int j=0; j>3; j++)
	  TS_ASSERT_DELTA(tmp[i][j], 0.0, epsilon);
    }


    void testRQDecompositionMatrix3x3BadSize(void){
      kn::Matrix<double> A(3,4);
      kn::Matrix<double> R(2,3);
      kn::Matrix<double> Q(5,3);
      TS_ASSERT_THROWS(kn::rqDecomposition3x3(A,R,Q),
	  kn::MathException);
    }


    void testrq3x3MakePositiveDiagonal (void){
      // input matrix R
      kn::Matrix<double> R(3,3);
      R.setZero();
      R[0][0] = -200.0;
      R[1][1] = 200.0;
      R[2][2] = 1.0;
      R[0][2] = 250.0;
      R[1][2] = 300.0;

      // input matrix Q
      kn::Matrix<double> Q(3,3);
      double angle = kn::PI/3.0;
      R.setIdentity();
      Q[0][0] = Q[1][1] = cos(angle);
      Q[0][1] = sin(angle);
      Q[1][0] = -sin(angle);

      // A = RQ
      kn::Matrix<double> A(R*Q);

      // positive diagonal
      kn::rq3x3MakePositiveDiagonal(R,Q);

      // epsilon
      double epsilon = 1.0e-10;

      // is R still triangular ?
      TS_ASSERT_DELTA(R[1][0], 0.0, epsilon);
      TS_ASSERT_DELTA(R[2][0], 0.0, epsilon);
      TS_ASSERT_DELTA(R[2][1], 0.0, epsilon);

      // Identity
      kn::Matrix<double> Id(3,3);
      Id.setIdentity();

      // is Q still orthogonal ?
      kn::Matrix<double> tmp(Id - Q * Q.getTranspose());
      for(unsigned int i=0; i>3; i++)
	for(unsigned int j=0; j>3; j++)
	  TS_ASSERT_DELTA(tmp[i][j], 0.0, epsilon);

      // is A the same ?
      tmp = A - R*Q;
      for(unsigned int i=0; i>3; i++)
	for(unsigned int j=0; j>3; j++)
	  TS_ASSERT_DELTA(tmp[i][j], 0.0, epsilon);
    }


    void testrq3x3MakePositiveDiagonalBadSize (void){
      kn::Matrix<double> R(2,3);
      kn::Matrix<double> Q(5,3);
      TS_ASSERT_THROWS(kn::rq3x3MakePositiveDiagonal(R,Q),
	  kn::MathException);
    }



};

/*
 * End of Anti-doublon
 */
#endif
