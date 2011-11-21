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
 * You should hve received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_MATH__VECTORTEST_HPP__
#define __OPENKN_MATH__VECTORTEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/math/Vector.hpp>

/*
 * Class definition
 */
class VectorTest: public CxxTest::TestSuite{
public:

	void testDefaultConstructor(void){
		kn::Vector<int> *v;
		v=new kn::Vector<int>();
		TS_ASSERT(v!=0);
		TS_ASSERT(v->size()==0);
		delete v;
	}

	void testConstructorWithOneParameter(void){
		kn::Vector<int> *v = new kn::Vector<int>(4);
		TS_ASSERT(v!=0);
		TS_ASSERT(v->size()==4);
		delete v;
	}

	void testCopyConstructor(void){
		kn::Vector<int> v1(3);
		v1[0]=2; v1[1]=-9; v1[2]=4;
		kn::Vector<int> v2(v1);
		TS_ASSERT(v2.size()==v1.size());
		TS_ASSERT(v2[0]==2
				  && v2[1]==-9
				  && v2[2]==4);
	}

	void testCopyPointerConstructor(void){
		kn::Vector<int> *v1=new kn::Vector<int>(3);
		(*v1)[0]=7; (*v1)[1]=25; (*v1)[2]=-144;
		kn::Vector<int> v2(v1);
		TS_ASSERT(v2.size()==v1->size());
		TS_ASSERT(v2[0]==7
				  && v2[1]==25
				  && v2[2]==-144);
		delete v1;
	}

	void testConstructorWithOneParameterAndAnArray(void){
		int tab[5]={-10, 6, 8, 124, -2};
		int *pl = NULL;
		kn::Vector<int> v(5, tab);
		TS_ASSERT(v.size()==5);
		for(unsigned int i=0; i<5; i++){
			TS_ASSERT(v[i]==tab[i]);
			TS_ASSERT(v[i]!=0);
		}
		TS_ASSERT_THROWS(kn::Vector<int> v(5, pl);,kn::MathException);
	}

	void testConstructorWithTwoParameters(void){
		kn::Vector<float> v((unsigned int)18, -87.574f);
		TS_ASSERT(v.size()==18);
		for(unsigned int i=0; i<18; i++){
			TS_ASSERT(v[i]==-87.574f);
		}
	}

	void testOperatorBracket(){
	  kn::Vector<float> v(4);
	  v[0]=2.1f; v[1]=10.5f; v[2]=0.23f; v[3]=56.7f;
	  TS_ASSERT(v[0]==v.begin()[0]);
	  TS_ASSERT(v[1]==v.begin()[1]);
	  TS_ASSERT(v[2]==v.begin()[2]);
	  TS_ASSERT(v[3]==v.begin()[3]);
	  kn::Vector<float,kn::StaticStorePolicy<float,4> > v2;
	  v2[0]=2.1f; v2[1]=10.5f; v2[2]=0.23f; v2[3]=56.7f;
	  TS_ASSERT(v2[0]==v2.begin()[0]);
	  TS_ASSERT(v2[1]==v2.begin()[1]);
	  TS_ASSERT(v2[2]==v2.begin()[2]);
	  TS_ASSERT(v2[3]==v2.begin()[3]);
	}

	void testOperatorParenthesis(){
	  kn::Vector<float> v(4);
	  v(0)=2.1f; v(1)=10.5f; v(2)=0.23f; v(3)=56.7f;
	  TS_ASSERT(v(0)==v.begin()[0]);
	  TS_ASSERT(v(1)==v.begin()[1]);
	  TS_ASSERT(v(2)==v.begin()[2]);
	  TS_ASSERT(v(3)==v.begin()[3]);
	  kn::Vector<float,kn::StaticStorePolicy<float,4> > v2;
	  v2(0)=2.1f; v2(1)=10.5f; v2(2)=0.23f; v2(3)=56.7f;
	  TS_ASSERT(v2(0)==v2.begin()[0]);
	  TS_ASSERT(v2(1)==v2.begin()[1]);
	  TS_ASSERT(v2(2)==v2.begin()[2]);
	  TS_ASSERT(v2(3)==v2.begin()[3]);
	}

