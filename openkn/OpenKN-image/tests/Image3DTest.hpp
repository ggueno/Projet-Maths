/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * Image3DTest.hpp created in 09 2008.
 * Mail : biri@univ-mlv.fr					  
 *													   
 * This file is part of the OpenKraken-Image.
 *
 * The OpenKraken-Image is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-Image is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_IMAGE__IMAGE3DTEST_HPP__
#define __OPENKN_IMAGE__IMAGE3DTEST_HPP__

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
#include <OpenKN/image/Image3D.hpp>
#include <OpenKN/image/ImageRGB.hpp>

/*
 * Class definition
 */

class Image3DTest : public CxxTest::TestSuite {
public:
	void testConstructorWithoutParameters( void ) {
		//std::cerr<<"HELLO WORLD im1"<<std::endl;

		kn::Image3D<unsigned char>	 i;
	  
		TS_ASSERT_EQUALS( i.width(), 0);
		TS_ASSERT_EQUALS( i.height(), 0);
		TS_ASSERT_EQUALS( i.depth(), 0);
		TS_ASSERT_EQUALS( i.nbChannel(), 0);
		TS_ASSERT_EQUALS( i.size(), 0);
	}

	void testConstructorWithFiveParameters( void ) {
		unsigned char static_buffer[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		unsigned char * dyn_buffer = new unsigned char[16];
		memcpy(dyn_buffer,static_buffer,16*sizeof(unsigned char));
		kn::Image3D<unsigned char>* i = new kn::Image3D<unsigned char>(2,2,2,2,dyn_buffer);
	  
		TS_ASSERT_EQUALS( i->width(), 2);
		TS_ASSERT_EQUALS( i->height(), 2);
		TS_ASSERT_EQUALS( i->depth(), 2);
		TS_ASSERT_EQUALS( i->nbChannel(), 2);
		TS_ASSERT_EQUALS((*i)(0,0,0)[0], 0);
		TS_ASSERT_EQUALS((*i)(0,1,1)[1], 13);
		TS_ASSERT_EQUALS((*i)(1,1,0)[1], 7);

		float static_bufferf[] = {0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,10.0f,11.0f,12.0f,13.0f,14.0f,15.0f};
		float * dyn_bufferf = new float[16];
		memcpy(dyn_bufferf,static_bufferf,16*sizeof(float));
		kn::Image3D<float>	 iF(2,2,2,2,dyn_bufferf);

		TS_ASSERT_EQUALS( iF.width(), 2);
		TS_ASSERT_EQUALS( iF.height(), 2);
		TS_ASSERT_EQUALS( iF.depth(), 2);
		TS_ASSERT_EQUALS( iF.nbChannel(), 2);
		TS_ASSERT_EQUALS(iF(0,0,0)[0], 0.0f);
		TS_ASSERT_EQUALS(iF(0,1,1)[1], 13.0f);				
		TS_ASSERT_EQUALS(iF(1,1,0)[1], 7.0f);				
	  
		delete i;
	}

	void testCopyConstructor(void) {
		unsigned char static_buffer[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		unsigned char * dyn_buffer = new unsigned char[16];
		memcpy(dyn_buffer,static_buffer,16*sizeof(unsigned char));
		kn::Image3D<unsigned char> i(2,2,2,2,dyn_buffer);
	 	kn::Image3D<unsigned char>	 i2 = i;
	
		TS_ASSERT_EQUALS( i2.width(), 2);
		TS_ASSERT_EQUALS( i2.height(), 2);
		TS_ASSERT_EQUALS( i2.depth(), 2);
		TS_ASSERT_EQUALS( i2.nbChannel(), 2);
		TS_ASSERT_EQUALS(i2(0,0,0)[0], 0);
		TS_ASSERT_EQUALS(i2(0,1,1)[1], 13);
		TS_ASSERT_EQUALS(i2(1,1,0)[1], 7);

	}
	
	void testOperatorParenthesis3Parameters(void) {
		unsigned char static_buffer[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		unsigned char * dyn_buffer = new unsigned char[16];
		memcpy(dyn_buffer,static_buffer,16*sizeof(unsigned char));
		kn::Image3D<unsigned char> i(2,2,2,2,dyn_buffer);
	 	
		TS_ASSERT_THROWS_NOTHING(i(0,0,0));
		for(int j=0;j<16;j+=2) {
			TS_ASSERT_SAME_DATA( i((j%4)/2,(j/4)%2,j/8), static_buffer+j, 2);
		}
	}

	void testOperatorParenthesis4Parameters(void) {
		unsigned char static_buffer[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		unsigned char * dyn_buffer = new unsigned char[16];
		memcpy(dyn_buffer,static_buffer,16*sizeof(unsigned char));
		kn::Image3D<unsigned char> i(2,2,2,2,dyn_buffer);
	 	
		TS_ASSERT_THROWS_NOTHING(i(0,0,0,0));
		for(int j=0;j<16;j++) {
			TS_ASSERT_EQUALS( i((j%4)/2,(j/4)%2,j/8,j%2) , j);
		}
	}

	void testOperatorEqualsCopy(void) {
	        
		unsigned char buffer[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		kn::Image3D<unsigned char> i1(2,2,2,2,buffer);
		
		kn::Image3D<unsigned char> i2(2,2,2,2);
		i2 = i1;

		for(int j=0;j<16;j++) {
			TS_ASSERT_EQUALS( i1.begin()[j], i2.begin()[j]);
		}
	}

	void testImage3DBuilding(void) {
		float static_bufferf[] = {0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,10.0f,11.0f,12.0f,13.0f,14.0f,15.0f};
		float * dyn_bufferf = new float[16];
		memcpy(dyn_bufferf,static_bufferf,16*sizeof(float));
		kn::Image3D<float>	 iF(2,2,2,2,dyn_bufferf);
		kn::Image3D<float>	 iF2(2,4,3,1);
		kn::Image3D<float>	 iF3;

		TS_ASSERT_THROWS(iF2=iF, kn::ImageException);
		TS_ASSERT_THROWS_NOTHING(iF3=iF);
		TS_ASSERT_EQUALS(iF(0,0,1)[2], iF3(0,0,1)[2]);
		iF3(0,0,1,2) = 5.5;
		TS_ASSERT_DIFFERS(iF(0,0,1)[2], iF3(0,0,1)[2]);
	}

	// Test function for the two at functions
	void testAtFunctions() {
		unsigned char static_buffer[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		unsigned char * dyn_buffer = new unsigned char[16];
		memcpy(dyn_buffer,static_buffer,16*sizeof(char));
		kn::Image3D<unsigned char>	 i(2,2,2,2,dyn_buffer);

		TS_ASSERT_THROWS(i.at(1,10,1), kn::ImageException);
		TS_ASSERT_THROWS(i.at(10,1,1), kn::ImageException);
		TS_ASSERT_THROWS(i.at(10,10,1), kn::ImageException);
		TS_ASSERT_SAME_DATA( i.at(0,0,0), static_buffer, 2);
		TS_ASSERT_EQUALS(i.at(1,1,0,0),6);
		TS_ASSERT_THROWS(i.at(1,1,4,1), kn::ImageException);
	}

	void testFill() {
                const unsigned int  w = 5;
                const unsigned int  h = 5;
		const unsigned int  l = 5;
		const unsigned char value = 120;
		
	        kn::Image3D<unsigned char> Image3D(w,h,l,3);
		Image3D.fill(value);

		for(unsigned int i=0; i<w; i++)
		  for(unsigned int j=0; j<h; j++)
		  	for(unsigned int k=0; k<l; k++)
		  		 TS_ASSERT_EQUALS(Image3D.at(i,j,k,0), value);
	}

	void testGetFrame() {
                const unsigned int  w = 5;
                const unsigned int  h = 5;
		const unsigned int  l = 5;
		
	        kn::Image3D<unsigned char> Image3D(w,h,l,3);
		kn::ImageRGB<unsigned char> ImageRGB(w,h);
		
		
		int cpt = 0;
		for(unsigned int i=0; i<w; i++)
		  for(unsigned int j=0; j<h; j++)
		    for(unsigned int k=0; k<l; k++){
		  	Image3D(i,j,k,0) = Image3D(i,j,k,1) = Image3D(i,j,k,2) = (cpt++)%255;		 
		  }
		  
		  Image3D.getFrame(2,ImageRGB);
		  TS_ASSERT_SAME_DATA( Image3D.at(0,0,2), ImageRGB.at(0,0), 75);
		  TS_ASSERT_THROWS(Image3D.getFrame(5,ImageRGB), kn::ImageException);
		  kn::ImageRGB<unsigned char> ImageRGB2(w,4);
		  TS_ASSERT_THROWS(Image3D.getFrame(2,ImageRGB2), kn::ImageException);
		  kn::ImageRGB<unsigned char> ImageRGB3(2,h);
		  TS_ASSERT_THROWS(Image3D.getFrame(2,ImageRGB3), kn::ImageException);
		  kn::Image<unsigned char> Image4(w,h,2);
		  TS_ASSERT_THROWS(Image3D.getFrame(2,Image4), kn::ImageException);
	}
	
	void testSetFrame() {
                const unsigned int  w = 5;
                const unsigned int  h = 5;
		const unsigned int  l = 5;
		
	        kn::Image3D<unsigned char> Image3D(w,h,l,3);
		kn::ImageRGB<unsigned char> ImageRGB(w,h);
		
		
		int cpt = 0;
		for(unsigned int i=0; i<w; i++)
		  for(unsigned int j=0; j<h; j++)
		   	ImageRGB(i,j,0) = ImageRGB(i,j,1) = ImageRGB(i,j,2) = (cpt++)%255;		 
		  
		  
		  Image3D.setFrame(2,ImageRGB);
		  TS_ASSERT_SAME_DATA( Image3D.at(0,0,2), ImageRGB.at(0,0), 75);
		  TS_ASSERT_THROWS(Image3D.setFrame(5,ImageRGB), kn::ImageException);
		  kn::ImageRGB<unsigned char> ImageRGB2(w,4);
		  TS_ASSERT_THROWS(Image3D.setFrame(2,ImageRGB2), kn::ImageException);
		  kn::ImageRGB<unsigned char> ImageRGB3(2,h);
		  TS_ASSERT_THROWS(Image3D.setFrame(2,ImageRGB3), kn::ImageException);
		  kn::Image<unsigned char> Image4(w,h,2);
		  TS_ASSERT_THROWS(Image3D.setFrame(2,Image4), kn::ImageException);
	}
};


/*
 * End of Anti-doublon
 */
#endif
