/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * CameraCalibrationDLT.hpp created in 04 2010.
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
#ifndef __OPENKN_VISION__CAMERA_CALIBRATION_DLT_HPP__
#define __OPENKN_VISION__CAMERA_CALIBRATION_DLT_HPP__

/*
 * External Includes
 */
#include <vector>


/*
 * Internal Includes
 */
#include <OpenKN/math/Matrix.hpp>
#include <OpenKN/math/Matrix3x3.hpp>
#include <OpenKN/math/Matrix4x4.hpp>
#include <OpenKN/math/Vector.hpp>

/*
 * Namespace
 */
namespace kn{

	/**
		* \brief compute the projection matrix P from a set of 3d-2d correspondances (X <-> x, with x=PX), cf. Multiple View Geometry, Hartley Zisserman, Computation of the camera matrix P
		* \param myList3d2d : a list of 3d-2d correspondances, in homogenous coordinates.
		* \return the projection matrix (3x4)
		* \throw VisionException : too few 3d-2d correspondances to perform the camera calibration.
		*/
	kn::Matrix<double> cameraCalibrationDLT(const std::vector< std::pair<kn::Vector<double,StaticStorePolicy<double,4> >,kn::Vector<double,StaticStorePolicy<double,3> > > > & myList3d2d);


	/**
		* \cond
		* \brief data normalization when computing the P matrix from a set of 3d-2d correspondances.
		* \param myList : a list of 3d-2d correspondances, in homogenous coordinates, to be normalized.
		* \param T : 3x3 transformation matrix (will be set by the function)
		* \param Tinverse : 3x3 inverse of T, to be set by the function
		* \param U : 4x4 transformation matrix (will be set by the function)s
		*/
	void normalizationDLT(std::vector< std::pair<kn::Vector<double,StaticStorePolicy<double,4> >,kn::Vector<double,StaticStorePolicy<double,3> > > > &myList,
			kn::Matrix3x3<double> &T,
			kn::Matrix3x3<double> &Tinverse,
			kn::Matrix4x4<double> &U);
	/// \endcond


	/**
		* \cond
		* \brief Build the linear system to solve for the projection matrix computation. DLT : Direct Linear Transform.
		* \param A : the main matrix of the linear system. This matrix is filled in this method.
		* \param myList : a list of 3d-2d correspondances, in homogenous coordinates.
		*/
	void makeSystemDLT(kn::Matrix<double> &A,
										const std::vector<std::pair<kn::Vector<double,StaticStorePolicy<double,4> >,kn::Vector<double,StaticStorePolicy<double,3> > > > &myList);
	/// \endcond

	/*
	 * End of Namespace
	 */
}

/*
 * End of Anti-doublon
 */
#endif
