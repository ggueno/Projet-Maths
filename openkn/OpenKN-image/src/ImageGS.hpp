/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * ImageGS.hpp created in 09 2008.
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
#ifndef __OPENKN_IMAGE__IMAGEGS_HPP__
#define __OPENKN_IMAGE__IMAGEGS_HPP__

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

		/** \brief Class for Grey Scale image
		 *
		 */
		template<typename T>
		class ImageGS : public Image<T> {

			/*
			 * Constructor & destructors
			 */
		public:
			/** \brief Constructor to build a 0 size image
			 */
			ImageGS();
			/** \brief Constructor to build an allocated empty image Grey Scale or an image from a raw data buffer
			 *	\param w width of the image
			 *	\param h height of the image
			 *	\param buffer optional data buffer WHICH IS NOT COPYIED
			 */
			ImageGS(const size_t w, const size_t h, T * buffer=NULL);
			/** \brief Copy Constructor
			 * \param e Image to clone
			 */
			ImageGS(const ImageGS & e);
			/** \brief dealoccates image data
			 */
			virtual ~ImageGS();

		public :
			/** \brief get value of the asked pixel (with bounds checking)
			 *	\param x width position of the pixel
			 *	\param y height position of the pixel
			 *	\return a value of the pixel
			 */
			inline virtual T & at(const unsigned int x, const unsigned int y) {
				if (x>=this->width() || y>=this->height() ) {
					std::ostringstream o("Operator(");
					o << x << "," << y << ") ";
					throw ImageException(o.str(), "Invalid range");
				}
				return (*this)(x,y);
			}

			/** \brief get value of the asked pixel
			 *	\param x width position of the pixel
			 *	\param y height position of the pixel
			 *	\return a value of the pixel
			 */
			inline virtual T & operator()(const unsigned int x, const unsigned int y){
				return (this->rows[y][x]);
			}

		};

		/*
		 * Templates definitions
		 */

		/*
		 * Functions definitions
		 */
		template<typename T>
		ImageGS<T>::ImageGS() : Image<T>() {
			this->imageNbChannel = 1;
		}

		template<typename T>
		ImageGS<T>::ImageGS(const size_t w, const size_t h, T* buffer) : Image<T>(w,h,1,buffer) {
		}


		template<typename T>
		ImageGS<T>::ImageGS(const ImageGS<T> & e) : Image<T>(e) {
		}

		template<typename T>
		ImageGS<T>::~ImageGS(void) {
		}


		/*
		 * Type definition
		 */
		typedef ImageGS<float> ImageGSf;
		typedef ImageGS<double> ImageGSd;
		typedef ImageGS<unsigned char> ImageGS8u;
		typedef ImageGS<unsigned short int> ImageGS16u;
		typedef ImageGS<unsigned int> ImageGS32u;
		typedef ImageGS<unsigned long int> ImageGS64u;
		typedef ImageGS<char> ImageGS8s;
		typedef ImageGS<short int> ImageGS16s;
		typedef ImageGS<int> ImageGS32s;
		typedef ImageGS<long int> ImageGS64s;

		/*
		 * End of Namespace
		 */
}

/*
 * End of Anti-doublon
 */
#endif
