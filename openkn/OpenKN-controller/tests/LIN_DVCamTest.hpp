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
#ifndef __OpenKN_CONTROLLER__LIN_DVCAMTEST_HPP__
#define __OpenKN_CONTROLLER__LIN_DVCAMTEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <LIN_DVCam.hpp>

/*
 * Class definition
 */

class DVCamTest : public CxxTest::TestSuite {
public:
	void testDVCamTest( void ) {

		kn::DVCam * dvcam = 0;
		try{
			dvcam = new kn::DVCam();
			TS_ASSERT(dvcam != 0);

            dvcam->openDevice(0);

			unsigned char * data = dvcam->getImage();
			TS_ASSERT(data != 0);

			delete dvcam;

		}catch(kn::ControllerException e){
            // either dvcam is not pluged or switch on or you don't have permissions on /dev/dv1394/* and /dev/raw1394
            TS_WARN(e.errorString());
		}
	}

};


/*
 * End of Anti-doublon
 */
#endif
