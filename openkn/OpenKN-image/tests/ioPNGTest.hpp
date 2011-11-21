/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * ioJPGTest.hpp created in 01 2009.
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
#ifndef __OPENKN_IMAGE__IOPNGTEST_HPP__
#define __OPENKN_IMAGE__IOPNGTEST_HPP__

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
#include <OpenKN/image/ioPNG.hpp>


/*
 * Class definition
 */
class ioPNGTest : public CxxTest::TestSuite {
public:

	static unsigned char whitecol[3];
	static unsigned char refcolor[3];
	static unsigned char refcoloralpha[4];

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
			refcolor[0] = 255; refcolor[1] = 0; refcolor[2] = 0;
		}
		if (j == ((i+1)%4) ) {
			// vert
			refcolor[1] = 255; refcolor[0] = 0; refcolor[2] = 0;
		}
		if (j == ((i+2)%4) ) {
			// bleu
			if (i<2) {
				refcolor[2] = 255; refcolor[1] = refcolor[0] = 0;
			}
			else if (i==2) {
				refcolor[2] = 255; refcolor[1] = refcolor[0] = 0;
			}
			else {
				refcolor[2] = 255; refcolor[1] = 0; refcolor[0] = 0;
			}
		}
		if (j == ((i+3)%4) ) {
			// blanc
			refcolor[2] = refcolor[1] = refcolor[0] = 255;
		}
		//std::cerr<<"For i="<<i<<" et j="<<j<<" we send "<<(int)refcolor[0]<<"/"<<(int)refcolor[1]<<"/"<<(int)refcolor[2]<<std::endl;
		return refcolor;
	}

	// i indice de ligne
	// j indice de colonne
	static unsigned char* redBlockValue(int i,int j) {
		if (i>=1 && i<=2 && j>=1 && j<=2) {
			refcoloralpha[0] = 255; refcoloralpha[1] = refcoloralpha[2] = 0;
			// Opaque
			refcoloralpha[3] = 255;
		}
		else {
			refcoloralpha[0] = 255; refcoloralpha[1] = refcoloralpha[2] = 0;
			// Opaque
			refcoloralpha[3] = 0;
		}
		return refcoloralpha;
	}

	void toolHandleGSImage(kn::Image<unsigned char> testimage,int (*fct)(int,int)) {
		TS_ASSERT(testimage.width() == 4);
		TS_ASSERT(testimage.height() == 4);
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				TS_ASSERT_EQUALS((int)(testimage(j,i,0)),(*fct)(i,j));
	}
	
	void toolHandleRGBImage(kn::Image<unsigned char> testimage,unsigned char* (*fct)(int,int)) {
		TS_ASSERT(testimage.width() == 4);
		TS_ASSERT(testimage.height() == 4);
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				TS_ASSERT_SAME_DATA(testimage(j,i),(*fct)(i,j),3);
	}

	void toolHandleRGBAImage(kn::Image<unsigned char> testimage,unsigned char* (*fct)(int,int)) {
		TS_ASSERT(testimage.width() == 4);
		TS_ASSERT(testimage.height() == 4);
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				TS_ASSERT_SAME_DATA(testimage(j,i),(*fct)(i,j),4);
	}
	
	void testLoadPNG( void ) {
			// Some usefull variables
			int png_type = -1;
			// Test for exception rising
			try {
				std::vector<kn::Image<unsigned char> >  testimages;
				testimages.resize(20);

				// CHECK DEFENSIVE PROGRAMMATION
// 				std::cerr<<"********* TEST unknown file"<<std::endl;
				TS_ASSERT_THROWS(kn::loadPNG(testimages[0],
						"./ImageLoaderJPGTestData/unknown.png"),
						kn::ImageException);

				// WHITE IMAGE
// 				std::cerr<<"********* TEST testeur_white_greyscale"<<std::endl;
				png_type = kn::loadPNG(testimages[1],"./ImageLoaderPNGTestData/testeur_white_greyscale.png");
				TS_ASSERT_EQUALS(png_type,kn::GRAYSCALE_PNG);
				toolHandleGSImage(testimages[1],whiteValue);

// 				std::cerr<<"********* TEST testeur_white_color"<<std::endl;
				png_type = kn::loadPNG(testimages[2],"./ImageLoaderPNGTestData/testeur_white_color.png");
				TS_ASSERT_EQUALS(png_type,kn::COLOR_RGB_PNG);
				toolHandleRGBImage(testimages[2],whiteRGBValue);

				// CHECKERBOARD IMAGE
				png_type = kn::loadPNG(testimages[3],"./ImageLoaderPNGTestData/testeur_checkerboard.png");
				TS_ASSERT_EQUALS(png_type,kn::GRAYSCALE_PNG);
				toolHandleGSImage(testimages[3],checkerboardValue);

				// DIAG IMAGE COMPRESSED / UNCOMPRESSED
// 				std::cerr<<"********* TEST testeur_diag_uncompressed"<<std::endl;
				png_type = kn::loadPNG(testimages[4],"./ImageLoaderPNGTestData/testeur_diag_uncompressed.png");
				TS_ASSERT_EQUALS(png_type,kn::GRAYSCALE_PNG);
				toolHandleGSImage(testimages[4],diagValue);

// 				std::cerr<<"********* TEST testeur_diag compressed"<<std::endl;
				png_type = kn::loadPNG(testimages[5],"./ImageLoaderPNGTestData/testeur_diag.png");
				TS_ASSERT_EQUALS(png_type,kn::GRAYSCALE_PNG);
				toolHandleGSImage(testimages[5],diagValue);

				// COLOR IMAGE COMPRESSED / UNCOMPRESSED
// 				std::cerr<<"********* TEST testeur_col_uncompressed"<<std::endl;
				png_type = kn::loadPNG(testimages[6],"./ImageLoaderPNGTestData/testeur_col_uncompressed.png");
				TS_ASSERT_EQUALS(png_type,kn::COLOR_RGB_PNG);
				toolHandleRGBImage(testimages[6],colRGBValue);

// 				std::cerr<<"********* TEST testeur_col compressed"<<std::endl;
				png_type = kn::loadPNG(testimages[7],"./ImageLoaderPNGTestData/testeur_col.png");
				TS_ASSERT_EQUALS(png_type,kn::COLOR_RGB_PNG);
				toolHandleRGBImage(testimages[7],colRGBValue);

				// ALPHA IMAGES
// 				std::cerr<<"********* TEST testeur_col compressed"<<std::endl;
				png_type = kn::loadPNG(testimages[8],"./ImageLoaderPNGTestData/testeur_red_block_with_alpha.png");
				TS_ASSERT_EQUALS(png_type,kn::COLOR_RGBA_PNG);
				toolHandleRGBAImage(testimages[8],redBlockValue);

			}
			catch (kn::ImageException &e) {
				//std::cerr<<"We got EXCEPTION"<<std::endl;
				TS_WARN("WE GOT EXCEPTION !");
				TS_WARN(e.errorString());
			}
		}
};

unsigned char ioPNGTest::whitecol[3] = {255,255,255};
unsigned char ioPNGTest::refcolor[3];
unsigned char ioPNGTest::refcoloralpha[4];

/*
 * End of Anti-doublon
 */
#endif
