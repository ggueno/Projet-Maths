/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * MatrixTest.hpp created in 10 2008.
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
#ifndef __OPENKN_MATH__MATRIXTEST_HPP__
#define __OPENKN_MATH__MATRIXTEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/math/Matrix.hpp>

/*
 * Class definition
 */

class MatrixTest : public CxxTest::TestSuite {
public:
	void testConstructorWith2sizes( void ) {
		kn::Matrixf *m = 0;
		m = new kn::Matrixf(3,4);
		TS_ASSERT( m != 0 );
		TS_ASSERT( m->rows() == 3 );
		TS_ASSERT( m->columns() == 4 );
		delete m;
	}

	void testConstructorWith2sizesAndValue( void ) {
		kn::Matrixf *m = 0;
		m = new kn::Matrixf(3,4,2.0);
		TS_ASSERT( m != 0 );
		TS_ASSERT( m->rows() == 3 );
		TS_ASSERT( m->columns() == 4 );
		for(unsigned int i = 0; i < m->rows(); ++i){
			for(unsigned int j = 0; j < m->columns(); ++j){
	TS_ASSERT( (*m)[i][j] == 2.0);
			}
		}
		delete m;
	}

	void testCopyConstructor( void ) {
		kn::Matrixf m(3,4,2.0);
		kn::Matrixf m2(m);
		TS_ASSERT( m2.rows() == m.rows() );
		TS_ASSERT( m2.columns() == m.columns() );
		for(unsigned int i = 0; i < m.rows(); ++i){
			for(unsigned int j = 0; j < m.columns(); ++j){
	TS_ASSERT( m2[i][j] == 2.0);
			}
		}
	}

	void testCopyPointerConstructor( void ) {
		kn::Matrixf *m = new kn::Matrixf(3,4,2.0);
		kn::Matrixf m2(m);
		TS_ASSERT( m2.rows() == m->rows() );
		TS_ASSERT( m2.columns() == m->columns() );
		for(unsigned int i = 0; i < m->rows(); ++i){
			for(unsigned int j = 0; j < m->columns(); ++j){
	TS_ASSERT( m2[i][j] == 2.0);
			}
		}
	}

	void testConstructorWithOneParameter( void ) {
		kn::Matrixf *m = new kn::Matrixf(3);
		kn::Matrixf m2(m);
		TS_ASSERT( m->rows() == 3 );
		TS_ASSERT( m->columns() == 3 );
	}

	void testConstructorWithTwoParametersAndAnArray( void ) {
		float tab[12] = {12.0,11.0,10.0,9.0,8.0,7.0,
					6.0,5.0,4.0,3.0,2.0,1.0};
		kn::Matrixf m(3,4,tab);
		TS_ASSERT( m.rows() == 3 );
		TS_ASSERT( m.columns() == 4 );
		for(unsigned int i = 0; i < m.rows(); ++i){
			for(unsigned int j = 0; j < m.columns(); ++j){
				TS_ASSERT( m[i][j] != 0.0);
				TS_ASSERT( m[i][j] == tab[i*m.columns()+j]);
			}
		}
	}

	void testConstructorWithOneParameterAndAnArray( void ) {
		float tab[9] = {9.0,8.0,7.0,
				6.0,5.0,4.0,
				3.0,2.0,1.0};
		kn::Matrixf m(3,tab);
		TS_ASSERT( m.rows() == 3 );
		TS_ASSERT( m.columns() == 3 );
		for(unsigned int i = 0; i < m.rows(); ++i){
			for(unsigned int j = 0; j < m.columns(); ++j){
				TS_ASSERT( m[i][j] != 0.0);
				TS_ASSERT( m[i][j] == tab[i*m.columns()+j]);
			}
		}
	}

