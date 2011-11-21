/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * Vector3Test.hpp created in 10 2008.
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
#ifndef __OPENKN_MATH__VECTOR3TEST_HPP__
#define __OPENKN_MATH__VECTOR3TEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/math/Vector3.hpp>

/*
 * Class definition
 */
class Vector3Test: public CxxTest::TestSuite{
public:

	void testConstructorWithoutParameter(void){
		kn::Vector3<int> *v;
		v=new kn::Vector3<int>();
		TS_ASSERT(v!=0);
		TS_ASSERT(v->size()==3);
		TS_ASSERT((*v)[0]==0
				  && (*v)[1]==0
				  && (*v)[2]==0);
		delete v;
	}

	void testCopyConstructor(void){
		kn::Vector3<int> v1;
		v1[0]=2; v1[1]=-9; v1[2]=4;
		kn::Vector3<int> v2(v1);
		TS_ASSERT(v2.size()==v1.size());
		TS_ASSERT(v2[0]==2
				  && v2[1]==-9
				  && v2[2]==4);
	}

	void testCopyPointerConstructor(void){
		kn::Vector3<int> *v1=new kn::Vector3<int>();
		(*v1)[0]=7; (*v1)[1]=25; (*v1)[2]=-144;
		kn::Vector3<int> v2(v1);
		TS_ASSERT(v2.size()==v1->size());
		TS_ASSERT(v2[0]==7
				  && v2[1]==25
				  && v2[2]==-144);
		delete v1;
	}

	void testConstructorWithAnArray(void){
		int tab[5]={-10, 6, 8, 124, -2};
		kn::Vector3<int> v(tab);
		TS_ASSERT(v.size()==3);
		for(unsigned int i=0; i<v.size(); i++){
			TS_ASSERT(v[i]==tab[i]);
			TS_ASSERT(v[i]!=0);
		}
	}

	void testConstructorWithOneParameter(void){
		kn::Vector3<float> v(-87.574f);
		TS_ASSERT(v.size()==3);
		for(unsigned int i=0; i<v.size(); i++){
			TS_ASSERT(v[i]==-87.574f);
		}
	}

	void testConstructorWithVector2Value(void){
		kn::Vector2<int> v(2,3);
		kn::Vector3<int> v1(v,4);
		TS_ASSERT(v1.size()==3);
		TS_ASSERT(v1[0]== 2 && v1[1]== 3 && v1[2]== 4);
	}

	void testConstructorWithValueVector2(void){
		kn::Vector2<int> v(2,3);
		kn::Vector3<int> v1(4,v);
		TS_ASSERT(v1.size()==3);
		TS_ASSERT(v1[0]== 4 && v1[1]== 2 && v1[2]== 3);
	}

	void testConstructorWithThreeParameters(void){
		kn::Vector3<int> v1(4,2,3);
		TS_ASSERT(v1.size()==3);
		TS_ASSERT(v1[0]== 4 && v1[1]== 2 && v1[2]== 3);
	}

	void testAccessor(void){
		kn::Vector3<float> v1(1.0f),v2(2.2f);
		TS_ASSERT(v1.size()==3 && v2.size()==3 );

		v1.x()=v2.x();
		v1.y()=v2.y();
		v1.z()=v2.z();
		TS_ASSERT(v1[0]== 2.2f && v1[1]== 2.2f && v1[2]== 2.2f);

		v2.x()=1.1f;
		v2.y()=2.2f;
		v2.z()=3.3f;
		TS_ASSERT(v2[0]== 1.1f && v2[1]== 2.2f && v2[2]== 3.3f);
	}

	void testOperatorAffect(void){
		kn::Vector3<int>	v1;
		kn::Vector<int>	v2(3);
		v1[0]=12; v1[1]=65; v1[2]=139;
		v2[0]=7; v2[1]=-10; v2[2]=-23;
		v1=v2;
		TS_ASSERT(v1[0]== 7 && v1[1]== -10 && v1[2]== -23);
	}


	void testOperatorMultiplyByVector(void){
		kn::Vector3<int>	v1;
		kn::Vector<int>	v2(3);
		v1[0]=12; v1[1]=65; v1[2]=139;
		v2[0]=7; v2[1]=-10; v2[2]=-23;
		TS_ASSERT(v1*v2==-3763);
	}

