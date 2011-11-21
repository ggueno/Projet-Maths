/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * LIN_V4L2WebcamTest.hpp created in 09 2008.
 * Mail : biri@univ-mlv.fr					  
 *													   
 * This file is part of the OpenKraken-controller.
 *
 * The OpenKraken-controller is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-controller is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_CONTROLLER__LIN_V4L2WEBCAMTEST_HPP__
#define __OPENKN_CONTROLLER__LIN_V4L2WEBCAMTEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <LIN_V4L2Webcam.hpp>

/*
 * Class definition
 */

class V4L2WebcamTest : public CxxTest::TestSuite {
public:
	void testWebcamAsV4L2WebcamTest( void ) {

		kn::CameraController * webcam = 0;
        std::string fd("/dev/video0");
		try{
			webcam = new kn::V4L2Webcam();
			TS_ASSERT(webcam != 0);

            webcam->openDevice();

			unsigned char * data = webcam->getImage();
			TS_ASSERT(data != 0);

			delete webcam;

		}catch(kn::ControllerException e){
			FILE *fp = fopen(fd.c_str(),"r");
			TS_ASSERT(fp==0);
			if(fp)
				TS_WARN(e.errorString());
		}
	}

	void testV4L2WebcamTest( void ) {

		kn::V4L2Webcam * webcam = 0;
        std::string fd("/dev/video0");
		try{
			webcam = new kn::V4L2Webcam();
			TS_ASSERT(webcam != 0);

            webcam->openDevice(fd);

			unsigned char * data = webcam->getImage();
			TS_ASSERT(data != 0);

			delete webcam;

		}catch(kn::ControllerException e){
			FILE *fp = fopen(fd.c_str(),"r");
			TS_ASSERT(fp==0);
			if(fp)
				TS_WARN(e.errorString());
		}
	}


};


/*
 * End of Anti-doublon
 */
#endif
