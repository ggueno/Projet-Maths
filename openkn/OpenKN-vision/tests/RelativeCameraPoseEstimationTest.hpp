/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * RelativeCameraPoseEstimationTest.hpp created in 05 2011.
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
#ifndef __OPENKN_VISION__RELATIVE_CAMERA_POSE_ESTIMATION_TEST_HPP__
#define __OPENKN_VISION__RELATIVE_CAMERA_POSE_ESTIMATION_TEST_HPP__

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
#include <OpenKN/vision/EpipolarGeometry.hpp>
#include <OpenKN/vision/ProjectiveCamera.hpp>
#include <OpenKN/vision/RelativeCameraPoseEstimation.hpp>
#include <OpenKN/math/Matrix.hpp>
#include <OpenKN/math/Matrix3x3.hpp>
#include <OpenKN/math/Vector4.hpp>
#include <OpenKN/math/EulerAngles.hpp>


/*
 * Class definition
 */

class RelativeCameraPoseEstimationTest : public CxxTest::TestSuite {
  public:


		void testRelativeCameraPoseEstimationFromFundamental(){
		
			// prepare some know cameras P0 and P1

			// K1 => basic internal parameters for a 800x600 image
			kn::Matrix3x3<double> K;
			K.setIdentity();
			K(0,0) = 1000;
			K(1,1) = 1000;
			K(0,2) = 300;
			K(1,2) = 400;			
			
			// rotation matrix
			kn::Matrix3x3<double> R;
			R.setIdentity();
			
			// camera pos 
			kn::Vector4d C;
			C.fill(0.0);
			C[3] = 1.0;
			
			// cam0 
			kn::ProjectiveCamera cam0(K,R,C);
			
			
			// K2 => basic internal parameters for a 400x300 image 
			K.setIdentity();
			K(0,0) = 500;
			K(1,1) = 500;
			K(0,2) = 150;
			K(1,2) = 200;
		
			// rotation matrix	
			R = kn::eulerAngles3x3d(0.01,0.2,0.01);

			// camera pos 
			C[0] = 2.0;
			C[1] = 0.1;
			C[2] = 0.5;
			
			// cam1
			kn::ProjectiveCamera cam1(K,R,C);	


			//Generate random point in front of both cameras
			srand(0);
			std::vector<kn::Vector3d> listPts;
			unsigned int nbPoints = 100;
			for(unsigned int i=0;i<nbPoints; ++i) {

				//Point creation
				kn::Vector3d tmp;
				tmp[0] = (rand()/double(RAND_MAX)-0.5)*2.0 *2.0;
				tmp[1] = (rand()/double(RAND_MAX)-0.5)*2.0 *2.0;
				tmp[2] = (rand()/double(RAND_MAX)-0.5)*2.0 *2.0 + 5.0;

				//Test if it is in front cam0 & cam1
				if( ((tmp-cam0.C().getUnhomogeneous())*cam0.principalRay() > 0.0) && ((tmp-cam1.C().getUnhomogeneous())*cam1.principalRay() > 0.0) ){
					listPts.push_back(tmp);
					++i;
				}else std::cout << "tient?, c'est bisard ..." << std::endl;
				
			}

			// project the 3d points on the 2 cameras
			std::vector< std::pair<kn::Vector3d,kn::Vector3d> > listProjPts;
			kn::Vector3d proj0,proj1;

			for(unsigned int i=0;i<listPts.size();i++){
				proj0 = cam0.project(listPts[i].getHomogeneous(1.0));
				proj1 = cam1.project(listPts[i].getHomogeneous(1.0));
				listProjPts.push_back(std::pair<kn::Vector3d,kn::Vector3d>(proj0,proj1));
			}


			// compute the fundamental matrix between the 2 cameras
			kn::Matrix3x3d F = kn::computeFundamentalMatrixNormalized(listProjPts);

			// retrieve the camera matrix from F
			kn::ProjectiveCamera cam0Test = kn::ProjectiveCamera();
			kn::ProjectiveCamera cam1Test = kn::ProjectiveCamera();
			kn::poseEstimationFromFundamental(F, cam0.K(), cam1.K(), listProjPts[0].first, listProjPts[0].second, cam0Test, cam1Test);

			//Test K
			for(unsigned int i=0;i<3;i++) {
				for(unsigned int j=0;j<3;j++) {
					TS_ASSERT_DELTA(cam0.K()[i][j], cam0Test.K()[i][j], 1.0e-8);
					TS_ASSERT_DELTA(cam1.K()[i][j], cam1Test.K()[i][j], 1.0e-8);
				}
			}

			//Test R
			for(unsigned int i=0;i<3;i++){
				for(unsigned int j=0;j<3;j++){
					TS_ASSERT_DELTA(cam0.R()[i][j], cam0Test.R()[i][j], 1.0e-8);
					TS_ASSERT_DELTA(cam1.R()[i][j], cam1Test.R()[i][j], 1.0e-8);
				}
			}			

			//Test C
			kn::Vector3d normalizedC1     = cam1.C().getUnhomogeneous().getNormalized();
			kn::Vector3d normalizedC1Test = cam1Test.C().getUnhomogeneous().getNormalized();
			for(unsigned int i=0;i<3;i++){
				TS_ASSERT_DELTA(cam0.C()[i], cam0Test.C()[i], 1.0e-8);
				TS_ASSERT_DELTA(normalizedC1[i], normalizedC1Test[i], 1.0e-8);
			}
		}

};


/*
 * End of Anti-doublon
 */
#endif
