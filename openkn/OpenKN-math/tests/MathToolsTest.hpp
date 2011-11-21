/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * mathToolsTest.hpp created in 10 2008.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-math.
 *
 * The OpenKraken-math is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-math is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_MATH__MATHTOOLSTEST_HPP__
#define __OPENKN_MATH__MATHTOOLSTEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/math/MathTools.hpp>

/*
 * Class definition
 */
class MathToolsTest: public CxxTest::TestSuite{
  public:

    void testDegToRad(void){
		TS_ASSERT_EQUALS(kn::degToRad(90.0f),kn::PI/2.0f);
		TS_ASSERT_EQUALS(kn::degToRad(0.0f),0.0f);
    }

    void testRadToDeg(void){
		TS_ASSERT_EQUALS(kn::radToDeg(kn::PI),180.0f);
		TS_ASSERT_EQUALS(kn::radToDeg(kn::PI/2.0),90.0f);
    }

    void testPythag(void){
		TS_ASSERT_EQUALS(kn::pythag(0.0,5.0),5.0);
		TS_ASSERT_EQUALS(kn::pythag(-5.0,0.0),5.0);
		TS_ASSERT_DELTA(kn::pythag(3.0,5.0),sqrt(3.0*3.0+5.0*5.0),0.000000000001);
		TS_ASSERT_EQUALS(kn::pythag(9.0,-7.0),sqrt(7.0*7.0+9.0*9.0));
    }

    void testSetSign(void){
		TS_ASSERT_EQUALS(kn::setSign(-3,5),3);
		TS_ASSERT_EQUALS(kn::setSign(3,-5),-3);
    }

    void testIsPowerOfTwo(void){
		TS_ASSERT(!kn::isPowerOfTwo(1023));
		TS_ASSERT(kn::isPowerOfTwo(1024));
    }

    void testCeilPowerOfTwo(void){
		TS_ASSERT_EQUALS(kn::ceilPowerOfTwo(1280),2048);
		TS_ASSERT_DIFFERS(kn::ceilPowerOfTwo(1280),1024);
    }

    void testFloorPowerOfTwo(void){
		TS_ASSERT_EQUALS(kn::floorPowerOfTwo(1280),1024);
		TS_ASSERT_DIFFERS(kn::floorPowerOfTwo(1280),2048);
    }

};

/*
 * End of Anti-doublon
 */
#endif
