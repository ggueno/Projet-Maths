/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * ARtoolkitMarkerMakerSample.cpp created in 02 2010.
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


/*
 * Internal Includes
 */
#include <OpenKN/image/ImageRGB.hpp>
#include <OpenKN/image/ioJPG.hpp>
#include <OpenKN/vision/ARtoolkitTools.hpp>

int main()
{
	kn::ImageRGB8u inputImage;
	kn::loadJPG(inputImage,"inputData/ARmarker.jpg");

	kn::ImageRGB8u printableImage( kn::arToolkitMarkerMaker(inputImage,"outputData/ARmarker.patt",true) );
	kn::saveJPG(printableImage,"outputData/ARmarkerPrintable.jpg");

	return 0;
}

