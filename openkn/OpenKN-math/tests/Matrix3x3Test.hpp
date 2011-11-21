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
#ifndef __OPENKN_MATH__MATRIX3X3TEST_HPP__
#define __OPENKN_MATH__MATRIX3X3TEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/math/Matrix3x3.hpp>
#include <OpenKN/math/Vector3.hpp>

/*
 * Class definition
 */

class Matrix3x3Test : public CxxTest::TestSuite {
	public:
		void testConstructor( void ) {
			kn::Matrix3x3f *m = 0;
			m = new kn::Matrix3x3f();
			TS_ASSERT( m != 0 );
			TS_ASSERT( m->rows() == 3 );
			TS_ASSERT( m->columns() == 3 );
			delete m;
		}

		void testConstructorWithValue( void ) {
			kn::Matrix3x3f *m = 0;
			m = new kn::Matrix3x3f(2.1f);
			TS_ASSERT( m != 0 );
			TS_ASSERT( m->rows() == 3 );
			TS_ASSERT( m->columns() == 3 );
			for(unsigned int i = 0; i < m->rows(); ++i){
				for(unsigned int j = 0; j < m->columns(); ++j){
					TS_ASSERT( (*m)[i][j] == 2.1f);
				}
			}
			delete m;
		}

		void testCopyConstructor( void ) {
			kn::Matrix3x3f m(2.1f);
			kn::Matrix3x3f m2(m);
			TS_ASSERT( m2.rows() == m.rows() );
			TS_ASSERT( m2.columns() == m.columns() );
			for(unsigned int i = 0; i < m.rows(); ++i){
				for(unsigned int j = 0; j < m.columns(); ++j){
					TS_ASSERT( m2[i][j] == 2.1f);
				}
			}
		}

		void testCopyPointerConstructor( void ) {
			kn::Matrix3x3f *m = new kn::Matrix3x3f(2.1f);
			kn::Matrix3x3f m2(m);
			TS_ASSERT( m2.rows() == m->rows() );
			TS_ASSERT( m2.columns() == m->columns() );
			for(unsigned int i = 0; i < m->rows(); ++i){
				for(unsigned int j = 0; j < m->columns(); ++j){
					TS_ASSERT( m2[i][j] == 2.1f);
				}
			}
		}

		void testConstructorWithAnArray( void ) {
			float tab[9] = {9.1f,8.0f,7.0f,
				6.0f,5.0f,4.0f,3.0f,2.0f,1.0f};
			kn::Matrix3x3f m(tab);
			TS_ASSERT( m.rows() == 3 );
			TS_ASSERT( m.columns() == 3 );
			for(unsigned int i = 0; i < m.rows(); ++i){
				for(unsigned int j = 0; j < m.columns(); ++j){
					TS_ASSERT( m[i][j] == tab[i*m.columns()+j]);
					TS_ASSERT( m[i][j] != 0.0);
				}
			}
		}

		void testConstructorWithVector( void ) {
			kn::Vectorf v(9);
			v[0] = 1.0f;
			v[1] = 2.0f;
			v[2] = 3.0f;
			v[3] = 4.0f;
			v[4] = 5.0f;
			v[5] = 6.0f;
			v[6] = 7.0f;
			v[7] = 8.0f;
			v[8] = 9.1f;

			kn::Matrix3x3f m(v,true);
			TS_ASSERT( m.rows() == 3 );
			TS_ASSERT( m.columns() == 3 );
			for(unsigned int i = 0; i < m.rows(); ++i){
				for(unsigned int j = 0; j < m.columns(); ++j){
					TS_ASSERT( m[i][j] == v[i*m.columns()+j]);
					TS_ASSERT( m[i][j] != 0.0);
				}
			}

			kn::Matrix3x3f m2(v,false);
			TS_ASSERT( m.rows() == 3 );
			TS_ASSERT( m.columns() == 3 );
			for(unsigned int i = 0; i < m.rows(); ++i){
				for(unsigned int j = 0; j < m.columns(); ++j){
					TS_ASSERT( m2[i][j] == v[j*m.rows()+i]);
					TS_ASSERT( m[i][j] != 0.0);
				}
			}
		}

