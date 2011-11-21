/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * ioPPMTest.hpp created in 09 2008.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-image.
 *
 * The libIMAC-loader is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The libIMAC-loader is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_IMAGE__LOADERPPMTEST_HPP__
#define __OPENKN_IMAGE__LOADERPPMTEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <vector>
#include <cxxtest/TestSuite.h>
#include <OpenKN/image/Image.hpp>

/*
 * Internal Includes
 */
#include <OpenKN/image/ioPPM.hpp>

/*
 * Class definition
 */
class ioPPMTest : public CxxTest::TestSuite {
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

	static unsigned char* diagRVBValue(int i,int j) {
		int res = diagValue(i,j);
		refcolor[0] = refcolor[1] = refcolor[2] = (unsigned char)res;
		return refcolor;
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
		//std::cerr<<"For i="<<i<<" et j="<<j<<" we send "<<(int)refcolor[0]<<"/"<<(int)refcolor[1]<<"/"<<(int)refcolor[2]<<std::endl;
		return refcolor;
	}

	static int colGSValue(int i,int j) {
		unsigned char* col;
		col = colRGBValue(i,j);
		return ((int)col[0]+(int)col[1]+(int)col[2])/3;
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
	
	void testLoadPPM( void ) {
			// Some usefull variables
			int depth_res = -1;
			// Test for exception rising
			try {
				std::vector<kn::Image<unsigned char> >  testimages;
				testimages.resize(20);
				TS_ASSERT_THROWS(kn::loadPPM(testimages[0],
					"./ImageLoaderPPMTestData/unknown.ppm"),kn::ImageException);
				TS_ASSERT_THROWS(kn::loadPPM(testimages[0],
					"./ImageLoaderPPMTestData/wrong_header.ppm"),kn::ImageException);

				// Test for handling a bunch of comment in header
				kn::loadPPM(testimages[1],"./ImageLoaderPPMTestData/testeur_bunch_of_comment.ppm");
				TS_ASSERT_THROWS(kn::loadPPM(testimages[1],"./ImageLoaderPPMTestData/testeur_bunch_of_comment.ppm"),kn::ImageException);
			
				// ************ Test for handling PBM  *******************
				// *******************************************************
				// WHITE ASCII
				depth_res = kn::loadPPM(testimages[2],
											"./ImageLoaderPPMTestData/testeur_white_ascii.pbm");
				toolHandleGSImage(testimages[2],whiteValue);
				TS_ASSERT_EQUALS(depth_res,1);
				// CHECKERBOARD ASCII
				kn::loadPPM(testimages[3],"./ImageLoaderPPMTestData/testeur_checkerboard_ascii.pbm");
				toolHandleGSImage(testimages[3],checkerboardValue);
				// WHITE BINARY
				kn::loadPPM(testimages[4],"./ImageLoaderPPMTestData/testeur_white_binary.pbm");
				toolHandleGSImage(testimages[4],whiteValue);
				// CHECKBOARD BINARY
				kn::loadPPM(testimages[5],
					"./ImageLoaderPPMTestData/testeur_checkerboard_binary.pbm");
				toolHandleGSImage(testimages[5],checkerboardValue);
				TS_TRACE("Still tests with rectangular image TO DO");
				TS_TRACE("Tests for P4 with width multiple of 8");
			
				// ************ Test for handling PGM  *******************
				// *******************************************************
				// DIAG ASCII
				depth_res = -1;
				depth_res = kn::loadPPM(testimages[6],"./ImageLoaderPPMTestData/testeur_diag_ascii.pgm");
				toolHandleGSImage(testimages[6],diagValue);
				TS_ASSERT_EQUALS(depth_res,1);
				// WHIRE BINARY
				kn::loadPPM(testimages[7],"./ImageLoaderPPMTestData/testeur_white_binary.pgm");
				toolHandleGSImage(testimages[7],whiteValue);
				// DIAG BINARY
				kn::loadPPM(testimages[8],"./ImageLoaderPPMTestData/testeur_diag_binary.pgm");
				toolHandleGSImage(testimages[8],diagValue);
				
				// ************ Test for handling PPM  *******************
				// *******************************************************
				// WHITE BINARY
				depth_res = -1;
				depth_res = kn::loadPPM(testimages[9],
					"./ImageLoaderPPMTestData/testeur_white_binary.ppm");
				toolHandleRVBImage(testimages[9],whiteRGBValue);
				TS_ASSERT_EQUALS(depth_res,3);
				// COL ASCII
				kn::loadPPM(testimages[10],
					"./ImageLoaderPPMTestData/testeur_col_ascii.ppm");
				toolHandleRVBImage(testimages[10],colRGBValue);
				// COL BINAIRE
				kn::loadPPM(testimages[11],
					"./ImageLoaderPPMTestData/testeur_col_binary.ppm");
				toolHandleRVBImage(testimages[11],colRGBValue);
			
				// ************ Test for conversion    *******************
				// *******************************************************
				kn::ImageRGB8u image_col_test;
				kn::ImageGS8u image_gs_test;
				
				depth_res = -1;
				depth_res = kn::loadPPM(image_col_test,"./ImageLoaderPPMTestData/testeur_diag_binary.pgm");
				TS_ASSERT_EQUALS(depth_res,1);
				toolHandleRVBImage(image_col_test,diagRVBValue);

				kn::loadPPM(image_gs_test,"./ImageLoaderPPMTestData/testeur_col_binary.ppm");
				//std::cerr<<"Depth "<<image_gs_test.depth()<<std::endl;
				toolHandleGSImage(image_gs_test,colGSValue);
				
			}
			catch (kn::ImageException &e) {
				TS_WARN("WE GOT EXCEPTION !");
				std::cerr<<e.errorString()<<std::endl;
				TS_WARN(e.errorString());
			}
		}

		void testSavePPM() {
			//li::image::ImageRGB8u * = new li::image::ImageRGB8u[2];
			std::vector<kn::ImageRGB8u> imagesource;
			imagesource.resize(2);
			int depth;
			try {
				//std::cerr<<"Here 1"<<std::endl;
				depth = kn::loadPPM(imagesource[0],"./ImageExporterPPMTestData/testeur_col_binary.ppm");
				TS_ASSERT_EQUALS(depth,3);
				toolHandleRVBImage(imagesource[0],colRGBValue);
				// PREMIER TEST : Fichier existe (= impossible d'écrire)
				//std::cerr<<"Here"<<std::endl;
				bool reussite = kn::savePPM(imagesource[0],"./ImageExporterPPMTestData/out.ppm");
				TS_ASSERT_EQUALS(reussite,true);
				depth = -1;
				depth = kn::loadPPM(imagesource[1],"./ImageExporterPPMTestData/out.ppm");
				TS_ASSERT_EQUALS(depth,3);
				toolHandleRVBImage(imagesource[1],colRGBValue);
			}
			catch (kn::ImageException &e) {
				TS_WARN("WE GOT EXCEPTION !");
				TS_WARN(e.errorString());
			}
		}
};

unsigned char ioPPMTest::whitecol[3] = {255,255,255};
unsigned char ioPPMTest::refcolor[3];

/*
 * End of Anti-doublon
 */
#endif