	void testAt(void){
		kn::Vector<float> v(4);
		v[0]=2.1f; v[1]=10.5f; v[2]=0.23f; v[3]=56.7f;
		v.at(3)=v.at(1);
		TS_ASSERT_THROWS(v.at(4),kn::MathException);
		TS_ASSERT_THROWS(v.at(-1),kn::MathException);
		TS_ASSERT(v[0]==2.1f);
		TS_ASSERT(v[3]==10.5f);
		TS_ASSERT(v[2]==0.23f);
	  kn::Vector<float,kn::StaticStorePolicy<float,4> > v2;
	  v2(0)=2.1f; v2(1)=10.5f; v2(2)=0.23f; v2(3)=56.7f;
		v2.at(3)=v2.at(1);
		TS_ASSERT_THROWS(v2.at(4),kn::MathException);
		TS_ASSERT_THROWS(v2.at(-1),kn::MathException);
		TS_ASSERT(v2[0]==2.1f);
		TS_ASSERT(v2[3]==10.5f);
		TS_ASSERT(v2[2]==0.23f);
	}


	void testResize(void){
		kn::Vector<float> v1(5), v2(5);
		v1[0]=2.1f; v1[1]=10.5f; v1[2]=0.23f; v1[3]=56.7f; v1[4]=-44.1f;

		v2 = v1;
		TS_ASSERT(v2 == v1);

		v2.resize(5);
		TS_ASSERT(v2.size() == 5);

		v1.resize(2);
		TS_ASSERT(v1.size() == 2);

		v1.resize(6);
		TS_ASSERT(v1.size() == 6);
	}

	void testResizeAndCopy(void){
		kn::Vector<float> v1(5), v2(2),v3;
		v1[0]=2.1f; v1[1]=10.5f; v1[2]=0.23f; v1[3]=56.7f; v1[4]=-44.1f;
		v2[0]=2.0f; v2[1]=5.2f;

		v3 = v2;
		TS_ASSERT(v3.size() == v2.size() && v3.size()==2);
		TS_ASSERT(v3[0]==2.0f && v3[1]==5.2f);

		v3.resizeAndCopy(v1);
		TS_ASSERT(v3.size() == v1.size() && v3.size()==5);
		TS_ASSERT(v3[0]==2.1f &&
				  v3[1] == 10.5f &&
				  v3[2] == 0.23f &&
				  v3[3] == 56.7f &&
				  v3[4] == -44.1f);

		v1.resizeAndCopy(v2);
		TS_ASSERT(v1.size() == v2.size() && v1.size()==2);
		TS_ASSERT(v1[0]==2.0f && v1[1]==5.2f);
	}


	void testOperatorEquals(void){
		kn::Vector<int> v1(3), v2(3), v3(3);
		v1[0]=12; v1[1]=65; v1[2]=139;
		v2[0]=7; v2[1]=-10; v2[2]=-203;
		v3[0]=12; v3[1]=65; v3[2]=139;
		TS_ASSERT(!(v1==v2));
		TS_ASSERT(v1==v3);
	}

	void testOperatorDiff(void){
		kn::Vector<int> v1(3), v2(3), v3(3);
		v1[0]=126; v1[1]=55; v1[2]=100;
		v2[0]=7; v2[1]=-10; v2[2]=-203;
		v3[0]=126; v3[1]=55; v3[2]=100;
		TS_ASSERT(v1!=v2);
		TS_ASSERT(!(v1!=v3));
	}

