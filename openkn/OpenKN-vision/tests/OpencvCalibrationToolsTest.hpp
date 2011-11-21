/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * OpenCVcalibrationToolsTest.hpp created in 03 2009.
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
#ifndef __OPENKN_VISION__OPENCV_CALIIBRATION_TOOLS_TEST_HPP__
#define __OPENKN_VISION__OPENCV_CALIIBRATION_TOOLS_TEST_HPP__

/*
 * External Includes
 */
//#include <iostream>
#include <cstring>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/vision/OpencvCalibrationTools.hpp>
#include <OpenKN/vision/ProjectiveCamera.hpp>
#include <OpenKN/vision/CameraCalibrationZhang.hpp>
#include <OpenKN/util/StringEnumerator.hpp>
#include <OpenKN/math/Matrix3x3.hpp>
#include <OpenKN/image/ImageRGB.hpp>
#include <OpenKN/image/ioJPG.hpp>
#include <OpenKN/image/ioPPM.hpp>

/*
 * Class definition
 */

class OpenCVcalibrationToolsTest : public CxxTest::TestSuite {
	public:

		void testDetection( void ) {
			// load images
			std::vector<kn::ImageRGB8u> imageList;
			for(unsigned int i=0; i<= 12; i++){
				kn::ImageRGB8u image;
				kn::loadJPG(image,kn::stringEnumerator("inputData/capture",i,4,".jpg"));
				imageList.push_back(image);
			}

			// homography list
			std::vector<kn::Matrix3x3d> Hlist;

			// detect the corners
			for(unsigned int i=0; i<= 12; i++){
				// 2d-2d correpondance list
				std::vector< std::pair<kn::Vector3d,kn::Vector3d> > correspondanceList;

				// detect the corners
				kn::opencvChessboardDetection(imageList[i],
										correspondanceList,
										6, 8,
										3.0, // cm
										true);

				if(correspondanceList.size() > 3) {
					Hlist.push_back(kn::computeHomographyNormalized(correspondanceList));
					kn::savePPM(imageList[i],kn::stringEnumerator("outputData/chessboard",i,4,".ppm"));
				}
			}
			
			// calibrate the camera
			TS_ASSERT_LESS_THAN_EQUALS(3,Hlist.size());
			kn::ProjectiveCamera P(kn::cameraCalibrationZhang(Hlist));
			//std::cout << "\n" << P.K();

			// check K matrix
			TS_ASSERT_DELTA(P.K()[1][0], 0.0, 1.0e-10);     // 0.0
			TS_ASSERT_DELTA(P.K()[2][0], 0.0, 1.0e-10);     // 0.0
			TS_ASSERT_DELTA(P.K()[2][1], 0.0, 1.0e-10);     // 0.0
			TS_ASSERT_DELTA(P.K()[2][2], 1.0, 1.0e-10);     // 1.0
			TS_ASSERT_DELTA(P.K()[0][0], 520.0, 30.0);      // focal X (pixel unit)
			TS_ASSERT_DELTA(P.K()[1][1], 520.0, 30.0);      // focal Y (pixel unit)
			TS_ASSERT_DELTA(P.K()[0][1], 0.0, 5.0);         // skew = near 0.0
			TS_ASSERT_DELTA(P.K()[0][2], 640.0/2.0, 20.0);  // principal point (near the middle of the image)
			TS_ASSERT_DELTA(P.K()[1][2], 480.0/2.0, 20.0);  // principal point (near the middle of the image)

			//std::cerr<<"Fin testDetection"<<std::endl;
		}
};


/*
 * End of Anti-doublon
 */
#endif
