/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * ioTGATest.hpp created in 09 2008.
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
#ifndef __OPENKN_IMAGE__IMAGELOADERTGATEST_HPP__
#define __OPENKN_IMAGE__IMAGELOADERTGATEST_HPP__

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
#include <OpenKN/image/ioTGA.hpp>
#include <OpenKN/image/Image.hpp>

/*
 * Class definition
 */
class ioTGATest : public CxxTest::TestSuite {
public:

	static unsigned char whitecol[3];
	static unsigned char refcolor[3];
	
	static int whiteValue(int ,int ) {return 255;}
	static int checkerboardValue(int i,int j) {return ((i+j)%2==0)?255:0;}

	static unsigned char* whiteRGBValue(int ,int ) {return whitecol;}

	// i indice de ligne
	// j indice de colonne
	static int diagValue(int i,int j) {
		switch (i) {
		case (0) :
			switch(j) {
			case (0) :
			case (1) : return 255;
			case (2) : return 215;
			case (3) : return 163;
			default : return -1;
			}
			break;
		case (1) :
			switch(j) {
			case (0) : return 255;
			case (1) : return 215;
			case (2) : return 72;
			case (3) : return 26;
			default : return -1;
			}
			break;
		case (2) :
			switch(j) {
			case (0) : return 215;
			case (1) : return 72;
			case (2) : return 4;
			case (3) : return 0;
			default : return -1;
			}
			break;
		case (3) :
			switch(j) {
			case (0) : return 163;
			case (1) : return 26;
			case (2) : 
			case (3) : return 0;
			default : return -1;
			}
			break;
		default : return -1;
		}
		return -1;
	}
	
	// i indice de ligne
	// j indice de colonne
	static unsigned char* colRGBValue(int i,int j) {
		if (j == i) {
			// rouge
			refcolor[0] = 255; refcolor[1] = refcolor[2] = 0;
		}
		if (j == ((i+1)%4) ) {
			// vert
			refcolor[1] = 255; refcolor[0] = refcolor[2] = 0;
		}
		if (j == ((i+2)%4) ) {
			// bleu
			refcolor[2] = 255; refcolor[1] = refcolor[0] = 0;
		}
		if (j == ((i+3)%4) ) {
			// blanc
			refcolor[2] = refcolor[1] = refcolor[0] = 255;
		}
		return refcolor;
	}
	
	void toolHandleGSImage(kn::Image<unsigned char> testimage,int (*fct)(int,int)) {
		TS_ASSERT(testimage.width() == 4);
		TS_ASSERT(testimage.height() == 4);
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				TS_ASSERT_EQUALS((int)(testimage(j,i,0)),(*fct)(i,j));
	}
	
	void toolHandleRVBImage(kn::Image<unsigned char> testimage,unsigned char* (*fct)(int,int)) {
		TS_ASSERT(testimage.width() == 4);
		TS_ASSERT(testimage.height() == 4);
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				TS_ASSERT_SAME_DATA(testimage(j,i),(*fct)(i,j),3);
	}
	
	void testLoadTGA(void) {
		// Some usefull variables
		int tga_type = -1;
		// Test for exception rising
		try {
			std::vector<kn::Image<unsigned char> >  testimages;
			testimages.resize(20);

			TS_ASSERT_THROWS(kn::loadTGA(testimages[0],"./ImageLoaderTGATestData/unknown.tga"),kn::ImageException);
			TS_ASSERT_THROWS(kn::loadTGA(testimages[0],"./ImageLoaderPPMTestData/testeur_wrong_header.tga"),kn::ImageException);
			// TO DO : test a lot of header wrong setting

			// ******************** Test for handling COLOR Image  *********************
			// *************************************************************************
			// WHITE IMAGE UNCOMPRESSED BOTTOM LEFT
			//std::cerr<<"**************** TEST testeur_white_nocompress_bottomleft "<<std::endl;
			tga_type = kn::loadTGA(testimages[1],
				"./ImageLoaderTGATestData/testeur_white_nocompress_bottomleft.tga");
			TS_ASSERT_EQUALS(tga_type,kn::COLOR_TGA);
			toolHandleRVBImage(testimages[1],whiteRGBValue);
			// WHITE IMAGE COMPRESSED BOTTOM LEFT
			//std::cerr<<"**************** TEST testeur_white_compress_bottomleft "<<std::endl;
			tga_type = kn::loadTGA(testimages[2],
				"./ImageLoaderTGATestData/testeur_white_compress_bottomleft.tga");
			TS_ASSERT_EQUALS(tga_type,kn::COLOR_RLE_TGA);
			toolHandleRVBImage(testimages[2],whiteRGBValue);
			// COLOR IMAGE UNCOMPRESSED BOTTOM LEFT
			//std::cerr<<"**************** TEST testeur_col_nocompress_bottomleft "<<std::endl;
			tga_type = kn::loadTGA(testimages[3],
				"./ImageLoaderTGATestData/testeur_col_nocompress_bottomleft.tga");
			TS_ASSERT_EQUALS(tga_type,kn::COLOR_TGA);
			toolHandleRVBImage(testimages[3],colRGBValue);
			// COLOR IMAGE UNCOMPRESSED TOP LEFT
			//std::cerr<<"**************** TEST testeur_col_nocompress_topleft2 "<<std::endl;
			tga_type = kn::loadTGA(testimages[4],
				"./ImageLoaderTGATestData/testeur_col_nocompress_topleft.tga");
			TS_ASSERT_EQUALS(tga_type,kn::COLOR_TGA);
			toolHandleRVBImage(testimages[4],colRGBValue);
		}
		catch (kn::ImageException &e) {
			//std::cerr<<"We got EXCEPTION"<<std::endl;
			TS_WARN("WE GOT EXCEPTION !");
			TS_WARN(e.errorString());
		}
	}
};

unsigned char ioTGATest::whitecol[3] = {255,255,255};
unsigned char ioTGATest::refcolor[3];

/*
 * End of Anti-doublon
 */
#endif