	void testConstructorWithTwoParametersAndVector( void ) {
		kn::Vectorf v(6);
		v[0] = 1.0;
		v[1] = 2.0;
		v[2] = 3.0;
		v[3] = 4.0;
		v[4] = 5.0;
		v[5] = 6.0;

		kn::Matrixf m(3,2,v,true);
		TS_ASSERT( m.rows() == 3 );
		TS_ASSERT( m.columns() == 2 );
		for(unsigned int i = 0; i < m.rows(); ++i){
			for(unsigned int j = 0; j < m.columns(); ++j){
				TS_ASSERT( m[i][j] != 0.0);
				TS_ASSERT( m[i][j] == v[i*2+j]);
			}
		}

		kn::Matrixf m2(3,2,v,false);
		TS_ASSERT( m.rows() == 3 );
		TS_ASSERT( m.columns() == 2 );
		for(unsigned int i = 0; i < m.rows(); ++i){
			for(unsigned int j = 0; j < m.columns(); ++j){
	TS_ASSERT( m2[i][j] == v[j*2+i]);
			}
		}
	}

	void testConstructorWithOneParameterAndVector( void ) {
		kn::Vectorf v(4);
		v[0] = 1.0;
		v[1] = 2.0;
		v[2] = 3.0;
		v[3] = 4.0;

		kn::Matrixf m(2,2,v,true);
		TS_ASSERT( m.rows() == 2 );
		TS_ASSERT( m.columns() == 2 );
		for(unsigned int i = 0; i < m.rows(); ++i){
			for(unsigned int j = 0; j < m.columns(); ++j){
	TS_ASSERT( m[i][j] == v[i*2+j]);
			}
		}

		kn::Matrixf m2(2,2,v,false);
		TS_ASSERT( m.rows() == 2 );
		TS_ASSERT( m.columns() == 2 );
		for(unsigned int i = 0; i < m.rows(); ++i){
			for(unsigned int j = 0; j < m.columns(); ++j){
	TS_ASSERT( m2[i][j] == v[j*2+i]);
			}
		}

	}

	void testAt( void ) {

		kn::Matrixf m1(2,3,0.0);
		m1[0][0] = 1.0; m1[0][1] = 2.0; m1[0][2] = 3.0;
		m1[1][0] = 4.0; m1[1][1] = 5.0; m1[1][2] = 6.0;
		m1.at(0,0)=m1.at(1,2);
		TS_ASSERT_THROWS(m1.at(5,5), kn::MathException);
		TS_ASSERT_THROWS(m1.at(2,2), kn::MathException);
		TS_ASSERT_THROWS(m1.at(1,3), kn::MathException);
		TS_ASSERT(m1[0][0]==6.0f);
	}


	// Operator ==
	void testOperatorEgal( void ) {

		kn::Matrixf m1(2,2,0.0);
		kn::Matrixf m2(2,2,1.0);
		TS_ASSERT( !(m1 == m2));

		kn::Matrixf m3(2,2,1.0);

		TS_ASSERT( (m3 == m2));
	}

	// Operator !=
	void testOperatorDiff( void ) {

		kn::Matrixf m1(2,2,0.0);
		kn::Matrixf m2(2,2,1.0);
		TS_ASSERT( (m1 != m2));

		kn::Matrixf m3(2,2,1.0);

		TS_ASSERT( !(m3 != m2));
	}

	// Operator =
	void testOperatorAssign( void ) {

		kn::Matrixf m1(2,2,0.0);
		kn::Matrixf m2(2,2,1.0);
		m1 = m2;
		for(unsigned int i = 0; i < m1.rows(); ++i){
			for(unsigned int j = 0; j < m1.columns(); ++j){
	TS_ASSERT_EQUALS( m1[i][j], 1.0);
			}
		}

		kn::Matrixf m3;
		m3 = m2;
		for(unsigned int i = 0; i < m1.rows(); ++i){
			for(unsigned int j = 0; j < m1.columns(); ++j){
	TS_ASSERT_EQUALS( m3[i][j], 1.0);
			}
		}

		kn::Matrixf m4(3,3,0.0);
		TS_ASSERT_THROWS(m4 = m2, kn::MathException);
	}

