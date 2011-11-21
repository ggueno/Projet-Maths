/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * DrawLine.hpp created in 10 2009.
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
#ifndef __OPENKN_IMAGE__DRAW_LINE_HPP__
#define __OPENKN_IMAGE__DRAW_LINE_HPP__


/*
 * Internal Includes
 */
#include "Image.hpp"
#include "ImageRGB.hpp"
#include "ImageGS.hpp"
#include "ImageException.hpp"


/*
 * Namespace
 */
namespace kn{
	

		/** \brief draw a segment line on "imageRGB" from (x1,y1) to (x2,y2) with the color (r,g,b).
		 * \param image : input image where we will draw the line
		 * \param x1 : starting point width index
		 * \param y1 : starting point height index
		 * \param x2 : end point heigth index
		 * \param y2 : end point width index
		 * \param r : color of the line : red component
		 * \param g : color of the line : green component
		 * \param b : color of the line : blue component
		 * \author Vincent
		 */
		void drawLine(ImageRGB8u &image,
        	              const int x1, const int y1,
                	      const int x2, const int y2,
                	      const unsigned char r,
                	      const unsigned char g,
                	      const unsigned char b);


		/** \brief draw a segment line on "imageGS" from (x1,y1) to (x2,y2) with the color "greyLevel".
		 * \param image : input image where we will draw the line
		 * \param x1 : starting point width index
		 * \param y1 : starting point height index
		 * \param x2 : end point heigth index
		 * \param y2 : end point width index
		 * \param greyLevel : color of the line : grey scale
		 * \author Vincent
		 */
		void drawLine(ImageGS8u &image,
        		      const int x1, const int y1,
                	      const int x2, const int y2,
                	      const unsigned char greyLevel);


		/** \brief draw a line on "imageRGB" with the color (r,g,b).
		 * \param image : input image where we will draw the line
		 * \param line : line = (a,b,c) where u = (x,y,w) belongs to the line if line.u=0
		 * \param r : color of the line : red component
		 * \param g : color of the line : green component
		 * \param b : color of the line : blue component
		 * \author Vincent
		 */
		void drawLine(ImageRGB8u &image,
			      const double line[3],
                	      const unsigned char r,
                	      const unsigned char g,
                	      const unsigned char b);


		/** \brief draw a line on "imageGS" with the color "greyLevel".
		 * \param image : input image where we will draw the line
		 * \param line : line = (a,b,c) where u = (x,y,w) belongs to the line if line.u=0
		 * \param greyLevel : color of the line : grey scale
		 * \author Vincent
		 */
		void drawLine(ImageGS8u &image,
			      const double line[3],
                	      const unsigned char greyLevel);

		/**
		 * \cond
		 * \brief draw a line by steps of on the x axis
		 */
		void drawLineX(ImageRGB8u &image,
			       const int x1, const int y1,
			       const int x2, const int y2,
			       const unsigned char r,
			       const unsigned char g,
			       const unsigned char b);
		/// \endcond


		/**
		 * \cond
		 * \brief draw a line by steps of on the x axis
		 */
		void drawLineX(ImageGS8u &image,
			       const int x1, const int y1,
			       const int x2, const int y2,
			       const unsigned char greyLevel);
		/// \endcond


		/**
		 * \cond
		 * \brief draw a line by steps of on the y axis
		 */
		void drawLineY(ImageRGB8u &image,
			       const int i1, const int j1,
			       const int i2, const int j2,
			       const unsigned char r,
			       const unsigned char g,
			       const unsigned char b);
		/// \endcond


		/**
		 * \cond
		 * \brief draw a line by steps of on the y axis
		 */
		void drawLineY(ImageGS8u &image,
			       const int x1, const int y1,
			       const int x2, const int y2,
			       const unsigned char greyLevel);
		/// \endcond


		/**
		 * \cond
		 * \brief draw an anti-aliased point
		 */
		void drawPixel(ImageRGB8u &image,
			       int x0, int y0,
			       const unsigned char r,
			       const unsigned char g,
			       const unsigned char b);
		/// \endcond


		/**
		 * \cond
		 * \brief draw an anti-aliased point
		 */
		void drawPixel(ImageGS8u &image,
			       int x0, int y0,
			       const unsigned char greyLevel);
		/// \endcond


		/**
		 * \cond
		 * \brief draw an anti-aliased point
		 */
		inline int int2FloatingInt(int nb){return (nb<<16) & 0xFFFF0000;}
		/// \endcond





		/*
		 * End of Namespace
		 */
	}

/*
 * End of Anti-doublon
 */
#endif
