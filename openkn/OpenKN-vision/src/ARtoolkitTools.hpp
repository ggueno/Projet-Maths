/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * ARtoolkitTools.hpp created in 02 2010.
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
 * Anti-doublon
 */
#ifndef __OPENKN_VISION__ARTOOLKIT_TOOLS_HPP__
#define __OPENKN_VISION__ARTOOLKIT_TOOLS_HPP__

/*
 * External Includes
 */
#include <cstring>


/*
 * Internal Includes
 */
#include <OpenKN/image/ImageRGB.hpp>

/*
 * Namespace
 */
namespace kn{

	/**
	 * \brief Create an ARtoolkit marker pattern file and the printable image from an input pattern image.
	 * \param inputImage : the inut image (should be square and have at least a 16x16 resolution
	 * \param fileName : name of the pattern files to be created
	 * \param is16 : true if you want to use a 16x16 pixel pattern, false for 32x32
	 * \return the printable pattern image (with the black borders)
	 * \throw VisionException inputImage : invalid size
         * \author Vincent
	 */
	ImageRGB8u arToolkitMarkerMaker(const ImageRGB8u &inputImage,
					const std::string &fileName, 
					bool is16 = true);


	/*
	 * End of Namespace
	 */
}

/*
 * End of Anti-doublon
 */
#endif





