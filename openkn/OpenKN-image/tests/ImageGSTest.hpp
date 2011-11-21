/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * ImageGSTest.hpp created in 09 2008.
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
#ifndef __OPENKN_IMAGE__IMAGEGSTEST_HPP__
#define __OPENKN_IMAGE__IMAGEGSTEST_HPP__

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
#include <OpenKN/image/ImageGS.hpp>

/*
 * Class definition
 */

class ImageGSTest : public CxxTest::TestSuite {
public:
	void testConstructorWithoutParameters( void ) {
		kn::ImageGS<unsigned char>	 i;
	  
		TS_ASSERT_EQUALS( i.width(), 0);
		TS_ASSERT_EQUALS( i.height(), 0);
		TS_ASSERT_EQUALS( i.nbChannel(), 1);
		TS_ASSERT_EQUALS( i.size(), 0);
	}

	void testConstructorWithFourParameters( void ) {
		unsigned char static_buffer[] = {0,1,2,3};
		unsigned char * dyn_buffer = new unsigned char[12];
		memcpy(dyn_buffer,static_buffer,12*sizeof(unsigned char));
		kn::ImageGS<unsigned char>  * i = new kn::ImageGS<unsigned char>(2,2,dyn_buffer);
	  
		TS_ASSERT_EQUALS( i->width(), 2);
		TS_ASSERT_EQUALS( i->height(), 2);
		TS_ASSERT_EQUALS( i->nbChannel(), 1);
		TS_ASSERT_EQUALS((*i)(0,0), 0);
		TS_ASSERT_EQUALS((*i)(0,1), 2);
	  
		delete i;	   
	}

	void testCopyConstructor(void) {
		unsigned char static_buffer[] = {0,1,2,3};
		unsigned char * dyn_buffer = new unsigned char[12];
		memcpy(dyn_buffer,static_buffer,12*sizeof(unsigned char));
		kn::ImageGS<unsigned char>  i(2,2,dyn_buffer);
		kn::ImageGS<unsigned char>  i2 = i;
	
		TS_ASSERT_EQUALS( i2.width(), 2);
		TS_ASSERT_EQUALS( i2.height(), 2);
		TS_ASSERT_EQUALS( i2.nbChannel(), 1);
		TS_ASSERT_EQUALS(i2(0,0), 0);
		TS_ASSERT_EQUALS(i2(0,1), 2);
	}

	void testOperatorParenthesis2Parameters(void) {
		unsigned char static_buffer[] = {0,1,2,3};
		unsigned char * dyn_buffer = new unsigned char[12];
		memcpy(dyn_buffer,static_buffer,12*sizeof(unsigned char));
		kn::ImageGS<unsigned char>  i(2,2,dyn_buffer);
		
		TS_ASSERT_THROWS_NOTHING(i(0,0));
		TS_ASSERT_EQUALS(i(1,0), 1);
	}

	void testAt(void) {
		unsigned char static_buffer[] = {0,1,2,3};
		unsigned char * dyn_buffer = new unsigned char[12];
		memcpy(dyn_buffer,static_buffer,12*sizeof(unsigned char));
		kn::ImageGS<unsigned char>  i(2,2,dyn_buffer);

		TS_ASSERT_THROWS_NOTHING(i.at(0,0));
		TS_ASSERT_EQUALS(i.at(1,0), 1);
		TS_ASSERT_THROWS(i.at(10,10), kn::ImageException);
	}


};


/*
 * End of Anti-doublon
 */
#endif

