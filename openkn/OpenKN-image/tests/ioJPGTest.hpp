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
#ifndef __OPENKN_IMAGE__IMAGELOADERJPGTEST_HPP__
#define __OPENKN_IMAGE__IMAGELOADERJPGTEST_HPP__

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
#include <OpenKN/image/ioJPG.hpp>


/*
 * Class definition
 */
class ioJPGTest : public CxxTest::TestSuite {
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
			refcolor[0] = 254; refcolor[1] = 0; refcolor[2] = 0;
		}
		if (j == ((i+1)%4) ) {
			// vert
			refcolor[1] = 255; refcolor[0] = 0; refcolor[2] = 1;
		}
		if (j == ((i+2)%4) ) {
			// bleu
			if (i<2) {
				refcolor[2] = 254; refcolor[1] = refcolor[0] = 0;
			}
			else if (i==2) {
				refcolor[2] = 255; refcolor[1] = refcolor[0] = 1;
			}
			else {
				refcolor[2] = 254; refcolor[1] = 0; refcolor[0] = 1;
			}
		}
		if (j == ((i+3)%4) ) {
			// blanc
			refcolor[2] = refcolor[1] = refcolor[0] = 255;
		}
		//std::cerr<<"For i="<<i<<" et j="<<j<<" we send "<<(int)refcolor[0]<<"/"<<(int)refcolor[1]<<"/"<<(int)refcolor[2]<<std::endl;
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

	void testLoadJPG( void ) {

			// Some usefull variables
			int jpg_type = -1;
			// Test for exception rising
			try {
				std::vector<kn::Image<unsigned char> >  testimages;
				testimages.resize(20);

				//std::cerr<<"********* TEST unknown file"<<std::endl;
				TS_ASSERT_THROWS(kn::loadJPG(testimages[0],"./ImageLoaderJPGTestData/unknown.jpg"),
						kn::ImageException);

				// ******************** Test for handling COLOR Image  *********************
				// *************************************************************************
				// WHITE IMAGE UNCOMPRESSED
// 				std::cerr<<"********* TEST testeur_white_nocompress"<<std::endl;
				jpg_type = kn::loadJPG(testimages[1],
					"./ImageLoaderJPGTestData/testeur_white_uncompressed.jpg");
// 				std::cerr<<"********* Reached"<<std::endl;
				TS_ASSERT_EQUALS(jpg_type,kn::RGB_JPG);
				toolHandleRVBImage(testimages[1],whiteRGBValue);
				// Checking double image
				TS_ASSERT_THROWS(kn::loadJPG(testimages[1],
						"./ImageLoaderJPGTestData/testeur_white_uncompressed.jpg"),
					kn::ImageException);
				// COLOR IMAGE UNCOMPRESSED
				//std::cerr<<"********* TEST testeur_col_uncompressed"<<std::endl;
				jpg_type = kn::loadJPG(testimages[2],
					"./ImageLoaderJPGTestData/testeur_col_uncompressed.jpg");
				TS_ASSERT_EQUALS(jpg_type,kn::RGB_JPG);
				toolHandleRVBImage(testimages[2],colRGBValue);

			}
			catch (kn::ImageException &e) {
				//std::cerr<<"We got EXCEPTION"<<std::endl;
				TS_WARN("WE GOT EXCEPTION !");
				TS_WARN(e.errorString());
			}
		}

		void testSaveJPG() {
			//li::image::ImageRGB8u * = new li::image::ImageRGB8u[2];
			std::vector<kn::ImageRGB8u> imagesource;
			imagesource.clear();
			imagesource.resize(4);
			int jpg_type;
			try {
				// TEST 1 : Lire le fichier et vérifier qu'il doit correspondre
				//std::cerr<<"Loading ... testeur_col_uncompressed"<<std::endl;
				jpg_type = kn::loadJPG(imagesource[0],"./ImageLoaderJPGTestData/testeur_col_uncompressed.jpg");
				TS_ASSERT_EQUALS(jpg_type,kn::RGB_JPG);
				toolHandleRVBImage(imagesource[0],colRGBValue);
				// TEST 1 : Sauver l'image puis la relire
				//std::cerr<<"Saving ... testeur_col_uncompressed"<<std::endl;
				bool reussite = kn::saveJPG(imagesource[0],"./ImageExporterJPGTestData/out.jpg",100);
				TS_ASSERT_EQUALS(reussite,true);
				jpg_type = -1;
				jpg_type = kn::loadJPG(imagesource[1],"./ImageExporterJPGTestData/out.jpg");
				TS_ASSERT_EQUALS(jpg_type,kn::RGB_JPG);
				/*
				toolHandleRVBImage(imagesource[1],colRGBValue);
				*/

				// Test avec fichier standard ...
				TS_TRACE("Make a test of loading standard jpg...");
				/*
				std::cerr<<"Loading ... standard_file"<<std::endl;
				jpg_type = kn::loadJPG(imagesource[2],"./ImageExporterJPGTestData/test.jpg");
				TS_ASSERT_EQUALS(jpg_type,kn::RGB_JPG);
				refcolor[0] = 51; refcolor[1] = 46; refcolor[2] = 43;
				TS_ASSERT_SAME_DATA(imagesource[0](100,100),refcolor,3);
				// TEST 1 : Sauver l'image puis la relire
				std::cerr<<"Saving ... testeur_col_uncompressed"<<std::endl;
				reussite = kn::saveJPG(imagesource[2],"./ImageExporterJPGTestData/test_out.jpg",100);
				TS_ASSERT_EQUALS(reussite,true);
				jpg_type = -1;
				jpg_type = kn::loadJPG(imagesource[3],"./ImageExporterJPGTestData/test_out.jpg");
				TS_ASSERT_EQUALS(jpg_type,kn::RGB_JPG);
				TS_ASSERT_SAME_DATA(imagesource[0](100,100),refcolor,3);
				// Code 100,100 : 33 2E 2B
				*/

			}
			catch (kn::ImageException &e) {
				TS_WARN("WE GOT EXCEPTION !");
				TS_WARN(e.errorString());
			}
		}


};

unsigned char ioJPGTest::whitecol[3] = {255,255,255};
unsigned char ioJPGTest::refcolor[3];

/*
 * End of Anti-doublon
 */
#endif