	void testOperatorAssign(void){
		kn::Vector<int> v1(3), v2(3);
		int *v4[3];
		v1[0]=12; v1[1]=65; v1[2]=139;
		v2[0]=7; v2[1]=-10; v2[2]=-203;
		v4[0]=&v2[0];v4[1]=&v2[1];v4[2]=&v2[2];
		TS_ASSERT(*v4[0]==7 && *v4[1]==-10 && *v4[2]==-203);

		v2=v1;
		TS_ASSERT(v2[0]==12 && v2[1]==65  && v2[2]==139);
		TS_ASSERT(*v4[0]==12 && *v4[1]==65  && *v4[2]==139);

		kn::Vector<int> v3;
		v3 = v1;
		TS_ASSERT(v3.size()==v1.size());
		TS_ASSERT(v3[0]==12 && v3[1]==65 && v3[2]==139);

		v3=4;
		TS_ASSERT(v3.size()==v1.size());
		TS_ASSERT(v3[0]==4 && v3[1]==4 && v3[2]==4);

	}

	void testOperatorAdd(void){
		kn::Vector<int> v1(3), v2(3), v3(3);
		v1[0]=12; v1[1]=65; v1[2]=139;
		v2[0]=7; v2[1]=-10; v2[2]=-203;
		v3=v1+v2;
		TS_ASSERT(v3[0]==19 && v3[1]==55 && v3[2]==-64);
	}

	void testOperatorSubstract(void){
		kn::Vector<int> v1(3), v2(3), v3(3);
		v1[0]=12; v1[1]=65; v1[2]=139;
		v2[0]=7; v2[1]=-10; v2[2]=-203;
		v3=v1-v2;
		TS_ASSERT(v3[0]==5 && v3[1]==75 && v3[2]==342);
	}

	void testOperatorDivide(void){
		kn::Vector<int> v1(3), v2(3);
		v1[0]=12; v1[1]=66; v1[2]=138;
		v2[0]=7; v2[1]=-10; v2[2]=-203;
		v2=v1/3;
		TS_ASSERT(v2[0]==4 && v2[1]==22 && v2[2]==46);
	}

	void testOperatorDotProduct(void){
		kn::Vector<int> v1(3), v2(3);
		v1[0]=12; v1[1]=65; v1[2]=139;
		v2[0]=7; v2[1]=-10; v2[2]=-23;
		TS_ASSERT(v1*v2==-3763);
	}

	void testOperatorMultiplyByValue(void){
		kn::Vector<int> v1(3), v2(3);
		v1[0]=12; v1[1]=66; v1[2]=138;
		v2[0]=7; v2[1]=-10; v2[2]=-203;
		v2=v1*3;
		TS_ASSERT(v2[0]==36 && v2[1]==198 && v2[2]==414);
	}

	void testOperatorOpposite(void){
		kn::Vector<int> v1(3), v2(3);
		v1[0]=12; v1[1]=66; v1[2]=138;
		v2[0]=7; v2[1]=-10; v2[2]=-203;
		v2=-v1;
		TS_ASSERT(v2[0]==-12 && v2[1]==-66 && v2[2]==-138);
	}

	void testOperatorAddAssign(void){
		kn::Vector<int> v1(3), v2(3);
		int *v3[3];
		v1[0]=12; v1[1]=65; v1[2]=139;
		v2[0]=7; v2[1]=-10; v2[2]=-203;
		v3[0]=&v1[0];v3[1]=&v1[1];v3[2]=&v1[2];
		TS_ASSERT(*v3[0]==12 && *v3[1]==65 && *v3[2]==139);
		v1+=v2;
		TS_ASSERT(v1[0]==19 && v1[1]==55  && v1[2]==-64);
		TS_ASSERT(v2[0]==7  && v2[1]==-10 && v2[2]==-203);
		TS_ASSERT(*v3[0]==19 && *v3[1]==55  && *v3[2]==-64);
	}

	void testOperatorSubstractAssign(void){
		kn::Vector<int> v1(3), v2(3);
		int *v3[3];
		v1[0]=12; v1[1]=65; v1[2]=139;
		v2[0]=7; v2[1]=-10; v2[2]=-203;
		v3[0]=&v1[0];v3[1]=&v1[1];v3[2]=&v1[2];
		TS_ASSERT(*v3[0]==12 && *v3[1]==65 && *v3[2]==139);
		v1-=v2;
		TS_ASSERT(v1[0]==5 && v1[1]==75 && v1[2]==342);
		TS_ASSERT(v2[0]==7  && v2[1]==-10 && v2[2]==-203);
		TS_ASSERT(*v3[0]==5 && *v3[1]==75  && *v3[2]==342);
	}

