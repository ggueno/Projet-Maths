/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * ImageTest.hpp created in 09 2008.
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
#ifndef __OPENKN_IMAGE__IMAGETEST_HPP__
#define __OPENKN_IMAGE__IMAGETEST_HPP__

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
#include <OpenKN/image/Image.hpp>

/*
 * Class definition
 */

class ImageTest : public CxxTest::TestSuite {
public:
	void testConstructorWithoutParameters( void ) {
		//std::cerr<<"HELLO WORLD im1"<<std::endl;

		kn::Image<unsigned char>	 i;
	  
		TS_ASSERT_EQUALS( i.width(), 0);
		TS_ASSERT_EQUALS( i.height(), 0);
		TS_ASSERT_EQUALS( i.nbChannel(), 0);
		TS_ASSERT_EQUALS( i.size(), 0);
	}

	void testConstructorWithFourParameters( void ) {
		unsigned char static_buffer[] = {0,1,2,3,4,5,6,7,8,9,10,11};
		unsigned char * dyn_buffer = new unsigned char[12];
		memcpy(dyn_buffer,static_buffer,12*sizeof(unsigned char));
		kn::Image<unsigned char>	 * i = new kn::Image<unsigned char>(2,2,3,dyn_buffer);
	  
		TS_ASSERT_EQUALS( i->width(), 2);
		TS_ASSERT_EQUALS( i->height(), 2);
		TS_ASSERT_EQUALS( i->nbChannel(), 3);
		TS_ASSERT_EQUALS((*i)(0,0)[0], 0);
		TS_ASSERT_EQUALS((*i)(0,1)[1], 7);

		float static_bufferf[] = {0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,10.0f,11.0f};
		float * dyn_bufferf = new float[12];
		memcpy(dyn_bufferf,static_bufferf,12*sizeof(float));
		kn::Image<float>	 iF(2,2,3,dyn_bufferf);

		TS_ASSERT_EQUALS( iF.width(), 2);
		TS_ASSERT_EQUALS( iF.height(), 2);
		TS_ASSERT_EQUALS( iF.nbChannel(), 3);
		TS_ASSERT_EQUALS(iF(0,0)[0], 0.0f);
		TS_ASSERT_EQUALS(iF(0,1)[1], 7.0f);				
	  
		delete i;
	}

	void testCopyConstructor(void) {
		unsigned char static_buffer[] = {0,1,2,3,4,5,6,7,8,9,10,11};
		unsigned char * dyn_buffer = new unsigned char[12];
		memcpy(dyn_buffer,static_buffer,12*sizeof(unsigned char));
		kn::Image<unsigned char>	 i(2,2,3,dyn_buffer);
		kn::Image<unsigned char>	 i2 = i;
	
		TS_ASSERT_EQUALS( i2.width(), 2);
		TS_ASSERT_EQUALS( i2.height(), 2);
		TS_ASSERT_EQUALS( i2.nbChannel(), 3);
		TS_ASSERT_EQUALS(i2(0,0)[0], 0);
		TS_ASSERT_EQUALS(i2(0,1)[1], 7);
	}
	
	void testOperatorParenthesis2Parameters(void) {
		unsigned char static_buffer[] = {0,1,2,3,4,5,6,7,8,9,10,11};
		unsigned char * dyn_buffer = new unsigned char[12];
		memcpy(dyn_buffer,static_buffer,12*sizeof(char));
		kn::Image<unsigned char>	 i(2,2,3,dyn_buffer);
		
		TS_ASSERT_THROWS_NOTHING(i(0,0));
		for(int j=0;j<4;j++) {
			TS_ASSERT_SAME_DATA( i(j%6,j/6), static_buffer+3*j, 3);
		}
	}

	
	void testContains(void) {
        unsigned int w = 20;
        unsigned int h = 40;
        kn::Image<unsigned char> image(w,h,3);

        int posX = 10;
        int posY = 10;
		TS_ASSERT(image.contains(posX,posY));

		posX = 10;
		posY = 200;
		TS_ASSERT(!image.contains(posX,posY));

		posX = 200;
		posY = 10;
		TS_ASSERT(!image.contains(posX,posY));

		posX = -200;
		posY = 10;
		TS_ASSERT(!image.contains(posX,posY));

		posX = 10;
		posY = -10;
		TS_ASSERT(!image.contains(posX,posY));
	}