		void testConstructorWithMatrix( void ) {
			kn::Matrixf *m = 0;
			m = new kn::Matrixf(3,3,2.0);
			kn::Matrix3x3f *m2 = new kn::Matrix3x3f(m);
			TS_ASSERT( m2 != 0 );
			TS_ASSERT( m2->rows() == 3 );
			TS_ASSERT( m2->columns() == 3 );
			for(unsigned int i = 0; i < m2->rows(); ++i){
				for(unsigned int j = 0; j < m2->columns(); ++j){
					TS_ASSERT( (*m2)[i][j] == (*m)[i][j]);
				}
			}
			delete m;
			delete m2;

			kn::Matrixf *m3 = new kn::Matrixf(5,3,2.0);
			TS_ASSERT_THROWS(new kn::Matrix3x3f(m3),kn::MathException);
			delete m3;
		}


		void testOperatorTranspose( void ) {

			kn::Matrix3x3f m1(0.0);
			m1[0][0] = 1.0f; m1[0][1] = 2.0f; m1[0][2] = 3.0f;
			m1[1][0] = 4.0f; m1[1][1] = 5.0f; m1[1][2] = 6.0f;
			m1[2][0] = 7.0f; m1[2][1] = 8.0f; m1[2][2] = 9.1f;

			kn::Matrix3x3f m2(0.0);
			m2[0][0] = 1.0f; m2[0][1] = 4.0f; m2[0][2] = 7.0f;
			m2[1][0] = 2.0f; m2[1][1] = 5.0f; m2[1][2] = 8.0f;
			m2[2][0] = 3.0f; m2[2][1] = 6.0f; m2[2][2] = 9.1f;

			m1.transpose();

			TS_ASSERT( m1 == m2);

			kn::Matrix3x3f m3(0.0);
			m3[0][0] = 1.0f; m3[0][1] = 2.0f; m3[0][2] = 3.0f;
			m3[1][0] = 4.0f; m3[1][1] = 5.0f; m3[1][2] = 6.0f;
			m3[2][0] = 7.0f; m3[2][1] = 8.0f; m3[2][2] = 9.1f;

			TS_ASSERT( m3.getTranspose() == m2);
		}