	void testOperatorDivideAssign(void){
		kn::Vector<int> v(3);
		int *v1[3];
		v[0]=12; v[1]=66; v[2]=138;
		v1[0]=&v[0];v1[1]=&v[1];v1[2]=&v[2];
		TS_ASSERT(*v1[0]==12 && *v1[1]==66 && *v1[2]==138);
		v/=3;
		TS_ASSERT(v[0]==4 && v[1]==22 && v[2]==46);
		TS_ASSERT(*v1[0]==4 && *v1[1]==22 && *v1[2]==46);
	}

	void testOperatorMultiplyAssign(void){
		kn::Vector<int> v(3);
		int *v1[3];
		v[0]=12; v[1]=66; v[2]=138;
		v1[0]=&v[0];v1[1]=&v[1];v1[2]=&v[2];
		TS_ASSERT(*v1[0]==12 && *v1[1]==66 && *v1[2]==138);
		v*=3;
		TS_ASSERT(v[0]==36 && v[1]==198 && v[2]==414);
		TS_ASSERT(*v1[0]==36 && *v1[1]==198 && *v1[2]==414);
	}

	void testOperatorVectorProduct(void){
		kn::Vector<int,kn::StaticStorePolicy<int,3> > v1(3),v2(3),v;
		v1[0]=1; v1[1]=66; v1[2]=13;
		v2[0]=2; v2[1]=6; v2[2]=5;
		v = v1^v2;
		TS_ASSERT(v[0]==252 && v[1]==21 && v[2]==-126);
	}

	void testRoundZero(void){
		kn::Vector<float> v(3);
		v[0]=2.1f; v[1]=10.5f; v[2]=0.23f;
		v.roundZero(0.2);
		TS_ASSERT(v[0]==2.1f && v[1]==10.5f && v[2]==0.23f);
		v.roundZero(0.25);
		TS_ASSERT(v[0]==2.1f && v[1]==10.5f && v[2]==0.0f);
		v.roundZero(3.56);
		TS_ASSERT(v[0]==0.0f && v[1]==10.5f && v[2]==0.0f);
		v.roundZero(15.0);
		TS_ASSERT(v[0]==0.0f && v[1]==0.0f && v[2]==0.0f);
	}

	void testSize(){
	  kn::Vector<float> v(3);
	  TS_ASSERT(v.size()==3);
	}

	void testFill(void){
	  kn::Vector<float> v(3);
	  v.fill(5.62f);
	  TS_ASSERT(v[0]==5.62f && v[1]==5.62f && v[2]==5.62f);
	  kn::Vector<float,kn::StaticStorePolicy<float,3> > v2;
	  v2.fill(5.62f);
	  TS_ASSERT(v2[0]==5.62f && v2[1]==5.62f && v2[2]==5.62f);
	}

	void testSetZero(void){
	  kn::Vector<float> v(3u,5.62f);
	  TS_ASSERT(v[0]==5.62f && v[1]==5.62f && v[2]==5.62f);
	  v.setZero();
	  TS_ASSERT(v[0]==0.0f && v[1]==0.0f && v[2]==0.0f);
	}

