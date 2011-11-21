/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * ioHDRTest.hpp created in 01 2009.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the libIMAC-loader.
 *
 * The libIMAC-loader is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The libIMAC-loader is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_IMAGE__IMAGELOADERHDRTEST_HPP__
#define __OPENKN_IMAGE__IMAGELOADERHDRTEST_HPP__

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
#include <OpenKN/image/Image.hpp>
#include <OpenKN/image/ioHDR.hpp>


/*
 * Class definition
 */
class ioHDRTest : public CxxTest::TestSuite {
public:

	void testLoadHDR( void ) {
			//std::cerr<<"HELLO WORLD loadHDR1"<<std::endl;

			// Some usefull variables
			int hdr_type = -1;
			// Test for exception rising
			try {
				kn::Image<float> testimage;
				//std::vector< >  testimages;
				//testimages.resize(20);

				//std::cerr<<"********* TEST unknown file"<<std::endl;
				// ******************** Test for non existing image  ***********************
				// *************************************************************************
				TS_ASSERT_THROWS(kn::loadHDR(testimage,"./ImageLoaderHDRTestData/unknown.hdr"),kn::ImageException);
				
				// ******************** Test for handling COLOR Image  *********************
				// *************************************************************************
				// VILETTE IMAGE
				float col[3];
				col[0] = 0.72460938f;
				col[1] = 0.73632813f;
				col[2] = 0.75195313f;
// 				std::cerr<<std::endl<<"********* TEST vilette IMAGE "<<std::endl;
				hdr_type = kn::loadHDR(testimage,"./ImageLoaderHDRTestData/Vilette_one_pixel.hdr");

				// Test good image size
				// Test four corners ...
				TS_ASSERT_EQUALS(testimage(0,0)[0],col[0]);
				TS_ASSERT_EQUALS(testimage(0,0)[1],col[1]);
				TS_ASSERT_EQUALS(testimage(0,0)[2],col[2]);
// 				std::cerr<<"Sample 0,0 : "<<testimage(0,0)[0]<<"/"<<testimage(0,0)[1]<<"/"<<testimage(0,0)[2]<<std::endl;
// 				std::cerr<<"********* Reached"<<std::endl;
			}
			catch (kn::ImageException &e) {
				TS_WARN("WE GOT EXCEPTION !");
				TS_WARN(e.errorString());
			}
		}
};

/*
 * End of Anti-doublon
 */
#endif
