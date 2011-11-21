/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * ImageProcessing.hpp created in 10 2008.
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
#ifndef __OPENKN_IMAGE__IMAGEPROCESSING_HPP__
#define __OPENKN_IMAGE__IMAGEPROCESSING_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>

/*
 * Internal Includes
 */
#include "Image.hpp"

/*
 * Namespace
 */
namespace kn{
		/*
		 * Class definition
		 */
		/** \brief Interface for images processing
		 *
		 */
		template<typename T> class ImageProcessing { 
			/*
			 * Constructor & destructors
			 */		
		
		public:
			/** \brief Virtual destructor 
			 *
			 */
			virtual ~ImageProcessing(){}
			
			
			/** \brief Processing applied on copy of image
			 *	\param img Image to process
			 *	\param result Result image
			 */
			virtual void filterOnCopy(const Image<T> & img,	 Image<T> & result)=0;
			
			/** \brief Processing applied in place on image
			 *	\param img Image to process
			 */
			virtual void filter(Image<T> & img)=0;
			
		};
		
		
		/*
		 * End of Namespace
		 */
}
 
/*
 * End of Anti-doublon
 */
#endif