	void testOperatorParenthesis3Parameters(void) {
		unsigned char static_buffer[] = {0,1,2,3,4,5,6,7,8,9,10,11};
		unsigned char * dyn_buffer = new unsigned char[12];
		memcpy(dyn_buffer,static_buffer,12*sizeof(char));
		kn::Image<unsigned char>	 i(2,2,3,dyn_buffer);
		
		TS_ASSERT_THROWS_NOTHING(i(0,0,0));
		for(int j=0;j<12;j++) {
			TS_ASSERT_EQUALS( i((j%6)/3,j/6,(j%6)%3), j);
		}
	}

	void testOperatorEqualsCopy(void) {
	        
		unsigned char buffer[] = {0,1,2,3,4,5,6,7,8,9,10,11};
		kn::Image<unsigned char> i1(2,2,3,buffer);
		
		kn::Image<unsigned char> i2(2,2,3);
		i2 = i1;

		for(int j=0;j<12;j++) {
			TS_ASSERT_EQUALS( i1.begin()[j], i2.begin()[j]);
		}
	}

	void testImageBuilding(void) {
		float static_bufferf[] = {0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,10.0f,11.0f};
		float * dyn_bufferf = new float[12];
		memcpy(dyn_bufferf,static_bufferf,12*sizeof(float));
		kn::Image<float>	 iF(2,2,3,dyn_bufferf);
		kn::Image<float>	 iF2(2,4,3);
		kn::Image<float>	 iF3;

		TS_ASSERT_THROWS(iF2=iF, kn::ImageException);
		TS_ASSERT_THROWS_NOTHING(iF3=iF);
		TS_ASSERT_EQUALS(iF(0,0)[2], iF3(0,0)[2]);
		iF3(0,0,2) = 5.5;
		TS_ASSERT_DIFFERS(iF(0,0)[2], iF3(0,0)[2]);
	}

	// Test function for the two at functions
	void testAtFunctions() {
		unsigned char static_buffer[] = {0,1,2,3,4,5,6,7,8,9,10,11};
		unsigned char * dyn_buffer = new unsigned char[12];
		memcpy(dyn_buffer,static_buffer,12*sizeof(char));
		kn::Image<unsigned char>	 i(2,2,3,dyn_buffer);

		TS_ASSERT_THROWS(i.at(1,10), kn::ImageException);
		TS_ASSERT_THROWS(i.at(10,1), kn::ImageException);
		TS_ASSERT_THROWS(i.at(10,10), kn::ImageException);
		TS_ASSERT_SAME_DATA( i.at(0,0), static_buffer, 3);
		TS_ASSERT_EQUALS(i.at(1,1,0),9);
		TS_ASSERT_THROWS(i.at(1,1,4), kn::ImageException);
	}

	void testFill() {
                const unsigned int  w = 5;
                const unsigned int  h = 5;
		const unsigned char value = 120;
		
	        kn::Image<unsigned char> image(w,h,3);
		image.fill(value);

		for(unsigned int i=0; i<w; i++)
		  for(unsigned int j=0; j<h; j++)
		    TS_ASSERT_EQUALS(image.at(i,j,0),value);
	}

	void testFlip() {
                const unsigned int  w = 5;
                const unsigned int  h = 10;
		kn::Image<unsigned char> image(w,h,3);

		// fill the image
		for(unsigned int i=0; i<w; i++)
		  for(unsigned int j=0; j<h; j++)
		    for(unsigned int c=0; c<3; c++)
		      image(i,j)[c] = (i+10*j)%255;

		// flip the image
		kn::Image<unsigned char> imageFlipped(image);
		imageFlipped.flip();

		// check
		for(unsigned int i=0; i<w; i++)
		  for(unsigned int j=0; j<h; j++)
		    for(unsigned int c=0; c<3; c++)
		      TS_ASSERT_EQUALS(image.at(i,j,c),imageFlipped.at(i,h-j-1,c));
	}