	void testOperatorMultiplyByVector3(void){
		kn::Vector3<int>	v1,v2;
		v1[0]=12; v1[1]=65; v1[2]=139;
		v2[0]=7; v2[1]=-10; v2[2]=-23;
		TS_ASSERT(v1*v2==-3763);
	}

	void testOperatorAddVector3(void){
		kn::Vector3<int>	v1,v2,v3;
		v1[0]=12; v1[1]=65; v1[2]=139;
		v2[0]=7; v2[1]=-10; v2[2]=-23;
		v3 = v1 + v2;
		TS_ASSERT(v3[0]==19 && v3[1]==55 && v3[2]==116);
	}

	void testOperatorMinusVector(void){
		kn::Vector3<int>	v1;
		kn::Vector<int>	v2(3);
		kn::Vector<int>	v3(3);
		v1[0]=12; v1[1]=65; v1[2]=139;
		v2[0]=7; v2[1]=-10; v2[2]=-23;
		v3 = v1 - v2;
		TS_ASSERT(v3[0]==5 && v3[1]==75 && v3[2]==162);
	}

	void testOperatorMinusVector3(void){
		kn::Vector3<int>	v1,v2,v3;
		v1[0]=12; v1[1]=65; v1[2]=139;
		v2[0]=7; v2[1]=-10; v2[2]=-23;
		v3 = v1 - v2;
		TS_ASSERT(v3[0]==5 && v3[1]==75 && v3[2]==162);
	}

	void testOperatorDivideVector(void){
		kn::Vector3<int>	v1;
		kn::Vector<int>	v2(3);
		v1[0]=12; v1[1]=66; v1[2]=140;
		v2 = v1 / 2;
		TS_ASSERT(v2[0]==6 && v2[1]==33 && v2[2]==70);
	}

	void testOperatorDivideVector3(void){
		kn::Vector3<int>	v1,v2;
		v1[0]=12; v1[1]=66; v1[2]=140;
		v2 = v1 / 2;
		TS_ASSERT(v2[0]==6 && v2[1]==33 && v2[2]==70);
	}

	void testOperatorMultipleVector(void){
		kn::Vector3<int>	v1;
		kn::Vector<int>	v2(3);
		v1[0]=12; v1[1]=66; v1[2]=140;
		v2 = v1 * 2;
		TS_ASSERT(v2[0]==24 && v2[1]==132 && v2[2]==280);
	}

	void testOperatorMultipleVector3(void){
		kn::Vector3<int>	v1,v2;
		v1[0]=12; v1[1]=66; v1[2]=140;
		v2 = v1 * 2;
		TS_ASSERT(v2[0]==24 && v2[1]==132 && v2[2]==280);
	}

	void testOperatorNegateVector(void){
		kn::Vector3<int>	v1;
		kn::Vector<int>	v2(3);
		v1[0]=12; v1[1]=66; v1[2]=140;
		v2 = -v1;
		TS_ASSERT(v2[0]==-12 && v2[1]==-66 && v2[2]==-140);
	}

	void testOperatorNegateVector3(void){
		kn::Vector3<int>	v1,v2;
		v1[0]=12; v1[1]=66; v1[2]=140;
		v2 = -v1;
		TS_ASSERT(v2[0]==-12 && v2[1]==-66 && v2[2]==-140);
	}

	void testOperatorAddInPlaceVector(void){
		kn::Vector3<int>	v1;
		kn::Vector<int>	v2(3);
		v1[0]=12; v1[1]=65; v1[2]=139;
		v2[0]=7; v2[1]=-10; v2[2]=-23;
		v1 += v2;
		TS_ASSERT(v1[0]==19 && v1[1]==55 && v1[2]==116);
	}

	void testOperatorAddInPlaceVector3(void){
		kn::Vector3<int>	v1,v2;
		v1[0]=12; v1[1]=65; v1[2]=139;
		v2[0]=7; v2[1]=-10; v2[2]=-23;
		v1 += v2;
		TS_ASSERT(v1[0]==19 && v1[1]==55 && v1[2]==116);
	}

