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
 * MERCHANTABILITY or FITNESS FOR Age PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_MATH__VECTOR2TEST_HPP__
#define __OPENKN_MATH__VECTOR2TEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/math/Vector2.hpp>

/*
 * Class definition
 */
class Vector2Test: public CxxTest::TestSuite{
public:

	void testConstructorWithoutParameter(void){
		kn::Vector2<int> *v;
		v=new kn::Vector2<int>();
		TS_ASSERT(v!=0);
		TS_ASSERT(v->size()==2);
		TS_ASSERT((*v)[0]==0
				  && (*v)[1]==0);
		delete v;
	}

	void testCopyConstructor(void){
		kn::Vector2<int> v1;
		v1[0]=2; v1[1]=-9;
		kn::Vector2<int> v2(v1);
		TS_ASSERT(v2.size()==v1.size());
		TS_ASSERT(v2[0]==2
				  && v2[1]==-9);
	}

	void testCopyPointerConstructor(void){
		kn::Vector2<int> *v1=new kn::Vector2<int>();
		(*v1)[0]=7; (*v1)[1]=25;
		kn::Vector2<int> v2(v1);
		TS_ASSERT(v2.size()==v1->size());
		TS_ASSERT(v2[0]==7
				  && v2[1]==25);
		delete v1;
	}

	void testConstructorWithTwoParameters(void){
		kn::Vector2<float> v(-12.0, 65.0);
		TS_ASSERT(v.size()==2);
		TS_ASSERT(v[0]==-12.0f
				  && v[1]==65.0f);
	}

	void testConstructorWithOneParameter(void){
		kn::Vector2<float> v(-87.574f);
		TS_ASSERT(v.size()==2);
		for(unsigned int i=0; i<v.size(); i++){
			TS_ASSERT(v[i]==-87.574f);
		}
	}

	void testConstructorWithAnArray(void){
		int tab[5]={-10, 6, 8, 124, -2};
		kn::Vector2<int> v(tab);
		TS_ASSERT(v.size()==2);
		for(unsigned int i=0; i<v.size(); i++){
			TS_ASSERT(v[i]==tab[i]);
			TS_ASSERT(v[i]!=0);
		}
	}

	void testConstructorWithAVector(void){
		kn::Vector<int> v1(2);
		v1[0]=-10; v1[1]=6;
		TS_ASSERT(v1.size()==2);
		kn::Vector2<int> v2(v1);
		TS_ASSERT(v2.size()==2);
		for(unsigned int i=0; i<v2.size(); i++){
			TS_ASSERT(v2[i]==v1[i]);
		}
	}

	void testAccessor(void){
		kn::Vector2<float> v1(1.0f),v2(2.2f);
		TS_ASSERT(v1.size()==2 && v2.size()==2 );

		v1.x()=v2.x();
		v1.y()=v2.y();
		TS_ASSERT(v1[0]== 2.2f && v1[1]== 2.2f);

		v2.x()=1.1f;
		v2.y()=2.2f;
		TS_ASSERT(v2[0]== 1.1f && v2[1]== 2.2f);
	}

	void testOperatorAffect(void){
		kn::Vector2<int>	v1;
		kn::Vector<int>	v2(2);
		v1[0]=12; v1[1]=65;
		v2[0]=7; v2[1]=-10;
		v1=v2;
		TS_ASSERT(v1[0]== 7 && v1[1]== -10);
	}


	void testOperatorMultiplyByVector(void){
		kn::Vector2<int>	v1;
		kn::Vector<int>	v2(2);
		v1[0]=12; v1[1]=65;
		v2[0]=7; v2[1]=-10;
		TS_ASSERT(v1*v2==-566);
	}

	void testOperatorMultiplyByVector2(void){
		kn::Vector2<int>	v1,v2;
		v1[0]=12; v1[1]=65;
		v2[0]=7; v2[1]=-10;
		TS_ASSERT(v1*v2==-566);
	}


	void testOperatorAddVector2(void){
		kn::Vector2<int>	v1,v2,v3;
		v1[0]=12; v1[1]=65;
		v2[0]=7; v2[1]=-10;
		v3 = v1 + v2;
		TS_ASSERT(v3[0]==19 && v3[1]==55);
	}

	void testOperatorMinusVector(void){
		kn::Vector2<int>	v1;
		kn::Vector<int>	v2(2);
		kn::Vector<int>	v3(2);
		v1[0]=12; v1[1]=65;
		v2[0]=7; v2[1]=-10;
		v3 = v1 - v2;
		TS_ASSERT(v3[0]==5 && v3[1]==75);
	}

