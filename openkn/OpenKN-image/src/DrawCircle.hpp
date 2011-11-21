/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * DrawCircle.hpp created in 02 2010.
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
#ifndef __OPENKN_IMAGE__DRAW_CIRCLE_HPP__
#define __OPENKN_IMAGE__DRAW_CIRCLE_HPP__


/*
 * Internal Includes
 */
#include "ImageRGB.hpp"
#include "ImageGS.hpp"


/*
 * Namespace
 */
namespace kn{
	
		/**
		 * \brief draw a circle on an imageRGB8u.
		 * \param image : input image where we will draw the cirlce
		 * \param xCenter : center of the circle (width)
		 * \param yCenter : center of the circle (height)
		 * \param radius : radius of the circle
		 * \param r : color of the circle : red component
		 * \param g : color of the circle : green component
		 * \param b : color of the circle : blue component
		 * \author Vincent
		 */
		void drawCircle(kn::ImageRGB8u &image,
        			const int xCenter,
				const int yCenter,
				const double radius,
				const unsigned char r,
				const unsigned char g,
				const unsigned char b);


		/** \brief draw a circle on an imageGS8u
		 * \param image : input image where we will draw the cirlce
		 * \param xCenter : center of the circle (width)
		 * \param yCenter : center of the circle (height)
		 * \param radius : radius of the circle
		 * \param greyLevel : color of the line : grey scale
		 * \author Vincent
		 */
		void drawCircle(ImageGS8u &image,
        			const int xCenter,
				const int yCenter,
				const double radius,
				const unsigned char greyLevel);


		/**
		 * \cond
		 * \brief draws 8 points liying on the circle
		 */
		void circlesPlotPoints(ImageRGB8u &image,
				       const int &xCenter,
				       const int &yCenter,
				       const int i, const int j,
				       const unsigned char r,
				       const unsigned char g,
				       const unsigned char b);
		/// \endcond


		/**
		 * \cond
		 * \brief draws 8 points liying on the circle
		 */
		void circlesPlotPoints(ImageGS8u &image,
				       const int &xCenter,
				       const int &yCenter,
				       const int i, const int j,
				       const unsigned char greyLevel);
		/// \endcond


		/** \brief draw a disc on an imageRGB8u
		 * \param image : input image where we will draw the disc
		 * \param xCenter : center of the circle (width)
		 * \param yCenter : center of the circle (height)
		 * \param radius : radius of the disc
		 * \param r : color of the disc : red component
		 * \param g : color of the disc : green component
		 * \param b : color of the disc : blue component
		 * \author Vincent
		 */
		void drawDisc(ImageRGB8u &image,
        		      const int xCenter,
			      const int yCenter,
        		      const double radius,
        		      const unsigned char r,
        		      const unsigned char g,
        		      const unsigned char b);


		/** \brief draw a disc on an imageGS8u
		 * \param image : input image where we will draw the disc
		 * \param xCenter : center of the circle (width)
		 * \param yCenter : center of the circle (height)
		 * \param radius : radius of the disc
		 * \param greyLevel : color of the line : grey scale
		 * \author Vincent
		 */
		void drawDisc(ImageGS8u &image,
        		      const int xCenter,
        		      const int yCenter,
        		      const double radius,
        		      const unsigned char greyLevel);


		/*
		 * End of Namespace
		 */
	}

/*
 * End of Anti-doublon
 */
#endif
