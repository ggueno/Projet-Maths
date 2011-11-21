/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * MatrixLoaderExporterTest.hpp created in 04 2009.
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
#ifndef __OPENKN_MATH__MATH_IO_TEST_HPP__
#define __OPENKN_MATH__MATH_IO_TEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <vector>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/math/MathException.hpp>
#include <OpenKN/math/Matrix.hpp>
#include <OpenKN/math/MathIO.hpp>


/*
 * Class definition
 */

class MatrixLoaderExporterTest : public CxxTest::TestSuite {
public:

	// save a matrix, check if the resulting matrix is identical to the original matrix
	void testMatrixLoaderExporter( void ) {
		// original matrix
		kn::Matrix<double> original(3,4);
		for(unsigned int i=0; i<original.rows(); i++)
			for(unsigned int j=0; j<original.columns(); j++)
				original[i][j] = 2.0*i + 3.0*j -5.0;

		// save
		TS_ASSERT_THROWS_NOTHING(saveMatrix(original,"output/matrix.mat"));
		TS_ASSERT_THROWS_NOTHING(saveMatrix(original,"output/matrixHeader.mat",true));
		TS_ASSERT_THROWS_NOTHING(saveMatrix(original,"output/matrixHeaderComment.mat",true,"matrix test"));
		TS_ASSERT_THROWS_NOTHING(saveMatrix(original,"output/matrixComment.mat",false,"matrix test"));


		// load 0 size matrix
		kn::Matrix<double> M0;
		TS_ASSERT_THROWS(loadMatrix(M0,"output/jeMangeDesTo.mat"), kn::MathException);
		kn::Matrix<double> M1;
		TS_ASSERT_THROWS_NOTHING(loadMatrix(M1,"output/matrix.mat"));
		kn::Matrix<double> M2;
		TS_ASSERT_THROWS_NOTHING(loadMatrix(M2,"output/matrixHeader.mat"));
		kn::Matrix<double> M3;
		TS_ASSERT_THROWS_NOTHING(loadMatrix(M3,"output/matrixComment.mat"));
		kn::Matrix<double> M4;
		TS_ASSERT_THROWS_NOTHING(loadMatrix(M4,"output/matrixHeaderComment.mat"));

		for(unsigned int i=0; i<original.rows(); i++) {
			for(unsigned int j=0; j<original.columns(); j++) {
				TS_ASSERT_EQUALS(original[i][j], M1[i][j]);
				TS_ASSERT_EQUALS(original[i][j], M2[i][j]);
				TS_ASSERT_EQUALS(original[i][j], M3[i][j]);
				TS_ASSERT_EQUALS(original[i][j], M4[i][j]);
			}
		}

		// load builed incorrect matrices
		kn::Matrix<double> P0_1(original.rows(),original.columns());
		TS_ASSERT_THROWS(loadMatrix(P0_1,"output/jeMangeDesTo.mat"), kn::MathException);
		kn::Matrix<double> P0_2(original.rows()+1,original.columns());
		TS_ASSERT_THROWS(loadMatrix(P0_2,"output/matrix.mat"), kn::MathException);
		kn::Matrix<double> P0_3(original.rows()+1,original.columns());
		TS_ASSERT_THROWS(loadMatrix(P0_3,"output/matrixHeader.mat"), kn::MathException);
		kn::Matrix<double> P0_4(original.rows(),original.columns()-1);
		TS_ASSERT_THROWS(loadMatrix(P0_4,"output/matrix.mat"), kn::MathException);
		kn::Matrix<double> P0_5(original.rows(),original.columns()-1);
		TS_ASSERT_THROWS(loadMatrix(P0_5,"output/matrixHeader.mat"), kn::MathException);

		// load builed matrices
		kn::Matrix<double> P1(original.rows(),original.columns());
		TS_ASSERT_THROWS_NOTHING(loadMatrix(P1,"output/matrix.mat"));
		kn::Matrix<double> P2(original.rows(),original.columns());
		TS_ASSERT_THROWS_NOTHING(loadMatrix(P2,"output/matrixHeader.mat"));
		kn::Matrix<double> P3(original.rows(),original.columns());
		TS_ASSERT_THROWS_NOTHING(loadMatrix(P3,"output/matrixComment.mat"));
		kn::Matrix<double> P4(original.rows(),original.columns());
		TS_ASSERT_THROWS_NOTHING(loadMatrix(P4,"output/matrixHeaderComment.mat"));

		for(unsigned int i=0; i<original.rows(); i++)
			for(unsigned int j=0; j<original.columns(); j++){
					TS_ASSERT_EQUALS(original[i][j], P1[i][j]);
					TS_ASSERT_EQUALS(original[i][j], P2[i][j]);
					TS_ASSERT_EQUALS(original[i][j], P3[i][j]);
					TS_ASSERT_EQUALS(original[i][j], P4[i][j]);
			}
	}

