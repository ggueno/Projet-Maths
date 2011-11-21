/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * OpencvCalibrationTools.hpp created in 03 2009.
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
#ifndef __OPENKN_VISION__OPENCV_CALIBRATION_TOOLS_HPP__
#define __OPENKN_VISION__OPENCV_CALIBRATION_TOOLS_HPP__

/*
 * External Includes
 */
#include <list>
#include <vector>
#include<opencv/cv.h>


/*
 * Internal Includes
 */
#include <OpenKN/math/Vector3.hpp>
#include <OpenKN/image/ImageRGB.hpp>

/*
 * Namespace
 */
namespace kn{
       /**
	* \brief detect an openCV chessboard and return a set of 2d correspondances (vector of pair of Vector3).
	* This function is based on the OpenCV library
	* \param inputImage : a RGB image constaining a chessboard
	* \param myList : the 2d-2D homogeneous vector list to be filled by this function
	* \param markerNbColumns : number of columns on the chessboard
	* \param markerNbLines : number of lines on the chessboard
	* \param markerSquareSize : size of a side of a chessboard square (in "your" unit)
	* \param drawDetectionOn : if "true", this function will draw the detected marker on the input image
	* \return a vector of 2d-2d correspondances (homogeneous 2d vector = Vector3)
	*/
	void opencvChessboardDetection(kn::ImageRGB8u &inputImage,
				       std::vector< std::pair<kn::Vector3d,kn::Vector3d> > &myList,
				       const unsigned int markerNbColumns,
				       const unsigned int markerNbLines,
				       const double markerSquareSize,
				       const bool drawDetectionOn = false);

	/*
	 * End of Namespace
	 */

}

/*
 * End of Anti-doublon
 */
#endif