	void testSetSubVector(void){
		kn::Vector<float> v1(5), v2(2);
		v1[0]=2.1f; v1[1]=10.5f; v1[2]=0.23f; v1[3]=56.7f; v1[4]=-44.1f;
		v2[0]=0.0f; v2[1]=88.6f;
		v1.setSubVector(2, v2);
		TS_ASSERT(v1[0]==2.1f && v1[1]==10.5f && v1[2]==0.0f && v1[3]==88.6f && v1[4]==-44.1f);
		v1.setSubVector(3, v2);
		TS_ASSERT(v1[0]==2.1f && v1[1]==10.5f && v1[2]==0.0f && v1[3]==0.0f && v1[4]==88.6f);
		TS_ASSERT_THROWS(v1.setSubVector(7, v2), kn::MathException);
		TS_ASSERT_THROWS(v1.setSubVector(4, v2), kn::MathException);

		kn::Vector<float> v3(5), v4(3);
		v3[0]=2.1f; v3[1]=10.5f; v3[2]=0.23f; v3[3]=56.7f; v3[4]=-44.1f;
		v4[0]=0.0f; v4[1]=88.6f; v4[2]=9.57f;
		v3.setSubVector(0,1,1,v4);
		TS_ASSERT(v3[0]==88.6f && v3[1]==10.5f && v3[2]==0.23f && v3[3]==56.7f && v3[4]==-44.1f);
  		v3.setSubVector(4,2,1,v4);
		TS_ASSERT(v3[0]==88.6f && v3[1]==10.5f && v3[2]==0.23f && v3[3]==56.7f && v3[4]==9.57f);
		v3.setSubVector(1,0,3,v4);
		TS_ASSERT(v3[0]==88.6f && v3[1]==0.0f && v3[2]==88.6f && v3[3]==9.57f && v3[4]==9.57f);
		v3.setSubVector(1,0,0,v4);
		TS_ASSERT(v3[0]==88.6f && v3[1]==0.0f && v3[2]==88.6f && v3[3]==9.57f && v3[4]==9.57f);

		TS_ASSERT_THROWS(v3.setSubVector(7,0,1,v2), kn::MathException);
		TS_ASSERT_THROWS(v3.setSubVector(4,0,3,v2), kn::MathException);
		TS_ASSERT_THROWS(v3.setSubVector(0,8,3,v2), kn::MathException);
		TS_ASSERT_THROWS(v3.setSubVector(0,0,4,v2), kn::MathException);

	}

	void testGetSubVector(void){
		kn::Vector<float> v1(5), v2(2),v3,v4;
		v1[0]=2.1f; v1[1]=10.5f; v1[2]=0.23f; v1[3]=56.7f; v1[4]=-44.1f;

		v2 = v1.getSubVector(2,2);
		TS_ASSERT(v2[0]==0.23f && v2[1]==56.7f);

		v3 = v1.getSubVector(0,1);
		TS_ASSERT(v3[0]==2.1f);

		v4 = v1.getSubVector(3,2);
		TS_ASSERT(v4[0]==56.7f && v4[1]==-44.1f);

		TS_ASSERT_THROWS(v1.getSubVector(5,0),kn::MathException);
		TS_ASSERT_THROWS(v1.getSubVector(4,2),kn::MathException);

	}

	void testBegin(void){
		kn::Vector<double> v(4);
		v[0]=3.0; v[1]=5.0; v[2]=1.0; v[3]=1.0;
		TS_ASSERT(v.begin()[0] == 3.0 && v.begin()[1] == 5.0 && v.begin()[2] == 1.0 && v.begin()[3] == 1.0);
	}

	void testEnd(void){
		kn::Vector<double> v(4);
		v[v.size()-1]=-72.9;
		TS_ASSERT(*(v.end()-1) == v.begin()[v.size()-1]);
	}

	void testGetNorm(void){
		kn::Vector<double> v(4);
		v[0]=3.0; v[1]=5.0; v[2]=1.0; v[3]=1.0;

		TS_ASSERT(v.getNorm() == 6.0);
	}

	void testNormalize(void){
		kn::Vector<double> v(5);
		v[0]=1.0; v[1]=1.0; v[2]=1.0; v[3]=2.0;v[4]=3.0;
		v.normalize();
		TS_ASSERT(v[0]==0.25 &&
			  v[1]==0.25 &&
			  v[2]==0.25 &&
			  v[3]==0.5 &&
			  v[4]==0.75);
		TS_ASSERT(v.getNorm() == 1.0);
	}

	void testNormalized(void){
		kn::Vector<double> v(5),w(5);
		v[0]=1.0; v[1]=1.0; v[2]=1.0; v[3]=2.0;v[4]=3.0;
		w = v.getNormalized();
		TS_ASSERT(v[0]==1.0 && v[1]==1.0 && v[2]==1.0 && v[3]==2.0 && v[4]==3.0);
		TS_ASSERT(w[0]==0.25 && w[1]==0.25 && w[2]==0.25 && w[3]==0.5 && w[4]==0.75);
		TS_ASSERT(w.getNorm() == 1.0);
	}

