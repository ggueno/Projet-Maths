/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * ioEPS.hpp created in 04 2010.
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
#ifndef __OPENKN_IMAGE__IO_EPS_HPP__
#define __OPENKN_IMAGE__IO_EPS_HPP__



/*
 * External Includes
 */
#include <string>



/*
 * Namespace
 */
namespace kn{

	  /*
	  * Class definition
	  */

	  /**
	  * \brief Some tools to create some simple primitives on an EPS file.
	  */
	  class ioEPS {
	    
	    
	    protected :
	     /**
	      * \brief width of the eps page
	      */
	      size_t width;
	      
	     /**
	      * \brief height of the eps page
	      */
	      size_t height;

	     /**
	      * \brief data containing the eps information
	      */
	      std::string  data;

	    public :
	     /**
	      * \brief constructor
	      * \param imageWidth : width of the eps page
	      * \param imageHeight : height of the eps page
	      */
	      ioEPS(const unsigned int imageWidth, const unsigned int imageHeight);
	      
	     /**
	      * \brief destructor
	      */	      
	      ~ioEPS();

	    protected :
	     /**
	      * \brief write a standard EPS file header
	      */
	      std::string writeHeaderEPS() const;

	    public : 
	     /**
	      * \brief save the eps file, you can still edit and save the eps file after this operation.
	      * \param fileName : file name (you should add ".eps")
	      */
	      void saveEPS(const std::string &fileName) const;

	     /**
	      * \brief draw a colored line from pt1 to pt2
	      * \param x1 : pt1 coordinates
	      * \param y1 : pt1 coordinates
	      * \param x2 : pt2 coordinates
	      * \param y2 : pt2 coordinates
	      * \param r : red component ranging from 0 to 1
	      * \param g : green component ranging from 0 to 1
	      * \param b : blue component ranging from 0 to 1
	      * \param lineWidth : width of the line
	      */
	      void drawLine(const unsigned int x1, const unsigned int y1,
			    const unsigned int x2, const unsigned int y2,
			    const float r, const float g, const float b,
			    const unsigned int lineWidth = 1);

	     /**
	      * \brief draw a colored circle
	      * \param x : center coordinates
	      * \param y : center coordinates
	      * \param radius : radius of the circle
	      * \param r : red component ranging from 0 to 1
	      * \param g : green component ranging from 0 to 1
	      * \param b : blue component ranging from 0 to 1
	      * \param lineWidth : width of the line
	      */			    
	      void drawCircle(const unsigned int x, const unsigned int y,
			      const unsigned int radius,
			      const float r, const float g, const float b,
			      const unsigned int lineWidth = 1);
      
	     /**
	      * \brief draw a colored filled circle
	      * \param x : center coordinates
	      * \param y : center coordinates
	      * \param radius : radius of the circle
	      * \param r : red component ranging from 0 to 1
	      * \param g : green component ranging from 0 to 1
	      * \param b : blue component ranging from 0 to 1
	      * \param lineWidth : width of the line
	      */
	      void drawCircleFilled(const unsigned int x, const unsigned int y,
				    const unsigned int radius,
				    const float r, const float g, const float b,
				    const unsigned int lineWidth = 1);
      
	     /**
	      * \brief draw a colored square
	      * \param x1 : upper left coordinates
	      * \param y1 : upper left coordinates
	      * \param x2 : lower right coordinates
	      * \param y2 : lower right coordinates
	      * \param r : red component ranging from 0 to 1
	      * \param g : green component ranging from 0 to 1
	      * \param b : blue component ranging from 0 to 1
	      * \param lineWidth : width of the line
	      */
	      void drawSquare(const unsigned int x1, const unsigned int y1,
			      const unsigned int x2, const unsigned int y2,
			      const float r, const float g, const float b,
			      const unsigned int lineWidth = 1);
      
	     /**
	      * \brief draw a filled colored square
	      * \param x1 : upper left coordinates
	      * \param y1 : upper left coordinates
	      * \param x2 : lower right coordinates
	      * \param y2 : lower right coordinates
	      * \param r : red component ranging from 0 to 1
	      * \param g : green component ranging from 0 to 1
	      * \param b : blue component ranging from 0 to 1
	      * \param lineWidth : width of the line
	      */
	      void drawSquareFilled(const unsigned int x1, const unsigned int y1,
				    const unsigned int x2, const unsigned int y2,
				    const float r, const float g, const float b,
				    const unsigned int lineWidth = 1);


	  };


       /*
        * End of Namespace
	*/
	}

/*
 * End of Anti-doublon
 */
#endif
