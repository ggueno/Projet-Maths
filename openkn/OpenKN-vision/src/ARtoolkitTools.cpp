/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * ARtoolkitTools.cpp created in 02 2010.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-vision.
 *
 * The OpenKraken-vision is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-vision is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/



/*
 * External Includes
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>



/*
 * Internal Includes
 */
#include "ARtoolkitTools.hpp"
#include "VisionException.hpp"
#include <OpenKN/image/ImageGS.hpp>


/*
 * Namespace
 */
namespace kn{


	/*
	 * \brief Create an ARtoolkit marker pattern file and the printable image from an input pattern image.
	 * \param inputImage : the inut image (should be square and have at least a 32x32 resolution
	 * \param fileName : name of the pattern files to be created
	 * \param is16 : true if you want to use a 16x16 pixel pattern, false for 32x32
	 * \return the printable pattern image (with the black borders)
	 * \throw VisionException inputImage : invalid size
         * \author Vincent
	 */
	ImageRGB8u arToolkitMarkerMaker(const ImageRGB8u &inputImage,
					const std::string &fileName,
					bool is16){
	// check input data
	if(inputImage.width()<32 || inputImage.height()<32)
	      throw VisionException("the minimum resolution for the input image is 32x32" ,"arToolkitMarkerMaker");

	if(inputImage.width() != inputImage.height())
	      throw VisionException("the input image should be square" ,"arToolkitMarkerMaker");

	// pattern size
	unsigned int patternSize = is16 == true ? 16 : 32;

	// pattern grey scale image
	ImageGS8u pattern(inputImage.width(),inputImage.height());
	for(unsigned int i=0; i<inputImage.width();++i)
		for(unsigned int j=0; j<inputImage.height();++j)
			pattern(i,j) = (inputImage(i,j)[0] + inputImage(i,j)[1] + inputImage(i,j)[2]) / 3; 

	// resize the pattern
	ImageGS8u smallPattern(patternSize,patternSize);
	unsigned int tmpWidth  = pattern.width()/patternSize;
	unsigned int tmpHeight = pattern.height()/patternSize;

	for(unsigned int i=0; i<patternSize; ++i)
		for(unsigned int j=0; j<patternSize; j++){
			ImageGS8u square(tmpWidth, tmpHeight);
			pattern.getSubImage(i*tmpHeight, j*tmpWidth, square);

			int greyLevel = 0;
			unsigned char *ptr = square.begin();
			while(ptr != square.end()){
				greyLevel += (int)*ptr;
				++ptr;
			}

			smallPattern(i,j) = (unsigned char) (greyLevel/(tmpWidth*tmpHeight));
	}

	// create and save the pattern file
	// open the output file
	std::ofstream patternfile(fileName.c_str());

	// write the pattern
	for(unsigned int dir=0; dir<4; ++dir){ // 4 directions
         for(int k=0; k<3; ++k) // 3 time the same marker
            for(unsigned int j=0; j<patternSize; j++){ // row by row
               for(unsigned int i=0; i<patternSize; ++i){ // col by col
			double scale = 0.9;
			//double scale = 0.95*(k-2)/(-2.0) + 0.7*k/2.0; // Lagrange polynomial for the 3 brightness candidates
			std::ostringstream oss;
			oss << std::setfill('0') << std::setw(3) <<  (int) (scale * smallPattern(i,j)); 
			patternfile << oss.str() << " ";
		  }
	    patternfile << std::endl;
	    }
	 patternfile << std::endl;

	 // rotate the pattern (ok because the pattern is square)
	 smallPattern.rotate();
	}

	// close the output file
	patternfile.close();


	// create the printable pattern image
	ImageRGB8u printableImage(inputImage.width()*2, inputImage.height()*2);
	printableImage.fill(0);

	unsigned int iOffset = inputImage.height()/2;
	unsigned int jOffset = inputImage.width()/2;

	// image copy
	for(unsigned int i=0; i<pattern.height(); i++)
		for(unsigned int j=0; j<pattern.width(); j++)
			for(unsigned int c=0; c<3; c++)
				printableImage(i+iOffset,j+jOffset)[c] = inputImage(i,j)[c];

	return printableImage;
	}


	/*
	* End of Namespace
	*/
}

