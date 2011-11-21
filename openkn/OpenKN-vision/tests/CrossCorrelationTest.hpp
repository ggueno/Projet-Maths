/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * CrossCorrelationTest.hpp created in 03 2010.
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
#ifndef __OPENKN_VISION__CROSS_CORRELATION_TEST_HPP__
#define __OPENKN_VISION__CROSS_CORRELATION_TEST_HPP__

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
#include <OpenKN/vision/CrossCorrelation.hpp>
#include <OpenKN/image/Image.hpp>
#include <OpenKN/image/ImageGS.hpp>
#include <OpenKN/image/ioJPG.hpp>
#include <OpenKN/math/Vector3.hpp>

/*
 * Class definition
 */

class CrossCorrelationTest : public CxxTest::TestSuite {
  public:

		void testCrossCorrelation(){
			kn::Image<unsigned char> ref;
			kn::loadJPG(ref,"inputData/crossRef.jpg");
			kn::Image<unsigned char> neg;
			kn::loadJPG(neg,"inputData/crossNeg.jpg");
			kn::Image<unsigned char> blur;
			kn::loadJPG(blur,"inputData/crossBlur.jpg");
			kn::Image<unsigned char> light;
			kn::loadJPG(light,"inputData/crossLight.jpg");
			kn::Image<unsigned char> contrast;
			kn::loadJPG(contrast,"inputData/crossContrast.jpg");

			kn::Vector2i window;
			window.x()=98;
			window.y()=98;
			kn::Vector3d center;
			center.x()=window.x()/2;
			center.y()=window.y()/2;
			center.z()=1;
			double score=0;

	//      std::cout<<std::endl;

			score = kn::crossCorrelation(ref, ref,  0);
			TS_ASSERT_DELTA(score, 1.0, 10e-15);
	//      std::cout<<" Ref -> Ref : "<<score<<std::endl;


			score = crossCorrelationRGB(
									ref, center, //image 1
									ref, center, //image 2
									window );    //window size
			TS_ASSERT_DELTA(score, 1.0, 10e-15);
	//      std::cout<<" Ref -> Ref : "<<score<<std::endl;

			score = crossCorrelationGS(
									ref, center, //image 1
									ref, center, //image 2
									window );    //window size
			TS_ASSERT_DELTA(score, 1.0, 10e-15);
	//      std::cout<<" Ref -> Ref : "<<score<<std::endl;

			score = crossCorrelation(
									ref, center, //image 1
									ref, center, //image 2
									window,	   //window size
									0);	   //channel
			TS_ASSERT_DELTA(score, 1.0, 10e-15);
	//      std::cout<<" Ref -> Ref : "<<score<<std::endl;

			score = crossCorrelation(
									ref, center, //image 1
									neg, center, //image 2
									window,	   //window size
									0);	   //channel
			TS_ASSERT_DELTA(score, -1.0, 10e-5);
	//      std::cout<<" Ref -> Neg : "<<score<<std::endl;

			score = crossCorrelation(
									ref, center, //image 1
									blur, center, //image 2
									window,	   //window size
									0);	   //channel
			TS_ASSERT_DELTA(score, 0.95, 0.025);
	//      std::cout<<" Ref -> Blur : "<<score<<std::endl;

			score = crossCorrelation(
									ref, center, //image 1
									light, center, //image 2
									window,	   //window size
									0);	   //channel
			TS_ASSERT_DELTA(score, 0.95, 0.025);
	//      std::cout<<" Ref -> Light : "<<score<<std::endl;

			score = crossCorrelation(
									ref, center, //image 1
									contrast, center, //image 2
									window,	   //window size
									0);	   //channel
			TS_ASSERT_DELTA(score, 0.95, 0.025);
	//      std::cout<<" Ref -> Contrast : "<<score<<std::endl;

			window.x()=80;
			window.y()=35;

			score = kn::crossCorrelation(ref, ref,  0);
			TS_ASSERT_DELTA(score, 1.0, 10e-15);
	//      std::cout<<" Ref -> Ref with rectangular window : "<<score<<std::endl;

	}

};


/*
 * End of Anti-doublon
 */
#endif