	// save/load a vector of matrix, check if the resulting matrix is identical to the original matrix
	void testMatrixListLoadSave( void ) {
		// original matrices
		kn::Matrix3x3d M33;
		for(unsigned int i=0; i<M33.rows(); i++)
			for(unsigned int j=0; j<M33.columns(); j++)
				M33[i][j] = 1.0*i + 2.0*j -3.0;

		kn::Matrix4x4d M44;
		for(unsigned int i=0; i<M44.rows(); i++)
			for(unsigned int j=0; j<M44.columns(); j++)
				M44[i][j] = 2.0*i + 4.0*j -6.0;

		kn::Matrixd M34(3,4);
		for(unsigned int i=0; i<M34.rows(); i++)
			for(unsigned int j=0; j<M34.columns(); j++)
				M34[i][j] = 1.0*i + 4.0*j -5.0;

		std::vector< kn::Matrix<double> > original;
		original.push_back(M33);
		original.push_back(M44);
		original.push_back(M34);

		// save
		TS_ASSERT_THROWS_NOTHING(saveMatrixList(original,"output/matrixList.lmat"));
		TS_ASSERT_THROWS_NOTHING(saveMatrixList(original,"output/matrixListHeader.lmat",true));
		TS_ASSERT_THROWS_NOTHING(saveMatrixList(original,"output/matrixListHeaderComment.lmat",true,"matrix list test"));
		TS_ASSERT_THROWS_NOTHING(saveMatrixList(original,"output/matrixListComment.lmat",false,"matrix list test"));


		// load matrixList
		std::vector< kn::Matrix<double> > l0;
		TS_ASSERT_THROWS(loadMatrixList(l0,"output/jeMangeDesTo.lmat"), kn::MathException);
		std::vector< kn::Matrix<double> > l1;
		TS_ASSERT_THROWS_NOTHING(loadMatrixList(l1,"output/matrixList.lmat"));
		std::vector< kn::Matrix<double> > l2;
		TS_ASSERT_THROWS_NOTHING(loadMatrixList(l2,"output/matrixListHeader.lmat"));
		std::vector< kn::Matrix<double> > l3;
		TS_ASSERT_THROWS_NOTHING(loadMatrixList(l3,"output/matrixListComment.lmat"));
		std::vector< kn::Matrix<double> > l4;
		TS_ASSERT_THROWS_NOTHING(loadMatrixList(l4,"output/matrixListHeaderComment.lmat"));

		for(unsigned int m=0;m<original.size();m++){
			//assert vector size
			TS_ASSERT_EQUALS(original.size(),l1.size());
			TS_ASSERT_EQUALS(original.size(),l2.size());
			TS_ASSERT_EQUALS(original.size(),l3.size());
			TS_ASSERT_EQUALS(original.size(),l4.size());
			//assert matrices size (rows)
			TS_ASSERT_EQUALS(original.at(m).rows(),l1.at(m).rows());
			TS_ASSERT_EQUALS(original.at(m).rows(),l2.at(m).rows());
			TS_ASSERT_EQUALS(original.at(m).rows(),l3.at(m).rows());
			TS_ASSERT_EQUALS(original.at(m).rows(),l4.at(m).rows());
			//assert matrices size (columns)
			TS_ASSERT_EQUALS(original.at(m).columns(),l1.at(m).columns());
			TS_ASSERT_EQUALS(original.at(m).columns(),l2.at(m).columns());
			TS_ASSERT_EQUALS(original.at(m).columns(),l3.at(m).columns());
			TS_ASSERT_EQUALS(original.at(m).columns(),l4.at(m).columns());
			//assert matrix value
			for(unsigned int i=0; i<original.at(m).rows(); i++){
				for(unsigned int j=0; j<original.at(m).columns(); j++){
					TS_ASSERT_EQUALS(original.at(m).at(i,j), l1.at(m).at(i,j));
					TS_ASSERT_EQUALS(original.at(m).at(i,j), l2.at(m).at(i,j));
					TS_ASSERT_EQUALS(original.at(m).at(i,j), l3.at(m).at(i,j));
					TS_ASSERT_EQUALS(original.at(m).at(i,j), l4.at(m).at(i,j));
				}
			}
		}
	}


