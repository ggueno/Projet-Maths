/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * CameraCalibrationIAC.hpp created in 04 2010.
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
#ifndef __OPENKN_VISION__CAMERA_CALIBRATION_IAC_HPP__
#define __OPENKN_VISION__CAMERA_CALIBRATION_IAC_HPP__

/*
 * External Includes
 */
#include <vector>


/*
 * Internal Includes
 */
#include <OpenKN/math/Matrix.hpp>
#include <OpenKN/math/Matrix3x3.hpp>
#include <OpenKN/math/Vector.hpp>
#include <OpenKN/math/Vector3.hpp>


/*
 * Namespace
 */
namespace kn{

      /**
        * \brief compute internal parameter matrix K from a set of orthogonal vanishing points using the Image of the Absolute Conic (IAC)
	* \param myList : a list of pair of vanishing points associated to perpendicular lines, at least 3 correspondances.
	* \return the internal parameter matrix K (3x3)
	* \throw VisionException : too few vanishing point correspondances. 
	*/
        kn::Matrix3x3d cameraCalibrationIAC(const std::vector< std::pair<kn::Vector3d,kn::Vector3d > > & myList);


      /**
        * \cond
	* \brief compute the absolute conic from a set of orthogonal vanishing points, and assuming that : the pixels are square and the image skew is 0.
	* \param myList :  a list of pair of vanishing points associated to perpendicular lines, at least 3 correspondances.
	*/
        kn::Matrix<double> computeAbsoluteConic(const std::vector< std::pair<kn::Vector3d,kn::Vector3d > > &myList);
	/// \endcond

      /**
	* \cond
	* \brief convert a vector to a matrix
	*/
	kn::Matrix<double> w2W(const kn::Vector<double> &w);
	/// \endcond

      /**
        * \cond
	* \brief creat a linear constraint (that already includes that the pixels are square and zero skew)
	*/
	kn::Vector<double> getSystemLine(const kn::Vector3d &v1, const kn::Vector3d &v2);
	/// \endcond

	/*
	 * End of Namespace
	 */
}

/*
 * End of Anti-doublon
 */
#endif
