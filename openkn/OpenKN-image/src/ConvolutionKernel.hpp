/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * ConvolutionKernel.hpp created in 10 2008.
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
#ifndef __OPENKN_IMAGE__CONVOLUTIONKERNEL_HPP__
#define __OPENKN_IMAGE__CONVOLUTIONKERNEL_HPP__


/*
 * External Includes
 */

#include <iostream>
#include <string>
#include <cstring>


/*
 * Internal Includes
 */
#include "ImageException.hpp"

/*
 * Namespace
 */
namespace kn{
		/*
		 * Class definition
		 */
	 
		/** \brief Kernel used for convolution filter
		 *
		 */
		class ConvolutionKernel{ 
			/*
			 * Constructor & destructors
			 */
		public:
			/** \brief Constructor by default
			 *	Compute a defaut kernel size 3*3 with origin in (1,1) (at the center of kernel)
			 *	Values are all equals to 1 (average)
			 */
			ConvolutionKernel();
			/** \brief Constructor to build a rectangular kernel
			 *	\param width width of the kernel
			 *	\param height height of the kernel
			 *	\param xOrigin x-coordinate of the kernel origin
			 *	\param yOrigin y-coordinate of the kernel origin
			 *	\param values optional values buffer WHICH IS NOT COPYIED. If not used, the kernel is filled with 1.0
			 */
			ConvolutionKernel(unsigned int width, unsigned int height,
							  unsigned int xOrigin, unsigned int yOrigin, double* values=NULL);
			/** \brief Copy Constructor
			 *	\param e Convolution Kernel to clone
			 */
			ConvolutionKernel(const ConvolutionKernel & e);
			/** \brief dealoccates image convolution data
			 *
			 */
			~ConvolutionKernel();


		protected :
			unsigned int _width;			///< width of the kernel
			unsigned int _height;			///< height of the kernel
			int _xOrigin;						///< x-coordinate of the origin of the kernel
			int _yOrigin;						///< y-coordinate of the origin of the kernel
			double* _values;					///< buffer containing the values of the kernel

		public :
			/** \brief getting the width of the kernel
			 *	\return the width of the kernel
			 */
			inline unsigned int width()const {return _width;}

			/** \brief getting the height of the kernel
			 *	\return the height of the kernel
			 */
			inline unsigned int height() const{return _height;}

			/** \brief getting the x-coordinate of the origin of the kernel
			 *	\return the x-coordinate of the origin of the kernel
			 */
			inline unsigned int xOrigin()const {return _xOrigin;}

			/** \brief getting the y-coordinate of the origin of the kernel
			 *	\return the y-coordinate of the origin of the kernel
			 */
			inline unsigned int yOrigin()const{return _yOrigin;}

			/** \brief getting the buffer of the values of the kernel
			 *	\return the buffer of the values of the kernel
			 */
			inline const double* values()const{return _values;}

			/** \brief getting the lower bound of the kernel x-coordinates
			 *	x must be in the range [xLowerBound, xUpperBound[
			 *	\return the lower bound of the kernel x-coordinates
			 */
			inline int xLowerBound()const{return -_xOrigin;}

			/** \brief getting the lower bound of the kernel y-coordinates
			 *  y must be in the range [yLowerBound, yUpperBound[
			 *  \return the lower bound of the kernel y-coordinates
			 */
			inline int yLowerBound()const{return -_yOrigin;}

			/** \brief getting the upper bound of the kernel x-coordinates
			 *	x must be in the range [xLowerBound, xUpperBound[
			 *	\return the upper bound of the kernel x-coordinates
			 */
			inline int xUpperBound()const{return _width-_xOrigin;}

			/** \brief getting the upper bound of the kernel y-coordinates
			 * y must be in the range [yLowerBound, yUpperBound[
			 * \return the upper bound of the kernel y-coordinates
			 */
			inline int yUpperBound()const{return _height-_yOrigin;}


			/** \brief getting the value of the point (x,y) of the kernel.
			 *  getting the value of the point (x,y) of the kernel, in the kernel referencial.
			 * \param x the x-coordinate, in kernel referencial
			 * \param y the y-coordinate, in kernel referencial
			 * \return the value of the point (x,y) of the kernel
			 * \throw ImageException coordinates out of bounds
			 */
			double operator()(int x, int y)const;


			/**
			 * \brief Allocate the kernel k to this kernel
			 * \param k the kernel used to defined this kernel
			 * \return the kernel
			 */
			ConvolutionKernel& operator=(const ConvolutionKernel& k);

		};
	
		/*
		 * End of Namespace
		 */
}
 
/*
 * End of Anti-doublon
 */
#endif

