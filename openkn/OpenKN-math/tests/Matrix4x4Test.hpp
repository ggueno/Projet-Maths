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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
 \***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_MATH__MATRIX4x4TEST_HPP__
#define __OPENKN_MATH__MATRIX4x4TEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/math/Matrix4x4.hpp>

/*
 * Class definition
 */

class Matrix4x4Test : public CxxTest::TestSuite {
	public:
		void testConstructor( void ) {
			kn::Matrix4x4f *m = 0;
			m = new kn::Matrix4x4f();
			TS_ASSERT( m != 0 );
			TS_ASSERT( m->rows() == 4 );
			TS_ASSERT( m->columns() == 4 );
			delete m;
		}

		void testConstructorWithMatrix( void ) {
			kn::Matrixf *m = 0;
			m = new kn::Matrixf(4,4,2.0);
			kn::Matrix4x4f *m2 = new kn::Matrix4x4f(m);
			TS_ASSERT( m2 != 0 );
			TS_ASSERT( m2->rows() == 4 );
			TS_ASSERT( m2->columns() == 4 );
			for(unsigned int i = 0; i < m2->rows(); ++i){
				for(unsigned int j = 0; j < m2->columns(); ++j){
					TS_ASSERT( (*m2)[i][j] == (*m)[i][j]);
				}
			}
			delete m;
			delete m2;

			kn::Matrixf *m3 = new kn::Matrixf(5,3,2.0);
			TS_ASSERT_THROWS(new kn::Matrix4x4f(m3),kn::MathException);
			delete m3;
		}

		void testConstructorWithValue( void ) {
			kn::Matrix4x4f *m = 0;
			m = new kn::Matrix4x4f(2.0);
			TS_ASSERT( m != 0 );
			TS_ASSERT( m->rows() == 4 );
			TS_ASSERT( m->columns() == 4 );
			for(unsigned int i = 0; i < m->rows(); ++i){
				for(unsigned int j = 0; j < m->columns(); ++j){
					TS_ASSERT( (*m)[i][j] == 2.0);
				}
			}
			delete m;
		}

		void testCopyConstructor( void ) {
			kn::Matrix4x4f m(2.0);
			kn::Matrix4x4f m2(m);
			TS_ASSERT( m2.rows() == m.rows() );
			TS_ASSERT( m2.columns() == m.columns() );
			for(unsigned int i = 0; i < m.rows(); ++i){
				for(unsigned int j = 0; j < m.columns(); ++j){
					TS_ASSERT( m2[i][j] == 2.0);
				}
			}
		}

		void testCopyPointerConstructor( void ) {
			kn::Matrix4x4f *m = new kn::Matrix4x4f(2.0);
			kn::Matrix4x4f m2(m);
			TS_ASSERT( m2.rows() == m->rows() );
			TS_ASSERT( m2.columns() == m->columns() );
			for(unsigned int i = 0; i < m->rows(); ++i){
				for(unsigned int j = 0; j < m->columns(); ++j){
					TS_ASSERT( m2[i][j] == 2.0);
				}
			}
		}

		void testConstructorWithAnArray( void ) {
			float tab[16] = {16.0,15.0,14.0,13.0,12.0,11.0,10.0
				,9.0,8.0,7.0,6.0,5.0,4.0,3.0,2.0,1.0};
			kn::Matrix4x4f m(tab);
			TS_ASSERT( m.rows() == 4 );
			TS_ASSERT( m.columns() == 4 );
			for(unsigned int i = 0; i < m.rows(); ++i){
				for(unsigned int j = 0; j < m.columns(); ++j){
					TS_ASSERT( m[i][j] == tab[i*m.columns()+j]);
					TS_ASSERT( m[i][j] != 0.0);
				}
			}
		}

