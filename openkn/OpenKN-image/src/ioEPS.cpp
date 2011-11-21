/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * ioEPS.cpp created in 04 2010
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
 * External Includes
 */
#include <string>
#include <fstream>
#include <sstream> 

/*
 * Internal Includes
 */
#include <ioEPS.hpp>

/*
 * Namespace
 */
namespace kn{
    /*
     * End of Namespace
     */

      ioEPS::ioEPS(const unsigned int imageWidth, const unsigned int imageHeight)
	: width(imageWidth), height(imageHeight)
      {
      }


      ioEPS::~ioEPS()
      {
      }


      void ioEPS::saveEPS(const std::string &fileName) const
      {
	// open the file
	std::ofstream epsfile(fileName.c_str());

	// header
	epsfile << writeHeaderEPS() << std::endl;

	// data
	epsfile << data << std::endl;

	// end of file
	epsfile << "%% EOF" << std::endl;

	// close file
	epsfile.close();
      }


      std::string  ioEPS::writeHeaderEPS() const
      {
	std::ostringstream oss;

	oss << "%%!PS-Adobe-3.0 EPSF-3.0\n"
	    << "%%Creator: OpenKraken-image\n"
	    << "%%Title: OpenKraken\n"
	    << "%%DocumentData: Clean7Bit\n"
	    << "%%Origin: 0 0\n"
	    << "%%BoundingBox: -1 -1 " << width+1 << " " << height+1 << "\n"
	    << "%%LanguageLevel: 2\n"
	    << "%%Page: 1 1\n\n";

	return oss.str(); 
      }


      void ioEPS::drawLine(const unsigned int x1, const unsigned int y1,
			   const unsigned int x2, const unsigned int y2,
			   const float r, const float g, const float b,
			   const unsigned int lineWidth)
      {
	std::ostringstream oss;

	oss << "newpath\n"
	    << x1 << " " << height-y1 << " moveto\n"
	    << x2 << " " << height-y2 << " lineto\n"
	    << lineWidth << " setlinewidth\n"
	    << r << " " << g << " " << b << " setrgbcolor" << std::endl
	    << "stroke" << std::endl;

	data += oss.str(); 
      }


      void ioEPS::drawSquare(const unsigned int x1, const unsigned int y1,
			     const unsigned int x2, const unsigned int y2,
			     const float r, const float g, const float b,
			     const unsigned int lineWidth)
      {
	std::ostringstream oss;

	oss << "newpath\n"
	    << x1 << " " << height-y1 << " moveto\n"
	    << x2 << " " << height-y1 << " lineto\n"
	    << x2 << " " << height-y2 << " lineto\n"
	    << x1 << " " << height-y2 << " lineto\n"
	    << x1 << " " << height-y1 << " lineto\n"
	    << lineWidth << " setlinewidth\n"
	    << r << " " << g << " " << b << " setrgbcolor" << std::endl
	    << "stroke" << std::endl;

	data += oss.str(); 
      }

      void ioEPS::drawSquareFilled(const unsigned int x1, const unsigned int y1,
				   const unsigned int x2, const unsigned int y2,
				   const float r, const float g, const float b,
				   const unsigned int lineWidth)
      {
	std::ostringstream oss;

	oss << "newpath\n"
	    << r << " " << g << " " << b << " setrgbcolor" << std::endl
	    << x1 << " " << height-y1 << " moveto\n"
	    << x2 << " " << height-y1 << " lineto\n"
	    << x2 << " " << height-y2 << " lineto\n"
	    << x1 << " " << height-y2 << " lineto\n"
	    << x1 << " " << height-y1 << " lineto\n"
	    << "closepath\ngsave\nfill\n"
	    << lineWidth << " setlinewidth\n"
	    << "stroke" << std::endl;

	data += oss.str(); 
      }


      void ioEPS::drawCircle(const unsigned int x, const unsigned int y,
			     const unsigned int radius,
			     const float r, const float g, const float b,
			     const unsigned int lineWidth)
      {
	std::ostringstream oss;

	oss << "newpath\n"
	    << r << " " << g << " " << b << " setrgbcolor" << std::endl
	    << x << " " << height-y << " " << radius << " 0 360 arc" << std::endl
	    << "closepath\n" 
	    << lineWidth << " setlinewidth\n"
	    << "stroke" << std::endl;

	data += oss.str(); 
      }


      void ioEPS::drawCircleFilled(const unsigned int x, const unsigned int y,
				   const unsigned int radius,
				   const float r, const float g, const float b,
				   const unsigned int lineWidth)
      {
	std::ostringstream oss;

	oss << "newpath\n"
	    << r << " " << g << " " << b << " setrgbcolor" << std::endl
	    << x << " " << height-y << " " << radius << " 0 360 arc" << std::endl
	    << "closepath\ngsave\nfill\n"
	    << lineWidth << " setlinewidth\n"
	    << "stroke" << std::endl;

	data += oss.str(); 
      }



    /*
     * End of Namespace
     */
}