	// Operator +
	void testOperatorPlus( void ) {

		kn::Matrixf m0(2,3,0.0);
		kn::Matrixf m1(2,3,1.0);
		kn::Matrixf m2(2,3,1.0);


		m0 = m1 + m2;
		for(unsigned int i = 0; i < m0.rows(); ++i){
			for(unsigned int j = 0; j < m0.columns(); ++j){
	TS_ASSERT( m0[i][j] == 2.0);
			}
		}

		m1 += m2;
		for(unsigned int i = 0; i < m1.rows(); ++i){
			for(unsigned int j = 0; j < m1.columns(); ++j){
	TS_ASSERT( m1[i][j] == 2.0);
			}
		}

		m0 = m1;
		m1 += 2.0;
		for(unsigned int i = 0; i < m1.rows(); ++i){
			for(unsigned int j = 0; j < m1.columns(); ++j){
	TS_ASSERT_DELTA(m1[i][j]-m0[i][j], 2.0, 1.0e-10);
			}
		}
	}

	// Operator -
	void testOperatorSubtract( void ) {

		kn::Matrixf m0(2,3,0.0);
		kn::Matrixf m1(2,3,1.0);
		kn::Matrixf m2(2,3,1.0);
		m0 = m1 - m2;
		for(unsigned int i = 0; i < m0.rows(); ++i){
			for(unsigned int j = 0; j < m0.columns(); ++j){
	TS_ASSERT( m0[i][j] == 0.0);
			}
		}

		m1 -= m2;
		for(unsigned int i = 0; i < m1.rows(); ++i){
			for(unsigned int j = 0; j < m1.columns(); ++j){
	TS_ASSERT( m1[i][j] == 0.0);
			}
		}

		m0 = m1;
		m1 -= 2.0;
		for(unsigned int i = 0; i < m1.rows(); ++i){
			for(unsigned int j = 0; j < m1.columns(); ++j){
	TS_ASSERT_DELTA(m0[i][j]-m1[i][j], 2.0, 1.0e-10);
			}
		}


	}

	// Operator /
	void testOperatorDivide( void ) {

		kn::Matrixf m0(2,3,2.0);
		kn::Matrixf m1(2,3,2.0);

		m0 = m1 / 2.0;
		for(unsigned int i = 0; i < m0.rows(); ++i){
			for(unsigned int j = 0; j < m0.columns(); ++j){
	TS_ASSERT( m0[i][j] == 1.0);
			}
		}

		m1 /= 2.0;
		for(unsigned int i = 0; i < m1.rows(); ++i){
			for(unsigned int j = 0; j < m1.columns(); ++j){
	TS_ASSERT( m1[i][j] == 1.0);
			}
		}
	}

	// Operator *
	void testOperatorTimes( void ) {

		kn::Matrixf m1(2,3,2.0);
		kn::Matrixf m2(3,2,2.0);

		kn::Matrixf m0(m1 * m2);

		for(unsigned int i = 0; i < m0.rows(); ++i){
			for(unsigned int j = 0; j < m0.columns(); ++j){
				TS_ASSERT( m0[i][j] == 12.0);
			}
		}

		kn::Matrixf m3(3,3,2.0);
		kn::Matrixf m4(3,3,2.0);

		m3 *= m4;

		for(unsigned int i = 0; i < m3.rows(); ++i){
			for(unsigned int j = 0; j < m3.columns(); ++j){
				TS_ASSERT( m3[i][j] == 12.0);
			}
		}

		m3 = m4 * 6.0;

		for(unsigned int i = 0; i < m3.rows(); ++i){
			for(unsigned int j = 0; j < m3.columns(); ++j){
					TS_ASSERT( m3[i][j] == 12.0);
			}
		}

		m4 *= 6.0;

		for(unsigned int i = 0; i < m4.rows(); ++i){
			for(unsigned int j = 0; j < m4.columns(); ++j){
				TS_ASSERT( m4[i][j] == 12.0);
			}
		}

		kn::Vectorf v0((unsigned int)3,2.0f);
		kn::Vectorf v1(m1*v0);
		for(unsigned int j = 0; j < v1.size(); ++j){
			TS_ASSERT( v1[j] == 12.0);
		}
	}

	void testTime(void) {
		kn::Matrixf m0(2,3);
		kn::Matrixf m1(2,3,2.0);
		kn::Matrixf m2(3,3,2.0);

		TS_ASSERT_THROWS(m0.times(m2,m1), kn::MathException);
		m0.times(m1,m2);

		for(unsigned int i = 0; i < m0.rows(); ++i){
			for(unsigned int j = 0; j < m0.columns(); ++j){
	TS_ASSERT( m0[i][j] == 12.0);
			}
		}

		kn::Matrixf m3(3,3);
		kn::Matrixf m4(2,2);

		TS_ASSERT_THROWS(m3.times(m1,m2), kn::MathException);
		TS_ASSERT_THROWS(m4.times(m1,m2), kn::MathException);
	}

