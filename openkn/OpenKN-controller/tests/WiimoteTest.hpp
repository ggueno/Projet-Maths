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
#ifndef __OpenKN_CONTROLLER__WIIMOTETEST_HPP__
#define __OpenKN_CONTROLLER__WIIMOTETEST_HPP__

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
#include <WiimoteManager.hpp>

/*
 * Class definition
 */

class WiimoteTest : public CxxTest::TestSuite {
public:
	void testWiimoteTest( void ) {

        kn::WiimoteManager *manager = 0;

		try{
			
            manager = new kn::WiimoteManager();
            
			TS_ASSERT(manager != 0);

			delete manager;

		}catch(kn::ControllerException e){
            // no wiimote detected
            TS_WARN(e.errorString());
		}
	}

};


/*
 * End of Anti-doublon
 */
#endif
