/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * CameraCalibrationTest.hpp created in 03 2009.
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
#ifndef __OPENKN_VISION__CAMERA_CALIBRATION_TEST_HPP__
#define __OPENKN_VISION__CAMERA_CALIBRATION_TEST_HPP__

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
#include <OpenKN/vision/CameraCalibrationDLT.hpp>
#include <OpenKN/math/Matrix.hpp>
#include <OpenKN/math/Matrix3x3.hpp>
#include <OpenKN/math/Vector4.hpp>


/*
 * Class definition
 */

class CameraCalibrationTest : public CxxTest::TestSuite {
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
		P.setColumn(3,-R*C.getUnhomogeneous());

		// K contribution
		P = K * P;
	}


	void test3d2dConstructor( void ) {
		// build a projection matrix
		kn::Matrix<double> P(3,4);
		kn::Matrix3x3d K;
		kn::Matrix3x3d R;
		kn::Vector4d C;
		buildTestMatrix(P,K,R,C);

		// build a set of pair of 3d-2d correspondance
		std::vector<std::pair<kn::Vector4d, kn::Vector3d> > correspondanceList;
		const unsigned int nbCorrespondance = 200; // at least 6
		unsigned int i= 0;
		srandom(0); // everytime the same order
		while(i < nbCorrespondance){
			// create a 3d point
			kn::Vector4d pt3d;
			for(unsigned int j=0; j<3; j++) {
				pt3d[j] = (1000.0*random()/(double)RAND_MAX) - 500.0;
			}
			pt3d[3] = 1.0;

			// project this point on a 2d pixel
			kn::Vector3d pix2d = (P*pt3d);
			pix2d.setHomogeneousNormalForm();

			// if the pixel position is "standard" (acceptable image resolution)
			if(fabs(pix2d[0]) < 1000.0 && fabs(pix2d[1]) < 1000.0 ){
					correspondanceList.push_back(std::pair<kn::Vector4d, kn::Vector3d>(pt3d,pix2d));
					i++;
			}
		}

		// ProjectiveCamera constructor
		kn::ProjectiveCamera camera(cameraCalibrationDLT(correspondanceList));

		// scale the projective matrices
		kn::Matrix<double> cameraP( camera.P() / camera.P()[2][3] );
		P = P / P[2][3];

		//std::cout << std::endl << cameraP << std::endl;
		//std::cout << std::endl << P << std::endl;

		// data check
		for(unsigned int i=0; i<3; i++)
			for(unsigned int j=0; j<4; j++)
				TS_ASSERT_DELTA(cameraP[i][j], P[i][j], 1.0e-10);
	}

};


/*
 * End of Anti-doublon
 */
#endif
