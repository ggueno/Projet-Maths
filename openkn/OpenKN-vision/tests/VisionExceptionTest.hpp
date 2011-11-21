/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * VisionExceptionTest.hpp created in 02 2009.
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
#ifndef __OPENKN_VISION__VISIONEXCEPTIONTEST_HPP__
#define __OPENKN_VISION__VISIONEXCEPTIONTEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/vision/VisionException.hpp>

/*
 * Class definition
 */

class VisionExceptionTest : public CxxTest::TestSuite {
	public:
		void testConstructorWithTwoParameters( void ) {
				kn::VisionException e("World!","Hello,");
				TS_ASSERT_EQUALS( e.errorString(), "(Hello,) Error : World!");
		}

		void testOperatorChev( void ) {
			kn::VisionException e("World!","Hello,");
			std::stringstream sstr;
			std::string strref="(Hello,) Error : World!";
			sstr << e;
			TS_ASSERT_EQUALS( sstr.str() , strref);
		}
};


/*
 * End of Anti-doublon
 */
#endif