	void testOperatorMinusInPlaceVector(void){
		kn::Vector3<int>	v1;
		kn::Vector<int>	v2(3);
		v1[0]=12; v1[1]=65; v1[2]=139;
		v2[0]=7; v2[1]=-10; v2[2]=-23;
		v1 -= v2;
		TS_ASSERT(v1[0]==5 && v1[1]==75 && v1[2]==162);
	}

	void testOperatorMinusInPlaceVector3(void){
		kn::Vector3<int>	v1,v2;
		v1[0]=12; v1[1]=65; v1[2]=139;
		v2[0]=7; v2[1]=-10; v2[2]=-23;
		v1 -= v2;
		TS_ASSERT(v1[0]==5 && v1[1]==75 && v1[2]==162);
	}

	void testOperatorDivideInPlaceVector3(void){
		kn::Vector3<int>	v1;
		v1[0]=12; v1[1]=66; v1[2]=140;
		v1 /= 2;
		TS_ASSERT(v1[0]==6 && v1[1]==33 && v1[2]==70);
	}
	void testOperatorMultipleInPlaceVector3(void){
		kn::Vector3<int>	v1;
		v1[0]=12; v1[1]=66; v1[2]=140;
		v1 *= 2;
		TS_ASSERT(v1[0]==24 && v1[1]==132 && v1[2]==280);
	}

	void testOperatorMultiplyScalarByVector3(void){
		kn::Vector3<int> v;
		v[0]=12; v[1]=65; v[2]=139;
		v = 2*v;
		TS_ASSERT(v[0]==24 && v[1]==130 && v[2]==278);
	}

	void testNormalize(void){
		kn::Vector3<double> v;
		v[0]=2.0; v[1]=3.0; v[2]=6.0;
		v.normalize();
		TS_ASSERT_EQUALS(v[0],2.0/7.0);
		TS_ASSERT_EQUALS(v[1],3.0/7.0);
		TS_ASSERT_EQUALS(v[2],6.0/7.0);
		TS_ASSERT_DELTA(v.getNorm(),1.0,0.0001);
	}

	void testGetNormalize(void){
		kn::Vector3<double> v;
		v[0]=2.0; v[1]=3.0; v[2]=6.0;
		kn::Vector3<double> v1 = v.getNormalized();
		TS_ASSERT(v1[0]==2.0/7.0 &&
			  v1[1]==3.0/7.0 &&
			  v1[2]==6.0/7.0);
		TS_ASSERT_DELTA(v1.getNorm(),1.0,0.0001);
	}

	void testCrossProduct(void){
		kn::Vector3<float> v1;
		v1[0]=2.0f; v1[1]=3.0f; v1[2]=6.0f;
		kn::Vector3<float> v2;
		v2[0]=1.0f; v2[1]=2.0f; v2[2]=4.0f;

		kn::Vector3<float> v3(v1^v2);
		TS_ASSERT_EQUALS(v3[0],  0.0f);
		TS_ASSERT_EQUALS(v3[1], -2.0f);
		TS_ASSERT_EQUALS(v3[2],  1.0);

		kn::Vector3<float> v4(v1.cross(v2));
		TS_ASSERT_EQUALS(v3[0],  0.0f);
		TS_ASSERT_EQUALS(v3[1], -2.0f);
		TS_ASSERT_EQUALS(v3[2],  1.0);
	}

	void testDotProduct(void){
		kn::Vector3<float> v1, v2;
		v1[0]=2.0f; v1[1]=3.0f; v1[2]=6.0f;
		v2[0]=1.0f; v2[1]=2.0f; v2[2]=4.0f;

      		TS_ASSERT_EQUALS(v1*v2,32.0f);
      		TS_ASSERT_EQUALS(v1.dot(v2),32.0f);
    	}

	void testFill(void){
		kn::Vector3<double> v;
		v.fill(7.0);
		TS_ASSERT_EQUALS(v[0],7.0);
		TS_ASSERT_EQUALS(v[1],7.0);
		TS_ASSERT_EQUALS(v[2],7.0);
	}

	void testSetZero(void){
		kn::Vector3<double> v;
		v[0]=2.0f; v[1]=3.0f; v[2]=6.0f;
		v.setZero();
		TS_ASSERT_EQUALS(v[0],0.0);
		TS_ASSERT_EQUALS(v[1],0.0);
		TS_ASSERT_EQUALS(v[2],0.0);
	}

};

/*
 * End of Anti-doublon
 */
#endif