		// Operator -
	void testOperatorMinus( void ) {

		kn::Matrixf m1(2,3,2.0);
		kn::Matrixf m2(-m1);

		for(unsigned int i = 0; i < m1.rows(); ++i){
			for(unsigned int j = 0; j < m2.columns(); ++j){
	TS_ASSERT( m2[i][j] == -m1[i][j]);
			}
		}
	}

	void testOperatorNorm( void ) {

		kn::Matrixf m1(2,2,2.0f);
		float norm = sqrt(2*2*(2.0f*2.0f));

		TS_ASSERT( m1.getNorm() == norm);

	}


	void testOperatorTranspose( void ) {

		kn::Matrixf m1(2,3);
		m1[0][0] = 1.0; m1[0][1] = 2.0; m1[0][2] = 3.0;
		m1[1][0] = 4.0; m1[1][1] = 5.0; m1[1][2] = 6.0;

		kn::Matrixf m2(3,2);
		m2[0][0] = 1.0; m2[0][1] = 4.0;
		m2[1][0] = 2.0; m2[1][1] = 5.0;
		m2[2][0] = 3.0; m2[2][1] = 6.0;

		m1.transpose();

		TS_ASSERT( m1 == m2);

		kn::Matrixf m3(2,3);
		m3[0][0] = 1.0; m3[0][1] = 2.0; m3[0][2] = 3.0;
		m3[1][0] = 4.0; m3[1][1] = 5.0; m3[1][2] = 6.0;

		TS_ASSERT( m3.getTranspose() == m2);
	}


	void testOperatorPower( void ) {

		kn::Matrixf m1(2,2,2.0f);

		m1.power(3);

		kn::Matrixf m2(2,2,32.0f);

		TS_ASSERT( m1 == m2);
	}

	void testOperatorIdentity( void ) {

		kn::Matrixf m1(2,3,0.0f);

		m1.setIdentity();

		for(unsigned int i = 0; i < m1.rows(); ++i){
			for(unsigned int j = 0; j < m1.columns(); ++j){
	if(i==j){
		TS_ASSERT( m1[i][j] == 1.0);
	}else{
		TS_ASSERT( m1[i][j] == 0.0);
	}

			}
		}
	}

	void testOperatorRoundZero( void ) {

		kn::Matrixf m1(2,3,0.0000001f);

		m1.roundZero(0.001);

		for(unsigned int i = 0; i < m1.rows(); ++i){
			for(unsigned int j = 0; j < m1.columns(); ++j){
		TS_ASSERT( m1[i][j] == 0.0);
			}
		}
	}

	void testSetSubMatrix( void ) {

		kn::Matrixf m1(4,4,1.0f);
		kn::Matrixf m2(2,2,2.0f);
		m1.setSubMatrix(1,1,m2);

		for(unsigned int i = 0; i < 4; ++i){
			for(unsigned int j = 0; j < 4; ++j){
	if((i==0 || i==3) || (j==0 || j==3)){
		TS_ASSERT( m1[i][j] == 1.0f);
	}else{
		TS_ASSERT( m1[i][j] == 2.0f);
	}
			}
		}
	}

	void testGetSubMatrix( void ) {

		kn::Matrixf m1(4,4,1.0f);
		kn::Matrixf m2;
		m1[1][2]=5.0f;
		m1[1][3]=6.0f;
		m2 = m1.getSubMatrix(1,2,2,2);

		TS_ASSERT( m2.rows()==2);
		TS_ASSERT( m2.columns()==2);
		TS_ASSERT( m2[0][0] == 5.0f);
		TS_ASSERT( m2[0][1] == 6.0f);
		TS_ASSERT( m2[1][0] == 1.0f);
		TS_ASSERT( m2[1][1] == 1.0f);

		TS_ASSERT_THROWS(m1.getSubMatrix(1,4,0,2), kn::MathException);
		TS_ASSERT_THROWS(m1.getSubMatrix(1,2,0,5), kn::MathException);
		TS_ASSERT_THROWS(m1.getSubMatrix(4,1,0,2), kn::MathException);
		TS_ASSERT_THROWS(m1.getSubMatrix(1,2,5,0), kn::MathException);
	}


