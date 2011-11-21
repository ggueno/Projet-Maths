/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * ExtrinsicMultiCameraAdjustment.hpp created in 12 2008.
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
#ifndef __OPENKN_VISION__EXTRINSICMULTICAMERAADJUSTMENT_HPP__
#define __OPENKN_VISION__EXTRINSICMULTICAMERAADJUSTMENT_HPP__

/*
 * External Includes
 */
#include <vector>
#include <map>


/*
 * Internal Includes
 */
#include <OpenKN/vision/ProjectiveCamera.hpp>
#include <OpenKN/vision/MultiCam3D2DCorrespondences.hpp>

/*
 * Namespace
 */
namespace kn {
	
	
	/**
       * \brief Compute the relative extrinsic parameters of a set of camera, using correspondences sets
       * \param cameras vector of cameras parameters
       * \param correspondences correspondences between 3D points and 2D points in camera images
       */
	void extrinsicMultiCameraAdjustment( std::vector< kn::ProjectiveCamera >& cameras, const kn::MultiCam3D2DCorrespondences & correspondences);

/*
 * End of Namespace
 */
}

/*
 * End of Anti-doublon
 */
#endif