		void testConstructorWithVector( void ) {
			kn::Vectorf v(16);
			v[0] = 1.0;
			v[1] = 2.0;
			v[2] = 3.0;
			v[3] = 4.0;
			v[4] = 5.0;
			v[5] = 6.0;
			v[6] = 7.0;
			v[7] = 8.0;
			v[8] = 9.0;
			v[9] = 10.0;
			v[10] = 11.0;
			v[11] = 12.0;
			v[12] = 13.0;
			v[13] = 14.0;
			v[14] = 15.0;
			v[15] = 16.0;

			kn::Matrix4x4f m(v,true);
			TS_ASSERT( m.rows() == 4 );
			TS_ASSERT( m.columns() == 4 );
			for(unsigned int i = 0; i < m.rows(); ++i){
				for(unsigned int j = 0; j < m.columns(); ++j){
					TS_ASSERT( m[i][j] == v[i*m.columns()+j]);
					TS_ASSERT( m[i][j] != 0.0);
				}
			}

			kn::Matrix4x4f m2(v,false);
			TS_ASSERT( m.rows() == 4 );
			TS_ASSERT( m.columns() == 4 );
			for(unsigned int i = 0; i < m.rows(); ++i){
				for(unsigned int j = 0; j < m.columns(); ++j){
					TS_ASSERT( m2[i][j] == v[j*m.rows()+i]);
					TS_ASSERT( m[i][j] != 0.0);
				}
			}
		}


		void testOperatorTranspose( void ) {

			kn::Matrix4x4f m1(0.0);
			m1[0][0] = 1.0;	m1[0][1] = 2.0;	  m1[0][2] = 3.0;	m1[0][3] = 4.0;
			m1[1][0] = 5.0;	m1[1][1] = 6.0;	  m1[1][2] = 7.0;	m1[1][3] = 8.0;
			m1[2][0] = 9.0;	m1[2][1] = 10.0;  m1[2][2] = 11.0;	m1[2][3] = 12.0;
			m1[3][0] = 13.0;	m1[3][1] = 14.0;  m1[3][2] = 15.0;	m1[3][3] = 16.0;

			kn::Matrix4x4f m2(0.0);
			m2[0][0] = 1.0;	m2[0][1] = 5.0;	  m2[0][2] = 9.0;	m2[0][3] = 13.0;
			m2[1][0] = 2.0;	m2[1][1] = 6.0;	  m2[1][2] = 10.0;	m2[1][3] = 14.0;
			m2[2][0] = 3.0;	m2[2][1] = 7.0;	  m2[2][2] = 11.0;	m2[2][3] = 15.0;
			m2[3][0] = 4.0;	m2[3][1] = 8.0;	  m2[3][2] = 12.0;	m2[3][3] = 16.0;

			m1.transpose();

			TS_ASSERT( m1 == m2);

			kn::Matrix4x4f m3(0.0);
			m3[0][0] = 1.0;	m3[0][1] = 2.0;	  m3[0][2] = 3.0;	m3[0][3] = 4.0;
			m3[1][0] = 5.0;	m3[1][1] = 6.0;	  m3[1][2] = 7.0;	m3[1][3] = 8.0;
			m3[2][0] = 9.0;	m3[2][1] = 10.0;  m3[2][2] = 11.0;	m3[2][3] = 12.0;
			m3[3][0] = 13.0;	m3[3][1] = 14.0;  m3[3][2] = 15.0;	m3[3][3] = 16.0;

			TS_ASSERT( m3.getTranspose() == m2);
		}