	// save a Vector, check if the resulting vector is identical to the original vector
	void testVectorLoaderExporter( void ) {
		// original vector
		kn::Vector<double> original(5);
		for(unsigned int i=0; i<original.size(); i++)
				original[i] = i*5.0;

		// save
		TS_ASSERT_THROWS_NOTHING(saveVector(original,"output/vector.vec"));
		TS_ASSERT_THROWS_NOTHING(saveVector(original,"output/vectorHeader.vec",true));
		TS_ASSERT_THROWS_NOTHING(saveVector(original,"output/vectorHeaderComment.vec",true,"vector test"));
		TS_ASSERT_THROWS_NOTHING(saveVector(original,"output/vectorComment.vec",false,"vector test"));


		// load 0 size vector
		kn::Vector<double> V0;
		TS_ASSERT_THROWS(loadVector(V0,"output/jeMangeDesTo.vec"), kn::MathException);
		kn::Vector<double> V1;
		TS_ASSERT_THROWS_NOTHING(loadVector(V1,"output/vector.vec"));
		kn::Vector<double> V2;
		TS_ASSERT_THROWS_NOTHING(loadVector(V2,"output/vectorHeader.vec"));
		kn::Vector<double> V3;
		TS_ASSERT_THROWS_NOTHING(loadVector(V3,"output/vectorComment.vec"));
		kn::Vector<double> V4;
		TS_ASSERT_THROWS_NOTHING(loadVector(V4,"output/vectorHeaderComment.vec"));

		for(unsigned int i=0; i<original.size(); i++){
				TS_ASSERT_EQUALS(original[i], V1[i]);
				TS_ASSERT_EQUALS(original[i], V2[i]);
				TS_ASSERT_EQUALS(original[i], V3[i]);
				TS_ASSERT_EQUALS(original[i], V4[i]);
		}

		// load builded incorrect vector
		kn::Vector<double> V0_1(original.size());
		TS_ASSERT_THROWS(loadVector(V0_1,"output/jeMangeDesTo.vec"), kn::MathException);
		kn::Vector<double> V0_2(original.size()+1);;
		TS_ASSERT_THROWS(loadVector(V0_2,"output/vector.vec"), kn::MathException);
		kn::Vector<double> V0_3(original.size()+1);
		TS_ASSERT_THROWS(loadVector(V0_3,"output/vectorHeader.vec"), kn::MathException);
		kn::Vector<double> V0_4(original.size()-1);
		TS_ASSERT_THROWS(loadVector(V0_4,"output/vector.vec"), kn::MathException);
		kn::Vector<double> V0_5(original.size()-1);
		TS_ASSERT_THROWS(loadVector(V0_5,"output/vectorHeader.vec"), kn::MathException);

		// load builded vector
		kn::Vector<double> V1_1(original.size());
		TS_ASSERT_THROWS_NOTHING(loadVector(V1_1,"output/vector.vec"));
		kn::Vector<double> V1_2(original.size());
		TS_ASSERT_THROWS_NOTHING(loadVector(V1_2,"output/vectorHeader.vec"));
		kn::Vector<double> V1_3(original.size());
		TS_ASSERT_THROWS_NOTHING(loadVector(V1_3,"output/vectorComment.vec"));
		kn::Vector<double> V1_4(original.size());
		TS_ASSERT_THROWS_NOTHING(loadVector(V1_4,"output/vectorHeaderComment.vec"));

		for(unsigned int i=0; i<original.size(); i++){
			TS_ASSERT_EQUALS(original[i], V1_1[i]);
			TS_ASSERT_EQUALS(original[i], V1_2[i]);
			TS_ASSERT_EQUALS(original[i], V1_3[i]);
			TS_ASSERT_EQUALS(original[i], V1_4[i]);
		}
	}