	void testSetRow( void ) {

		kn::Matrixf m(4,4,0.0f);
		kn::Vector<float> v(4);
		v[0]=2.0f; v[1]=-9.0f; v[2]=4.0f; v[3]=13.0f;

		m.setRow(1,v);

		for(unsigned int i = 0; i < 4; ++i){
			TS_ASSERT(m[1][i] == v[i]);
			TS_ASSERT(m[1][i] != 0.0);
		}

		float buf[5]={3.0f,5.3f,6.3f,-7.3f,9.3f};
		m.setRow(2,buf);

		for(unsigned int i = 0; i < 4; ++i){
			TS_ASSERT(m[2][i] == buf[i]);
			TS_ASSERT(m[2][i] != 0.0);
		}
	}


	void testSetColumn( void ) {

		kn::Matrixf m(4,4,0.0f);
		kn::Vector<float> v(4);
		v[0]=2.0f; v[1]=-9.0f; v[2]=4.0f; v[3]=13.0f;

		m.setColumn(1,v);

		for(unsigned int i = 0; i < 4; ++i){
			TS_ASSERT(m[i][1] == v[i]);
			TS_ASSERT(m[i][1] != 0.0);
		}

		float buf[5]={3.0f,5.3f,6.3f,-7.3f,9.3f};
		m.setColumn(2,buf);

		for(unsigned int i = 0; i < 4; ++i){
			TS_ASSERT(m[i][2] == buf[i]);
			TS_ASSERT(m[i][2] != 0.0);
		}
	}

	void testGetRow( void ) {

		kn::Matrixf m(4,4,1.0f);
		for(unsigned int i = 0; i < 4; ++i){
			m[1][i] = i+1.0f;
		}
		kn::Vector<float> v(m.getRow(1));

		TS_ASSERT( v.size() == 4);

		for(unsigned int i = 0; i < 4; ++i){
			TS_ASSERT(m[1][i] == v[i]);
		}
	}

	void testGetColumn( void ) {

		kn::Matrixf m(4,4,1.0f);
		for(unsigned int i = 0; i < 4; ++i){
			m[i][1] = i+1.0f;
		}
		kn::Vector<float> v(m.getColumn(1));

		TS_ASSERT( v.size() == 4);

		for(unsigned int i = 0; i < 4; ++i){
			TS_ASSERT(m[i][1] == v[i]);
		}
	}

	void testSwapRows( void ) {

		float tab[9] = {9.0,8.0,7.0,
				6.0,5.0,4.0,
				3.0,2.0,1.0};
		kn::Matrixf m(3,tab);
		kn::Matrixf m2(m);

		m.swapRows(1,2);

		for(unsigned int i = 0; i < 3; ++i){
			TS_ASSERT(m[1][i] == m2[2][i]);
			TS_ASSERT(m[2][i] == m2[1][i]);
		}
	}

	void testSwapColumns( void ) {

		float tab[9] = {9.0,8.0,7.0,
				6.0,5.0,4.0,
				3.0,2.0,1.0};
		kn::Matrixf m(3,tab);
		kn::Matrixf m2(m);

		m.swapColumns(1,2);

		for(unsigned int i = 0; i < 3; ++i){
			TS_ASSERT(m[i][1] == m2[i][2]);
			TS_ASSERT(m[i][2] == m2[i][1]);
		}
	}

	void testSetDiagonal( void ) {

		kn::Matrixf m(4,3,1.0f);
		kn::Vector<float> v(3);
		v[0]=2.0f; v[1]=-9.0f; v[2]=4.0f;

		m.setDiagonal(v);

		for(unsigned int i = 0; i < 3; ++i){
			TS_ASSERT(m[i][i] == v[i]);
		}

		float buf[5]={3.0f,5.3f,6.3f,-7.3f,9.3f};
		m.setDiagonal(buf);

		for(unsigned int i = 0; i < 3; ++i){
			TS_ASSERT(m[i][i] == buf[i]);
		}
	}