		void testOperatorIdentity( void ) {

			kn::Matrix3x3f m1(0.0f);

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

		// Operator  Matrix * Vector
		void testOperatorTimesVectorStatic( void ) {

			kn::Matrix3x3f m(2.0);
			kn::Vector<float,kn::StaticStorePolicy<float,3> > v;
			v.fill(2.0f);
			kn::Vector<float,kn::StaticStorePolicy<float,3> > r;

			//std::cerr<<"Checking static ...";std::cerr.flush();
			r = m * v;
			//std::cerr<<"... End !"<<std::endl;
			
			for(unsigned int i = 0; i < r.size(); ++i){
				TS_ASSERT( r[i] == 12.0);
			}
		}

		// Operator  Matrix * Vector
		void testOperatorTimesVectorDynamic( void ) {

			kn::Matrix3x3f m(2.0);
			kn::Vector<float,kn::DynamicStorePolicy<float> > v(3);
			v.fill(2.0f);
			kn::Vector<float,kn::DynamicStorePolicy<float> > r(3);

			//std::cerr<<"Checking dynamic ...";std::cerr.flush();
			r = m * v;
			//std::cerr<<"... End !"<<std::endl;
			
			for(unsigned int i = 0; i < r.size(); ++i){
				TS_ASSERT( r[i] == 12.0);
			}
		}

		// Operator Vector * Matrix
		void testOperatorVectorStaticTimesMatrix3x3( void ) {

			kn::Matrix3x3f m(2.0);
			kn::Vector<float,kn::StaticStorePolicy<float,3> > v;
			v.fill(2.0f);
			kn::Vector<float,kn::StaticStorePolicy<float,3> > r;

			//std::cerr<<"Checking vector * Matrix static ...";std::cerr.flush();
			r = v * m;
			//std::cerr<<"... End !"<<std::endl;
			
			for(unsigned int i = 0; i < r.size(); ++i){
				TS_ASSERT( r[i] == 12.0);
			}
		}

		// Operator Vector * Matrix
		void testOperatorVectorDynamicTimesMatrix3x3( void ) {

			kn::Matrix3x3f m(2.0);
			kn::Vector<float,kn::DynamicStorePolicy<float> > v(3);
			v.fill(2.0f);
			kn::Vector<float,kn::DynamicStorePolicy<float> > r(3);

			//std::cerr<<"Checking vector * Matrix dyn ...";std::cerr.flush();
			r = v * m;
			//std::cerr<<"... End !"<<std::endl;

			for(unsigned int i = 0; i < r.size(); ++i){
				TS_ASSERT( r[i] == 12.0);
			}
		}


		// Operator =
		void testOperatorAssign( void ) {

			kn::Matrix3x3f m1(0.0);
			kn::Matrix3x3f m2(1.0);
			m1 = m2;
			for(unsigned int i = 0; i < 3; ++i){
				for(unsigned int j = 0; j < 3; ++j){
					TS_ASSERT( m1[i][j] == 1.0);
				}
			}
		}

		// Operator +
		void testOperatorPlus( void ) {

			kn::Matrix3x3f m0(0.0);
			kn::Matrix3x3f m1(1.0);
			kn::Matrix3x3f m2(1.0);


			m0 = m1 + m2;
			for(unsigned int i = 0; i < 3;++i){
				for(unsigned int j = 0; j < 3; ++j){
					TS_ASSERT( m0[i][j] == 2.0);
				}
			}

			m1 += m2;
			for(unsigned int i = 0; i < 3; ++i){
				for(unsigned int j = 0; j < 3; ++j){
					TS_ASSERT( m1[i][j] == 2.0);
				}
			}

		}

		// Operator -
		void testOperatorSubtract( void ) {

			kn::Matrix3x3f m0(0.0);
			kn::Matrix3x3f m1(3.0);
			kn::Matrix3x3f m2(2.0);
			m0 = m1 - m2;
			for(unsigned int i = 0; i < 3; ++i){
				for(unsigned int j = 0; j < 3; ++j){
					TS_ASSERT( m0[i][j] == 1.0);
				}
			}

			m1 -= m2;
			for(unsigned int i = 0; i < 3; ++i){
				for(unsigned int j = 0; j < 3; ++j){
					TS_ASSERT( m1[i][j] == 1.0);
				}
			}

		}

		// Operator /
		void testOperatorDivide( void ) {

			kn::Matrix3x3f m0(2.0);
			kn::Matrix3x3f m1(2.0);

			m0 = m1 / 2.0;
			for(unsigned int i = 0; i < 3; ++i){
				for(unsigned int j = 0; j < 3; ++j){
					TS_ASSERT( m0[i][j] == 1.0);
				}
			}

			m1 /= 2.0;
			for(unsigned int i = 0; i < 3; ++i){
				for(unsigned int j = 0; j < 3; ++j){
					TS_ASSERT( m1[i][j] == 1.0);
				}
			}

		}

		// Operator *
		void testOperatorTimes( void ) {

			kn::Matrix3x3f m1(2.0);
			kn::Matrix3x3f m2(2.0);

			kn::Matrix3x3f m0(m1 * m2);

			for(unsigned int i = 0; i < 3; ++i){
				for(unsigned int j = 0; j < 3; ++j){
					TS_ASSERT( m0[i][j] == 12.0);
				}
			}

			kn::Matrix3x3f m3(2.0);
			kn::Matrix3x3f m4(2.0);

			m3 *= m4;

			for(unsigned int i = 0; i < 3; ++i){
				for(unsigned int j = 0; j < 3; ++j){
					TS_ASSERT( m3[i][j] == 12.0);
				}
			}

			m3 = m4 * 6.0;

			for(unsigned int i = 0; i < 3; ++i){
				for(unsigned int j = 0; j < 3; ++j){
					TS_ASSERT( m3[i][j] == 12.0);
				}
			}

			m4 *= 6.0;

			for(unsigned int i = 0; i < 3; ++i){
				for(unsigned int j = 0; j < 3; ++j){
					TS_ASSERT( m4[i][j] == 12.0);
				}
			}

			kn::Vector3f v0;
			v0.fill(2.0);
			kn::Vector3f v1(m1*v0);
			for(unsigned int j = 0; j < 3; ++j){
				TS_ASSERT( v1[j] == 12.0);
			}

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

		// Operator  d * Matrix
		void testOperatorScalarTimesMatrix( void ) {

				kn::Matrix3x3f m(2.0f);

				m = 2.0f*m;

				for(unsigned int i = 0; i < m.rows(); ++i){
						for(unsigned int j = 0; j < m.columns(); ++j){
								TS_ASSERT( m[i][j] == 4.0);
						}
				}
		}

		// cross3x3
		void testCross3x3( void ) {
			kn::Vector3d v1;
			v1[0] = 1.0;
			v1[1] = 0.0;
			v1[2] = 5.0;

			kn::Vector3d v2;
			v2[0] =  0.0;
			v2[1] =  1.0;
			v2[2] =  5.0;

			kn::Matrix3x3d m;
			m.cross3x3(v1);

			kn::Vector3d v3(m*v2);
			kn::Vector3d v4(v1^v2);

			for(unsigned int i = 0; i < 3; ++i){
				TS_ASSERT_EQUALS(v3[i],v4[i]);
			}
		}

		void testPower( void ) {
			kn::Matrix3x3f m(0.0f);
			m[0][0]=0;
			m[1][1]=1;
			m[2][2]=2;

			m.power(3);

			for(unsigned int i = 0; i < m.rows(); ++i){
				for(unsigned int j = 0; j < m.columns(); ++j){
						if(i==j){ TS_ASSERT( m[i][j] == i*i*i);}
						else{ TS_ASSERT( m[i][j] == 0);}
				}
			}
		}

		void testGetDiagonal( void ) {

			kn::Matrix3x3f m(1.0f);
			for(unsigned int i = 0; i < m.rows(); ++i){
				m[i][1] = i+1.0f;
			}
			kn::Vector<float,kn::StaticStorePolicy<float,3> > v(m.getDiagonal());

			for(unsigned int i = 0; i < m.rows(); ++i){
				TS_ASSERT(m[i][i] == v[i]);
			}
		}


		void testGetRow( void ) {
			kn::Matrix3x3f m(1.0f);
			for(unsigned int i = 0; i < 3; ++i){
				m[1][i] = i+1.0f;
			}
			kn::Vector<float,kn::StaticStorePolicy<float,3> > v(m.getRow(1));

			TS_ASSERT( v.size() == 3);

			for(unsigned int i = 0; i < 3; ++i){
				TS_ASSERT(m[1][i] == v[i]);
			}
		}

		void testGetColumn( void ) {
			kn::Matrix3x3f m(1.0f);
			for(unsigned int i = 0; i < 3; ++i){
				m[i][1] = i+1.0f;
			}
			kn::Vector<float,kn::StaticStorePolicy<float,3> > v(m.getColumn(1));

			TS_ASSERT( v.size() == 3);

			for(unsigned int i = 0; i < 3; ++i){
				TS_ASSERT(m[i][1] == v[i]);
			}
		}


		void testTrace( void ) {
			float tab[16] = {9.0,8.0,7.0,
											6.0,5.0,4.0,
											3.0,2.0,1.0};
			kn::Matrix3x3f m(tab);

			TS_ASSERT(m.trace() == 15.0);
		}

};

/*
 * End of Anti-doublon
 */

#endif
