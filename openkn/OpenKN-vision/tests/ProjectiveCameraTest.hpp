/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * ProjectiveCameraTest.hpp created in 03 2009.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-vision.
 *
 * The OpenKraken-vision is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-vision is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_VISION__PROJECTIVE_CAMERA_TEST_HPP__
#define __OPENKN_VISION__PROJECTIVE_CAMERA_TEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <vector>
#include <cxxtest/TestSuite.h>
#include <cmath>
#include <cstdlib>

/*
 * Internal Includes
 */
#include <OpenKN/vision/ProjectiveCamera.hpp>
#include <OpenKN/math/Matrix.hpp>
#include <OpenKN/math/Matrix3x3.hpp>
#include <OpenKN/math/Vector4.hpp>


/*
 * Class definition
 */

class ProjectiveCameraTest : public CxxTest::TestSuite {
public:

	void buildTestMatrix(kn::Matrix<double> &P,
											 kn::Matrix3x3d &K,
											 kn::Matrix3x3d &R,
											 kn::Vector4d   &C) {
		// webcam type internal parameters
		K.setIdentity();
		K[0][2] = 550.0;
		K[1][2] = 550.0;
		K[0][0] = 240.0;
		K[1][1] = 320.0;

		// rotation matrix on z axis and angle alpha
		double alpha = 0.5; //radian
		R.setIdentity();
		R[0][0] = R[1][1] = cos(alpha);
		R[1][0] = sin(alpha);
		R[0][1] = - R[1][0];

		// position of the camera
		C[0] = 100.0;
		C[1] = 20.0;
		C[2] = -200.0;
		C[3] = 1.0;

		// compose
		// R contribution
		for(unsigned int i=0; i<3; i++)
			for(unsigned int j=0; j<3; j++)
				P[i][j] = R[i][j];

		// -RC contribution
		//kn::Vector<double> Ct(C.getUnhomogeneous());
		P.setColumn(3,-R*C.getUnhomogeneous());
		//std::cerr<<"La"<<std::endl;
		
		// K contribution
		P = K * P;
	}

	void testDefaultConstructor(){
		//std::cerr<<"Ici testDefaultConstructor"<<std::endl;
		// constructor
		kn::ProjectiveCamera camera;
		
		//Test
		for(unsigned int i=0; i<3; i++){
			for(unsigned int j=0; j<3; j++){
				if(i==j){
					TS_ASSERT_DELTA(1., camera.K()[i][j], 1.0e-10);
					TS_ASSERT_DELTA(1., camera.R()[i][j], 1.0e-10);
					TS_ASSERT_DELTA(1., camera.M()[i][j], 1.0e-10);
					TS_ASSERT_DELTA(1., camera.P()[i][j], 1.0e-10);
				} else{
					TS_ASSERT_DELTA(0., camera.K()[i][j], 1.0e-10);
					TS_ASSERT_DELTA(0., camera.R()[i][j], 1.0e-10);
					TS_ASSERT_DELTA(0., camera.M()[i][j], 1.0e-10);
					TS_ASSERT_DELTA(0., camera.P()[i][j], 1.0e-10);
				}
			}
			TS_ASSERT_DELTA(0., camera.P()[i][3], 1.0e-10);
		}
		//std::cerr<<"Fin testDefaultConstructor"<<std::endl;
	}

	void testDecompose( void ) {
		//std::cerr<<"Ici testDecompose"<<std::endl;
		// build a projection matrix
		kn::Matrix<double> P(3,4);
		kn::Matrix3x3d K;
		kn::Matrix3x3d R;
		kn::Vector4d   C;
		buildTestMatrix(P,K,R,C);

		// constructor
		kn::ProjectiveCamera camera(P);

		// check
		for(unsigned int i=0; i<3; i++)
		{
			for(unsigned int j=0; j<3; j++)
			{
				TS_ASSERT_DELTA(K[i][j], camera.K()[i][j], 1.0e-10);
				TS_ASSERT_DELTA(R[i][j], camera.R()[i][j], 1.0e-10);
			}
			TS_ASSERT_DELTA(C[i], camera.C()[i], 1.0e-10);
		}
		//std::cerr<<"Fin testDecompose"<<std::endl;
	}

};


/*
 * End of Anti-doublon
 */
#endif