	void testGetDiagonal( void ) {

		kn::Matrixf m(3,4,1.0f);
		for(unsigned int i = 0; i < m.rows(); ++i){
			m[i][1] = i+1.0f;
		}
		kn::Vector<float> v(m.getDiagonal());

		for(unsigned int i = 0; i < m.rows(); ++i){
			TS_ASSERT(m[i][i] == v[i]);
		}

		kn::Matrixf m2(4,3,1.0f);
		for(unsigned int i = 0; i < m2.columns(); ++i){
			m2[i][1] = i+1.0f;
		}
		kn::Vector<float> v2(m.getDiagonal());

		for(unsigned int i = 0; i < m2.columns(); ++i){
			TS_ASSERT(m2[i][i] == v2[i]);
		}

	}


	void testTrace( void ) {
		float tab[9] = {9.0,8.0,7.0,
				6.0,5.0,4.0,
				3.0,2.0,1.0};
		kn::Matrixf m(3,tab);

		TS_ASSERT(m.trace() == 15.0);
	}


	// Operator Vector * Matrix
	void testOperatorVectorTimesMatrix( void ) {

		kn::Matrixf m(2,3,2.0);
		kn::Vector<float> v(2,2.0);
		kn::Vector<float> r(v * m);

		TS_ASSERT( r.size() == 3);

		for(unsigned int i = 0; i < r.size(); ++i){
			TS_ASSERT( r[i] == 8.0f);
		}
	}

	// Operator  Matrix * Vector
	void testOperatorTimesVector( void ) {

		kn::Matrixf m(2,3,2.0);
		kn::Vector<float> v((unsigned int)3,2.0f);
		kn::Vector<float> r(m * v);

		TS_ASSERT( r.size() == 2);

		for(unsigned int i = 0; i < r.size(); ++i){
			TS_ASSERT( r[i] == 12.0f);
		}
	}

	// Operator  d * Matrix
	void testOperatorScalarTimesMatrix( void ) {

		kn::Matrixf m(2,3,2.0);

		m = 2.0f*m;

		for(unsigned int i = 0; i < m.rows(); ++i){
			for(unsigned int j = 0; j < m.columns(); ++j){
				TS_ASSERT( m[i][j] == 4.0);
			}
		}
	}

	// setZero
	void testSetZero( void ) {

		kn::Matrix<double> m(2,3,2.0);

		m.setZero();

		for(unsigned int i = 0; i < m.rows(); ++i){
				for(unsigned int j = 0; j < m.columns(); ++j){
						TS_ASSERT( m[i][j] == 0.0);
				}
		}
	}

	// fill
	void testFill( void ) {

		kn::Matrix<double> m(2,3,2.0);

		m.fill(4.0);

		for(unsigned int i = 0; i < m.rows(); ++i){
			for(unsigned int j = 0; j < m.columns(); ++j){
				TS_ASSERT( m[i][j] == 4.0);
			}
		}
	}

	// cross3x3
	void testCross3x3( void ) {
		kn::Vector<double> v1(3);
		v1[0] = 1.0;
		v1[1] = 0.0;
		v1[2] = 5.0;

		kn::Vector<double> v2(3);
		v2[0] =  0.0;
		v2[1] =  1.0;
		v2[2] =  5.0;

		kn::Matrix<double> m(3,3);
		m.cross3x3(v1);

		kn::Vector<double> v3(m*v2);
		kn::Vector<double,kn::StaticStorePolicy<double,3> > v4(v1^v2);

		for(unsigned int i = 0; i < 3; ++i){
			TS_ASSERT_EQUALS(v3[i],v4[i]);
		}
	}

	// cross3x3
	void testCross3x3Exception( void ) {
		kn::Vector<double> v1(4);
		kn::Matrix<double> m1(3,3);
		TS_ASSERT_THROWS(m1.cross3x3(v1), kn::MathException);

		kn::Vector<double> v2(3);
		kn::Matrix<double> m2(4,2);
		TS_ASSERT_THROWS(m2.cross3x3(v2), kn::MathException);
	}


};


/*
 * End of Anti-doublon
 */

#endif