	void testOperatorMinusVector2(void){
		kn::Vector2<int>	v1,v2,v3;
		v1[0]=12; v1[1]=65;
		v2[0]=7; v2[1]=-10;
		v3 = v1 - v2;
		TS_ASSERT(v3[0]==5 && v3[1]==75);
	}

	void testOperatorDivideVector(void){
		kn::Vector2<int>	v1;
		kn::Vector<int>	v2(2);
		v1[0]=12; v1[1]=66;
		v2 = v1 / 2;
		TS_ASSERT(v2[0]==6 && v2[1]==33);
	}

	void testOperatorDivideVector2(void){
		kn::Vector2<int>	v1,v2;
		v1[0]=12; v1[1]=66;
		v2 = v1 / 2;
		TS_ASSERT(v2[0]==6 && v2[1]==33);
	}

	void testOperatorMultipleVector(void){
		kn::Vector2<int>	v1;
		kn::Vector<int>	v2(2);
		v1[0]=12; v1[1]=66;
		v2 = v1 * 2;
		TS_ASSERT(v2[0]==24 && v2[1]==132);
	}

	void testOperatorMultipleVector2(void){
		kn::Vector2<int>	v1,v2;
		v1[0]=12; v1[1]=66;
		v2 = v1 * 2;
		TS_ASSERT(v2[0]==24 && v2[1]==132);
	}

	void testOperatorNegateVector(void){
		kn::Vector2<int>	v1;
		kn::Vector<int>	v2(2);
		v1[0]=12; v1[1]=66;
		v2 = -v1;
		TS_ASSERT(v2[0]==-12 && v2[1]==-66);
	}

	void testOperatorNegateVector2(void){
		kn::Vector2<int>	v1,v2;
		v1[0]=12; v1[1]=66;
		v2 = -v1;
		TS_ASSERT(v2[0]==-12 && v2[1]==-66);
	}

	void testOperatorAddInPlaceVector(void){
		kn::Vector2<int>	v1;
		kn::Vector<int>	v2(2);
		v1[0]=12; v1[1]=65;
		v2[0]=7; v2[1]=-10;
		v1 += v2;
		TS_ASSERT(v1[0]==19 && v1[1]==55);
	}

	void testOperatorAddInPlaceVector2(void){
		kn::Vector2<int>	v1,v2;
		v1[0]=12; v1[1]=65;
		v2[0]=7; v2[1]=-10;
		v1 += v2;
		TS_ASSERT(v1[0]==19 && v1[1]==55);
	}

	void testOperatorMinusInPlaceVector(void){
		kn::Vector2<int>	v1;
		kn::Vector<int>	v2(2);
		v1[0]=12; v1[1]=65;
		v2[0]=7; v2[1]=-10;
		v1 -= v2;
		TS_ASSERT(v1[0]==5 && v1[1]==75);
	}

	void testOperatorMinusInPlaceVector2(void){
		kn::Vector2<int>	v1,v2;
		v1[0]=12; v1[1]=65;
		v2[0]=7; v2[1]=-10;
		v1 -= v2;
		TS_ASSERT(v1[0]==5 && v1[1]==75);
	}

	void testOperatorDivideInPlaceVector2(void){
		kn::Vector2<int>	v1;
		v1[0]=12; v1[1]=66;
		v1 /= 2;
		TS_ASSERT(v1[0]==6 && v1[1]==33);
	}
	void testOperatorMultipleInPlaceVector2(void){
		kn::Vector2<int>	v1;
		v1[0]=12; v1[1]=66;
		v1 *= 2;
		TS_ASSERT(v1[0]==24 && v1[1]==132);
	}

	void testOperatorMultiplyScalarByVector2(void){
		kn::Vector2<int> v;
		v[0]=12; v[1]=65;
		v = 2*v;
		TS_ASSERT(v[0]==24 && v[1]==130);
	}

	void testNormalize(void){
		kn::Vector2<double> v;
		v[0]=3.0; v[1]=4.0;
		v.normalize();
		TS_ASSERT(v[0]==3.0/5.0 &&
			  v[1]==4.0/5.0);
		TS_ASSERT(v.getNorm() == 1.0);
	}

	void testGetNormalize(void){
		kn::Vector2<double> v;
		v[0]=3.0; v[1]=4.0;
		kn::Vector2<double> v1 = v.getNormalized();
		TS_ASSERT(v1[0]==3.0/5.0 &&
			  v1[1]==4.0/5.0);
		TS_ASSERT(v1.getNorm() == 1.0);
	}

};

/*
 * End of Anti-doublon
 */
#endif

