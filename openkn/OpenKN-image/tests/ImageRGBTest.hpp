/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * ImageRGBTest.hpp created in 09 2008.
 * Mail : biri@univ-mlv.fr					  
 *													   
 * This file is part of the OpenKraken-image.
 *
 * The OpenKraken-image is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-image is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_IMAGE__IMAGERGBTEST_HPP__
#define __OPENKN_IMAGE__IMAGERGBTEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <cstring>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/image/ImageRGB.hpp>

/*
 * Class definition
 */

class ImageRGBTest : public CxxTest::TestSuite {
public:
	void testConstructorWithoutParameters( void ) {
		kn::ImageRGB<unsigned char>	 i;
	  
		TS_ASSERT_EQUALS( i.width(), 0);
		TS_ASSERT_EQUALS( i.height(), 0);
		TS_ASSERT_EQUALS( i.nbChannel(), 3);
		TS_ASSERT_EQUALS( i.size(), 0);
	}


	void testConstructorWithFourParameters( void ) {
		unsigned char static_buffer[] = {0,1,2,3,4,5,6,7,8,9,10,11};
		unsigned char * dyn_buffer = new unsigned char[12];
		memcpy(dyn_buffer,static_buffer,12*sizeof(char));
		kn::ImageRGB<unsigned char>	* i = new kn::ImageRGB<unsigned char>(2,2,dyn_buffer);
	  
		TS_ASSERT_EQUALS( i->width(), 2);
		TS_ASSERT_EQUALS( i->height(), 2);
		TS_ASSERT_EQUALS( i->nbChannel(), 3);
		TS_ASSERT_EQUALS((*i)(0,0)[0], 0);
		TS_ASSERT_EQUALS((*i)(0,1)[1], 7);
	  
		delete i;	   
	}

	void testCopyConstructor(void) {
		unsigned char static_buffer[] = {0,1,2,3,4,5,6,7,8,9,10,11};
		unsigned char * dyn_buffer = new unsigned char[12];
		memcpy(dyn_buffer,static_buffer,12*sizeof(char));
		kn::ImageRGB<unsigned char>	i(2,2,dyn_buffer);
		kn::ImageRGB<unsigned char>	i2 = i;
	
		TS_ASSERT_EQUALS( i2.width(), 2);
		TS_ASSERT_EQUALS( i2.height(), 2);
		TS_ASSERT_EQUALS( i2.nbChannel(), 3);
		TS_ASSERT_EQUALS(i2(0,0)[0], 0);
		TS_ASSERT_EQUALS(i2(0,1)[1], 7);
	}
};


/*
 * End of Anti-doublon
 */
#endif