	void testFlop() {
                const unsigned int  w = 5;
                const unsigned int  h = 10;
		kn::Image<unsigned char> image(w,h,3);

		// fill the image
		for(unsigned int i=0; i<w; i++)
		  for(unsigned int j=0; j<h; j++)
		    for(unsigned int c=0; c<3; c++)
		      image(i,j)[c] = (i+10*j)%255;

		// flop the image
		kn::Image<unsigned char> imageFlopped(image);
		imageFlopped.flop();

		// check
		for(unsigned int i=0; i<w; i++)
		  for(unsigned int j=0; j<h; j++)
		    for(unsigned int c=0; c<3; c++)
		      TS_ASSERT_EQUALS(image.at(i,j,c),imageFlopped.at(w-i-1,j,c));
	}
	
	void testRotate() {
                const unsigned int  w = 5;
                const unsigned int  h = 10;
		kn::Image<unsigned char> image(w,h,3);

		// fill the image
		for(unsigned int i=0; i<w; i++)
		  for(unsigned int j=0; j<h; j++)
		    for(unsigned int c=0; c<3; c++)
		      image(i,j)[c] = (i+10*j)%255;

		// flop the image
		kn::Image<unsigned char> imageRotated(image);
		imageRotated.rotate();

		// check
		TS_ASSERT_EQUALS(imageRotated.width(),h);
		TS_ASSERT_EQUALS(imageRotated.height(),w);
		
		for(unsigned int i=0; i<w; i++)
		  for(unsigned int j=0; j<h; j++)
		    for(unsigned int c=0; c<3; c++)
		      TS_ASSERT_EQUALS(image.at(i,j,c),imageRotated.at(j,w-1-i,c));
	}
	
	
	void testRotateInverse() {
                const unsigned int  w = 5;
                const unsigned int  h = 10;
		kn::Image<unsigned char> image(w,h,3);

		// fill the image
		for(unsigned int i=0; i<w; i++)
		  for(unsigned int j=0; j<h; j++)
		    for(unsigned int c=0; c<3; c++)
		      image(i,j)[c] = (i+10*j)%255;

		// flop the image
		kn::Image<unsigned char> imageRotated(image);
		imageRotated.rotateInverse();

		// check
		TS_ASSERT_EQUALS(imageRotated.width(),h);
		TS_ASSERT_EQUALS(imageRotated.height(),w);
		
		for(unsigned int i=0; i<w; i++)
		  for(unsigned int j=0; j<h; j++)
		    for(unsigned int c=0; c<3; c++)
		      TS_ASSERT_EQUALS(image.at(i,j,c),imageRotated.at(h-1-j,i,c));
	}

	void testGetSubImage() {
                const unsigned int  w = 5;
                const unsigned int  h = 10;
		kn::Image<unsigned char> image(w,h,3);

		// fill the image
		for(unsigned int i=0; i<w; i++)
		  for(unsigned int j=0; j<h; j++)
		    for(unsigned int c=0; c<3; c++)
		      image(i,j)[c] = (i+10*j)%255;


		// get the sub image
		kn::Image<unsigned char> sub(3,3,3);
		image.getSubImage(2,2,sub);

		// check
		for(unsigned int i=0; i<3; i++)
		  for(unsigned int j=0; j<3; j++)
		    for(unsigned int c=0; c<3; c++)
		      TS_ASSERT_EQUALS(image.at(i+2,j+2,c),sub.at(i,j,c));
	}
	
	void testSetSubImage() {
                const unsigned int  w = 5;
                const unsigned int  h = 10;
		kn::Image<unsigned char> image(w,h,3);

		image.fill(100);


		// get the sub image
		kn::Image<unsigned char> sub(3,3,3);
		sub.fill(0);
		image.setSubImage(2,2,sub);

		// check
		for(unsigned int i=0; i<3; i++)
		  for(unsigned int j=0; j<3; j++)
		    for(unsigned int c=0; c<3; c++)
		      TS_ASSERT_EQUALS(image.at(i+2,j+2,c),sub.at(i,j,c));
	}
	
	
};


/*
 * End of Anti-doublon
 */
#endif