	// save/load a vector of Vector, check if the resulting vector are identical to the original vector
	void testVectorListLoadSave( void ) {
		// original vectorList
		kn::Vectord v2(2);
		for(unsigned int i=0; i<v2.size(); i++)
			v2.at(i) = (i+1)*v2.size();

		kn::Vectord v3(3);
		for(unsigned int i=0; i<v3.size(); i++)
			v3.at(i) = (i+1)*v3.size();

		kn::Vectord v4(4);
		for(unsigned int i=0; i<v4.size(); i++)
			v4.at(i) = (i+1)*v4.size();

		kn::Vectord v5(5);
		for(unsigned int i=0; i<v5.size(); i++)
			v5.at(i) = (i+1)*v5.size();

		std::vector< kn::Vector<double> > original;
		original.push_back(v2);
		original.push_back(v3);
		original.push_back(v4);
		original.push_back(v5);

		// save
		TS_ASSERT_THROWS_NOTHING(saveVectorList(original,"output/vectorList.lvec"));
		TS_ASSERT_THROWS_NOTHING(saveVectorList(original,"output/vectorListHeader.lvec",true));
		TS_ASSERT_THROWS_NOTHING(saveVectorList(original,"output/vectorListHeaderComment.lvec",true,"vector list test"));
		TS_ASSERT_THROWS_NOTHING(saveVectorList(original,"output/vectorListComment.lvec",false,"vector list test"));


		// load vectorList
		std::vector< kn::Vector<double> > l0;
		TS_ASSERT_THROWS(loadVectorList(l0,"output/jeMangeDesTo.lvec"), kn::MathException);
		std::vector< kn::Vector<double> > l1;
		TS_ASSERT_THROWS_NOTHING(loadVectorList(l1,"output/vectorList.lvec"));
		std::vector< kn::Vector<double> > l2;
		TS_ASSERT_THROWS_NOTHING(loadVectorList(l2,"output/vectorListHeader.lvec"));
		std::vector< kn::Vector<double> > l3;
		TS_ASSERT_THROWS_NOTHING(loadVectorList(l3,"output/vectorListComment.lvec"));
		std::vector< kn::Vector<double> > l4;
		TS_ASSERT_THROWS_NOTHING(loadVectorList(l4,"output/vectorListHeaderComment.lvec"));

		//assert vector size
		TS_ASSERT_EQUALS(original.size(),l1.size());
		TS_ASSERT_EQUALS(original.size(),l2.size());
		TS_ASSERT_EQUALS(original.size(),l3.size());
		TS_ASSERT_EQUALS(original.size(),l4.size());

		for(unsigned int m=0;m<original.size();m++){
			//assert kn::Vector size
			TS_ASSERT_EQUALS(original.at(m).size(),l1.at(m).size());
			TS_ASSERT_EQUALS(original.at(m).size(),l2.at(m).size());
			TS_ASSERT_EQUALS(original.at(m).size(),l3.at(m).size());
			TS_ASSERT_EQUALS(original.at(m).size(),l4.at(m).size());
			//assert vector value
			for(unsigned int i=0; i<original.at(m).size(); i++){
				TS_ASSERT_EQUALS(original.at(m).at(i), l1.at(m).at(i));
				TS_ASSERT_EQUALS(original.at(m).at(i), l2.at(m).at(i));
				TS_ASSERT_EQUALS(original.at(m).at(i), l3.at(m).at(i));
				TS_ASSERT_EQUALS(original.at(m).at(i), l4.at(m).at(i));
			}
		}
	}

