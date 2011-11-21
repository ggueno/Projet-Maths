/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * tiangulationTest.hpp created in 05 2009.
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
#ifndef __OPENKN_VISION__TRIANGULATION_TEST_HPP__
#define __OPENKN_VISION__TRIANGULATION_TEST_HPP__


/*
 * External Includes
 */
#include <cxxtest/TestSuite.h>
#include <vector>


/*
 * Internal Includes
 */
#include <OpenKN/vision/ProjectiveCamera.hpp>
#include <OpenKN/vision/Triangulation.hpp>
#include <OpenKN/math/Matrix.hpp>
#include <OpenKN/math/Vector3.hpp>
#include <OpenKN/math/Vector4.hpp>


/*
 * Class definition
 */

class TriangulationTest : public CxxTest::TestSuite {
public:

	kn::ProjectiveCamera buildTestMatrix(const double &k) {
		// internal parameters (webcam style)
		kn::Matrix3x3d K;
		K.setIdentity();
		K[0][2] = 550.0;
		K[1][2] = 550.0;
		K[0][0] = 240.0;
		K[1][1] = 320.0;

		// rotation matrix on z axis and angle alpha
		double alpha = 0.0; //radian
		kn::Matrix3x3d R;
		R.setIdentity();
		R[0][0] = R[1][1] = cos(alpha);
		R[1][0] = sin(alpha);
		R[0][1] = - R[1][0];

		// translation vector
		kn::Vector4d C;
		C[0] = k;
		C[1] = C[2] = 0.0;
		C[3] = 1.0;

		return kn::ProjectiveCamera(K,R,C);
	}

	void testTriangulation2cameras( void ) {
		//std::cerr<<"Ici testTriangulation2cameras"<<std::endl;
		// camera
		kn::ProjectiveCamera P1 = buildTestMatrix(0.0);
		kn::ProjectiveCamera P2 = buildTestMatrix(20.0);

		// a 3D point
		kn::Vector<double> X(4);
		X[0] = 20.0;
		X[1] = 300.0;
		X[2] = 400.0;
		X[3] = 1.0;

		// projection
		kn::Vector3d x1(P1.project(X));
		kn::Vector3d x2(P2.project(X));

		// triangulation
		kn::Vector4d Xp = kn::linearTriangulation(P1.P(), P2.P(), x1, x2);

		// check
		for(unsigned int i=0; i<4; i++)
			TS_ASSERT_DELTA(X[i], Xp[i], 1.0e-10);
		//std::cerr<<"Fin testTriangulation2cameras"<<std::endl;
	}


	void testTriangulationMoreCameras( void ) {
		//std::cerr<<"Ici testTriangulationMoreCameras"<<std::endl;
		// camera
		std::vector<kn::Matrix<double> > camList;
		const int nbCamera = 10;
		for(int i=0; i<nbCamera; i++)
			camList.push_back(buildTestMatrix(5.0*i).P());

		// a 3D point
		kn::Vector4d X;
		X[0] = 20.0;
		X[1] = 300.0;
		X[2] = 400.0;
		X[3] = 1.0;

		// projection
		std::vector<kn::Vector3d > pixelList;
		for(int i=0; i<nbCamera; i++){
			kn::Vector3d tmp = (camList[i] * X);
			tmp.setHomogeneousNormalForm();
			pixelList.push_back(tmp);
		}

		// triangulation
		kn::Vector4d Xp = kn::linearTriangulation(camList, pixelList);

		// check
		for(unsigned int i=0; i<4; i++)
			TS_ASSERT_DELTA(X[i], Xp[i], 1.0e-10);
		
		//std::cerr<<"Fin testTriangulationMoreCameras"<<std::endl;
	}
	
};


/*
 * End of Anti-doublon
 */
#endif