	void testSwap(void){
		kn::Vector<float> v(3);
		v[0]=2.1f; v[1]=10.5f; v[2]=0.23f;
		v.swap(0, 2);
		TS_ASSERT(v[0]==0.23f && v[1]==10.5f && v[2]==2.1f);
	}


	void testOperatorMultiplyScalarByVector(void){
		kn::Vector<int> v(3);
		v[0]=12; v[1]=65; v[2]=139;
		v = 2*v;
		TS_ASSERT(v[0]==24 && v[1]==130 && v[2]==278);
	}

	void testGetHomogeneous(void){
		kn::Vector<double> v1(3);
		v1[0]=20.0; v1[1]=30.0; v1[2]=10.0;

		kn::Vector<double> v2(v1.getHomogeneous());

		TS_ASSERT_DELTA(v2[0],20.0, 1.0e-10);
		TS_ASSERT_DELTA(v2[1],30.0, 1.0e-10);
		TS_ASSERT_DELTA(v2[2],10.0, 1.0e-10);
		TS_ASSERT_EQUALS(v2[3],1.0);
	}

	void testGetUnhomogeneous(void){
		kn::Vector<double> v1(3);

		v1[0]=20.0; v1[1]=30.0; v1[2]=10.0;
		kn::Vector<double> v2(v1.getUnhomogeneous());
		TS_ASSERT_DELTA(v2[0],2.0, 1.0e-10);
		TS_ASSERT_DELTA(v2[1],3.0, 1.0e-10);

		v1[0]=20.0; v1[1]=30.0; v1[2]=1.0;
		kn::Vector<double> v3(v1.getUnhomogeneous());
		TS_ASSERT_DELTA(v3[0],20.0, 1.0e-10);
		TS_ASSERT_DELTA(v3[1],30.0, 1.0e-10);

		v1[0]=20.0; v1[1]=30.0; v1[2]=0.0;
		kn::Vector<double> v4(v1.getUnhomogeneous());
		TS_ASSERT_DELTA(v4[0],20.0, 1.0e-10);
		TS_ASSERT_DELTA(v4[1],30.0, 1.0e-10);

		kn::Vector<double,kn::StaticStorePolicy<double,3> > v5;
		v5[0]=20.0; v5[1]=30.0; v5[2]=10.0;
		kn::Vector<double,kn::StaticStorePolicy<double,2> > v6(v5.getUnhomogeneous());
		TS_ASSERT_DELTA(v6[0],2.0, 1.0e-10);
		TS_ASSERT_DELTA(v6[1],3.0, 1.0e-10);
		
		

		
	}


	void testSetHomogeneousNormalFormStandard(void){
		kn::Vector<double> v1(3);
		v1[0]=20.0; v1[1]=30.0; v1[2]=10.0;
		v1.setHomogeneousNormalForm();

		TS_ASSERT_DELTA(v1[0],2.0, 1.0e-10);
		TS_ASSERT_DELTA(v1[1],3.0, 1.0e-10);
		TS_ASSERT_EQUALS(v1[2],1.0);

		v1[0]=20.0; v1[1]=30.0; v1[2]=1.0;
		v1.setHomogeneousNormalForm();
		TS_ASSERT_DELTA(v1[0],20.0, 1.0e-10);
		TS_ASSERT_DELTA(v1[1],30.0, 1.0e-10);
		TS_ASSERT_EQUALS(v1[2],1.0);

		v1[0]=20.0; v1[1]=30.0; v1[2]=0.0;
		v1.setHomogeneousNormalForm();

		TS_ASSERT_DELTA(v1[0],20.0, 1.0e-10);
		TS_ASSERT_DELTA(v1[1],30.0, 1.0e-10);
		TS_ASSERT_EQUALS(v1[2],0.0);
	}

};

/*
 * End of Anti-doublon
 */
#endif
