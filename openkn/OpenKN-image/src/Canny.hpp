/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * Canny.hpp created in 03 2009.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_IMAGE__CANNY_HPP__
#define __OPENKN_IMAGE__CANNY_HPP__

/*
 * External Includes
 */
#include <list>
#include <vector>


/*
 * Internal Includes
 */

#include "ImageGS.hpp"

/*
 * Namespace
 */
namespace kn{
       /**
	* \brief Compute the Canny filtering. The canny filter is in 3 steps :
	* 1 - computation  of gradient norme and direction
	* 2 - keeping only pixels with gradient norme local maxima, in regard of perpendicular direction of the gradient direction
	* 3 - keeping only pixels with values saved by hysteresis, i.e, pixels which :
	*     a - have a gradient norme higher than the upper threshold
	*     b - or have a gradient norme higher than the lower threshold, and which have a neighbour already saved by the hysteresis.
	* \param inputImage : a grayscale image
	* \param outputImage : a grayscale image, where will be stored the result. Same dimensions that the input are required.
	* \param lowerThres : the lower threshold for the hysteresis step
	* \param upperThres : the upper threshold for the hysteresis step
	*/
	void canny(kn::ImageGS8u &inputImage, kn::ImageGS8u &outputImage, unsigned int lowerThres, unsigned int upperThres);

       /*
	* End of Namespace
	*/

}

/*
 * End of Anti-doublon
 */
#endif
