/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * ioTGA.hpp created in 10 2008.
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
#ifndef __OPENKN_IMAGE__IOTGA_HPP__
#define __OPENKN_IMAGE__IOTGA_HPP__

/*
 * External Includes
 */
#include <string>

/*
 * Internal Includes
 */
#include "Image.hpp"

/*
 * Namespace
 */
namespace kn{
		/** \addtogroup Macros */
		/*@{*/
		/** \defgroup TGA_image_type TGA Image Type (7 kinds) */
		/*@{*/
		enum TGA_file_type {NONE_TGA=0, INDEXED_TGA=1, COLOR_TGA=2, GS_TGA=3,
												INDEXED_RLE_TGA=9, COLOR_RLE_TGA=10, GS_RLE_TGA=11};
		/*@}*/
		/*@}*/


		/** \brief Loader function for TGA image.
			* This is a generic TGA loading function. It handles both compress and no
			* compress format file.<br>
			* Exact format is defined here : http://www.fileformat.info/format/tga/index.dir
			* or more formaly here :
			* http://tfcduke.developpez.com/tutoriel/format/tga/fichiers/tga_specs.pdf
			* \param res Image qui va recevoir les données du fichier image
			* \param filename Name of the file to load
			* \return The type of the TGA file (see kn::TGA_file_type)
			* \todo Must this function check that the extension of the name file is correct ? (.tga/.TGA)
			* \todo Color map TGA loading
			* \todo Horizontal mirrored TGA loading
			* \todo Translated image loading
			* \todo Dealing with ARGB
			*/
		int loadTGA(Image<unsigned char>& res,const std::string& filename);


	/*
	 * End of Namespace
	 */
}

/*
 * End of Anti-doublon
 */
#endif