	// save/load a vector of Vector, check if the resulting vector are identical to the original vector
	void testVector3ListLoadSave( void ) {
		// original vectorList
		kn::Vector3d v2;
		for(unsigned int i=0; i<v2.size(); i++)
			v2.at(i) = (i)*v2.size();

		kn::Vector3d v3;
		for(unsigned int i=0; i<v3.size(); i++)
			v3.at(i) = (i+1)*v3.size();

		kn::Vector3d v4;
		for(unsigned int i=0; i<v4.size(); i++)
			v4.at(i) = (i+2)*v4.size();

		kn::Vector3d v5;
		for(unsigned int i=0; i<v5.size(); i++)
			v5.at(i) = (i+3)*v5.size();

		std::vector< kn::Vector3d > original;
		original.push_back(v2);
		original.push_back(v3);
		original.push_back(v4);
		original.push_back(v5);

		// save
		TS_ASSERT_THROWS_NOTHING(saveVectorList(original,"output/vector3List.lvec"));
		TS_ASSERT_THROWS_NOTHING(saveVectorList(original,"output/vector3ListHeader.lvec",true));
		TS_ASSERT_THROWS_NOTHING(saveVectorList(original,"output/vector3ListHeaderComment.lvec",true,"vector list test"));
		TS_ASSERT_THROWS_NOTHING(saveVectorList(original,"output/vector3ListComment.lvec",false,"vector list test"));


		// load vectorList
		std::vector< kn::Vector3d > l0;
		TS_ASSERT_THROWS(loadVectorList(l0,"output/jeMangeDesTo.lvec"), kn::MathException);
		std::vector< kn::Vector3d > l1;
		TS_ASSERT_THROWS_NOTHING(loadVectorList(l1,"output/vector3List.lvec"));
		std::vector< kn::Vector3d > l2;
		TS_ASSERT_THROWS_NOTHING(loadVectorList(l2,"output/vector3ListHeader.lvec"));
		std::vector< kn::Vector3d > l3;
		TS_ASSERT_THROWS_NOTHING(loadVectorList(l3,"output/vector3ListComment.lvec"));
		std::vector< kn::Vector<double> > l4;
		TS_ASSERT_THROWS_NOTHING(loadVectorList(l4,"output/vector3ListHeaderComment.lvec"));
	/*
		std::cout<<original<<std::endl;
		std::cout<<l0<<std::endl;
		std::cout<<l1<<std::endl;
		std::cout<<l2<<std::endl;
		std::cout<<l3<<std::endl;
	*/

		//assert vector size
		TS_ASSERT_EQUALS(original.size(),l1.size());
		TS_ASSERT_EQUALS(original.size(),l2.size());
		TS_ASSERT_EQUALS(original.size(),l3.size());
		TS_ASSERT_EQUALS(original.size(),l4.size());
		for(unsigned int m=0;m<original.size();m++){
			//assert kn::Vector size
			TS_ASSERT_EQUALS(original.at(m).size(),l1.at(m).size());
			TS_ASSERT_EQUALS(original.at(m).size(),l2.at(m).size());
			TS_ASSERT_EQUALS(original.at(m).size(),l3.at(m).size());
			TS_ASSERT_EQUALS(original.at(m).size(),l4.at(m).size());
			//assert vector value
			for(unsigned int i=0; i<original.at(m).size(); i++){
				TS_ASSERT_EQUALS(original.at(m).at(i), l1.at(m).at(i));
				TS_ASSERT_EQUALS(original.at(m).at(i), l2.at(m).at(i));
				TS_ASSERT_EQUALS(original.at(m).at(i), l3.at(m).at(i));
				TS_ASSERT_EQUALS(original.at(m).at(i), l4.at(m).at(i));
			}
		}
	}



};


/*
 * End of Anti-doublon
 */

#endif