		void testOperatorIdentity( void ) {

			kn::Matrix4x4f m1(0.0f);

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


		// Operator	 Matrix * Vector
		void testOperatorTimesVectorDynamic( void ) {
			kn::Matrix4x4f m(2.0);
			kn::Vector<float,kn::DynamicStorePolicy<float> > v(4);
			v.fill(2.0f);
			kn::Vector<float,kn::DynamicStorePolicy<float> > r(4);

			r = m * v;

			for(unsigned int i = 0; i < r.size(); ++i){
				TS_ASSERT( r[i] == 16.0);
			}
		}

		// Operator	 Matrix * Vector
		void testOperatorTimesVectorStatic( void ) {
			kn::Matrix4x4f m(2.0);
			kn::Vector<float,kn::StaticStorePolicy<float,4> > v;
			v.fill(2.0f);
			kn::Vector<float,kn::StaticStorePolicy<float,4> > r;
			
			r = m * v;
			
			for(unsigned int i = 0; i < r.size(); ++i){
				TS_ASSERT( r[i] == 16.0);
			}
			
		}



		// Operator Vector * Matrix
		void testOperatorVectorTimesMatrix4x4( void ) {

			kn::Matrix4x4f m(2.0);
			kn::Vector<float> v((unsigned int)4,2.0f);
			kn::Vector<float> r(4);

			r = v * m;

			for(unsigned int i = 0; i < r.size(); ++i){
				TS_ASSERT( r[i] == 16.0);
			}
		}

		// Operator Vector * Matrix
		void testOperatorVector4TimesMatrix4x4( void ) {
			kn::Matrix4x4f m(2.0);
			kn::Vector<float,kn::StaticStorePolicy<float,4> > v;
			v.fill(2.0f);
			kn::Vector<float,kn::StaticStorePolicy<float,4> > r;

			r = v * m;

			for(unsigned int i = 0; i < r.size(); ++i){
				TS_ASSERT( r[i] == 16.0);
			}
		}

		// Operator =
		void testOperatorAssign( void ) {
			kn::Matrix4x4<float> m1(0.0);
			kn::Matrix4x4<float> m2(1.0);
			m1 = m2;
			for(unsigned int i = 0; i < 4; ++i){
				for(unsigned int j = 0; j < 4; ++j){
					TS_ASSERT( m1[i][j] == 1.0);
				}
			}
		}

		// Operator +
		void testOperatorPlus( void ) {
			kn::Matrix4x4f m0(0.0);
			kn::Matrix4x4f m1(1.0);
			kn::Matrix4x4f m2(1.0);


			m0 = m1 + m2;
			for(unsigned int i = 0; i < 4; ++i){
				for(unsigned int j = 0; j < 4; ++j){
					TS_ASSERT( m0[i][j] == 2.0);
				}
			}

			m1 += m2;
			for(unsigned int i = 0; i < 4; ++i){
				for(unsigned int j = 0; j < 4; ++j){
					TS_ASSERT( m1[i][j] == 2.0);
				}
			}
		}

		// Operator -
		void testOperatorSubtract( void ) {
			kn::Matrix4x4f m0(0.0);
			kn::Matrix4x4f m1(3.0);
			kn::Matrix4x4f m2(2.0);
			m0 = m1 - m2;
			for(unsigned int i = 0; i < 4; ++i){
				for(unsigned int j = 0; j < 4; ++j){
					TS_ASSERT( m0[i][j] == 1.0);
				}
			}

			m1 -= m2;
			for(unsigned int i = 0; i < 4; ++i){
				for(unsigned int j = 0; j < 4; ++j){
					TS_ASSERT( m1[i][j] == 1.0);
				}
			}
		}

		// Operator /
		void testOperatorDivide( void ) {
			kn::Matrix4x4f m0(2.0);
			kn::Matrix4x4f m1(2.0);

			m0 = m1 / 2.0;
			for(unsigned int i = 0; i < 4; ++i){
				for(unsigned int j = 0; j < 4; ++j){
					TS_ASSERT( m0[i][j] == 1.0);
				}
			}

			m1 /= 2.0;
			for(unsigned int i = 0; i < 4; ++i){
				for(unsigned int j = 0; j < 4; ++j){
					TS_ASSERT( m1[i][j] == 1.0);
				}
			}
		}

		// Operator *
		void testOperatorTimes( void ) {
			kn::Matrix4x4f m1(2.0);
			kn::Matrix4x4f m2(2.0);

			kn::Matrix4x4f m0(m1 * m2);

			for(unsigned int i = 0; i < 4; ++i){
				for(unsigned int j = 0; j < 4; ++j){
					TS_ASSERT( m0[i][j] == 16.0);
				}
			}

			kn::Matrix4x4f m3(2.0);
			kn::Matrix4x4f m4(2.0);

			m3 *= m4;

			for(unsigned int i = 0; i < 4; ++i){
				for(unsigned int j = 0; j < 4; ++j){
					TS_ASSERT( m3[i][j] == 16.0);
				}
			}

			m3 = m4 * 6.0;

			for(unsigned int i = 0; i < 4; ++i){
				for(unsigned int j = 0; j < 4; ++j){
					TS_ASSERT( m3[i][j] == 12.0);
				}
			}

			m4 *= 6.0;

			for(unsigned int i = 0; i < 4; ++i){
				for(unsigned int j = 0; j < 4; ++j){
					TS_ASSERT( m4[i][j] == 12.0);
				}
			}

			kn::Vector4f v0;
			v0.fill(2.0f);
			kn::Vector4f v1(m1*v0);
			for(unsigned int j = 0; j < 4; ++j){
				TS_ASSERT( v1[j] == 16.0);
			}
		}

		// Operator -
		void testOperatorMinus( void ) {

			kn::Matrix4x4f m1(2.0);
			kn::Matrix4x4f m2(-m1);

			for(unsigned int i = 0; i < 4; ++i){
				for(unsigned int j = 0; j < 4; ++j){
					TS_ASSERT( m2[i][j] == -m1[i][j]);
				}
			}
		}

		// Operator  d * Matrix
		void testOperatorScalarTimesMatrix( void ) {

				kn::Matrix4x4f m(2.0f);

				m = 2.0f*m;

				for(unsigned int i = 0; i < m.rows(); ++i){
						for(unsigned int j = 0; j < m.columns(); ++j){
								TS_ASSERT( m[i][j] == 4.0);
						}
				}
		}

	void testPower( void ) {
		kn::Matrix4x4f m(0.0f);
		m[0][0]=0;
		m[1][1]=1;
		m[2][2]=2;
		m[3][3]=3;

		m.power(3);

		for(unsigned int i = 0; i < m.rows(); ++i){
			for(unsigned int j = 0; j < m.columns(); ++j){
				if(i==j){ TS_ASSERT( m[i][j] == i*i*i);}
				else{ TS_ASSERT( m[i][j] == 0);}
			}
		}
	}

	void testGetDiagonal( void ) {

		kn::Matrix4x4f m(1.0f);
		for(unsigned int i = 0; i < m.rows(); ++i){
			m[i][1] = i+1.0f;
		}
		kn::Vector<float,kn::StaticStorePolicy<float,4> > v(m.getDiagonal());

		for(unsigned int i = 0; i < m.rows(); ++i){
			TS_ASSERT(m[i][i] == v[i]);
		}
	}


	void testGetRow( void ) {
		kn::Matrix4x4f m(1.0f);
		for(unsigned int i = 0; i < 4; ++i){
			m[1][i] = i+1.0f;
		}
		kn::Vector<float,kn::StaticStorePolicy<float,4> > v(m.getRow(1));

		TS_ASSERT( v.size() == 4);

		for(unsigned int i = 0; i < 4; ++i){
			TS_ASSERT(m[1][i] == v[i]);
		}
	}

	void testGetColumn( void ) {
		kn::Matrix4x4f m(1.0f);
		for(unsigned int i = 0; i < 4; ++i){
			m[i][1] = i+1.0f;
		}
		kn::Vector<float,kn::StaticStorePolicy<float,4> > v(m.getColumn(1));

		TS_ASSERT( v.size() == 4);

		for(unsigned int i = 0; i < 4; ++i){
			TS_ASSERT(m[i][1] == v[i]);
		}
	}


	void testTrace( void ) {
		float tab[16] = {16.0,15.0,14.0,13.0,
											12.0,11.0,10.0,9.0,
											8.0,7.0,6.0,5.0,
											4.0,3.0,2.0,1.0};
		kn::Matrix4x4f m(tab);

		TS_ASSERT(m.trace() == 34.0);
	}


};

/*
 * End of Anti-doublon
 */

#endif
