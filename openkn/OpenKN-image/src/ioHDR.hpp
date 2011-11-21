/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * ioHDR.hpp created in 10 2008.
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
#ifndef __OPENKN_IMAGE__IOHDR_HPP__
#define __OPENKN_IMAGE__IOHDR_HPP__

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
namespace kn {
	/** \brief Load function for HDR images.
		* This is a generic HDR loading class. It handles .hdr format file.<br>
		* File format is available through http://www.graphics.cornell.edu/~bjw/rgbe.html
		* \author Venceslas BIRI (biri@univ-mlv.fr)
		* \param res Image recieving data from JPG file
		* \param filename Name of the file to load
		* \return 1 if succed (otherwise it rises exception)
		*/
	int loadHDR(Image<float>& res,const std::string& filename);

/*
 * End of Namespace
 */
}

/*
 * End of Anti-doublon
 */
#endif
