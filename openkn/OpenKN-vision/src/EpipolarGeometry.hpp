/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * EpipolarGeometry.hpp created in 12 2008.
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_EPIPOLAR_GEOMETRY_HPP__
#define __OPENKN_EPIPOLAR_GEOMETRY_HPP__

/*
 * External Includes
 */
#include <vector>

/*
 * Internal Includes
 */
#include "ProjectiveCamera.hpp"
#include <OpenKN/math/Matrix.hpp>
#include <OpenKN/math/Matrix3x3.hpp>
#include <OpenKN/math/Vector3.hpp>

   /*
    * Namespace
    */
namespace kn{

	  /**
	    * \brief Compute the normalized fundamental matrix F
	    * The data normalization provides a better accuracy of matrix values but the computation is slower; The fundamental matrix is computed from a points2d2d list where every correspondance (x,x') satisfies x'Fx= 0.
	    * \param points2d2d a vector of homogeneous vector3d pairs list (list of correspondance homogeneous vectors) (at least 8 correspondance)
	    * \return the fundamental matrix F
	    * \throw VisionException is number of pairs is incorrect 
	    */
	    kn::Matrix3x3d computeFundamentalMatrixNormalized(const std::vector< std::pair<kn::Vector3d,kn::Vector3d> >& points2d2d);

	  /**
	    * \brief Compute the unnormalized fundamental matrix F
	    * This approach skip the data normalization that causes a small loss of accuracy of matrix values but the computation is faster; The fundamental matrix is computed from a points2d2d list where every correspondance (x,x') satisfies x'Fx=0.
	    * \param points2d2d a vector of homogeneous vector3d pairs list (list of correspondance homogeneous vectors)(at least 8 correspondance)
	    * \return the fundamental matrix F
	    * \throw VisionException is number of pairs is incorrect
	    */
	    kn::Matrix3x3d computeFundamentalMatrixUnNormalized(const std::vector< std::pair<kn::Vector3d,kn::Vector3d> >& points2d2d);

	  /**
	    * \brief Compute the fundamental matrix F
	    * The fundamental matrix is computed from a points2d2d list where every correspondance (x,x') satisfies x'Fx=0.
	    * \param points2d2d a vector of homogeneous vector3d pairs list (list of correspondance homogeneous vectors)(at least 8 correspondance)
	    * \param normalized specifies if F is computed with data normalization or not
	    * \return the fundamental matrix F
	    */
	    kn::Matrix3x3d computeFundamentalMatrix(const std::vector< std::pair<kn::Vector3d,kn::Vector3d> >& points2d2d, 
						    const bool& normalized = true);

	  /**
	    * \brief force the fundamental matrix F to be rank 2
	    * A valid fundamental matrix should be rank 2 which is not ensured by the linear method. If necessary, this function replace F by the nearest 3x3 matrix of rank 2. F is decomposed by a SVD : F=UDV. The smalest singular value of D is set to zero which leads to a new matrix D'. The new F matrix is given by F'=UD'V
	    * \param F : the fundamental matrix to be enhanced
	    */
	    void enforcementFundamentalMatrix(kn::Matrix3x3d &F);

	  /**
	    * \brief compute the fundamental matrix between 2 projective cameras
	    * Compute the fundamental matrix F between 2 projective camera matrix P1 and P2 : F = [e2]xP2.P1+ (P+ = pseudo-inverse) and e2 = P2.C
	    * \param cam1 : the projective camera 1
	    * \param cam2 : the projective camera 2
	    * \return the fundamental matrix F
	    */
	    kn::Matrix3x3d computeFundamentalMatrix(const kn::ProjectiveCamera &cam1, const kn::ProjectiveCamera &cam2);

	  /**
	    * \brief compute 2 epipoles from a fundamental matrix
	    * Solve F.e1=0 and Ft.e2=0
	    * \param F : the fundamental matrix
	    * \param e1 : epipole of cam 1
	    * \param e2 : epipole of cam 2
	    */
	    void computeEpipoles(const kn::Matrix3x3d &F, kn::Vector3d &e1, kn::Vector3d &e2);

	    /**
	    * \brief compute a weak calibration for 2 matrices related by an fundamental matrix.
	    * P1=[Id|0] and P2=[e2xF|e2]
	    * \param P1 : the camera1 projection matrix to be set as P1=[Id|0]
	    * \param P2 : the camera2 projection matrix to be set as P2=[e2xF|e2]
	    * \param F : the fundamental matrix between image1 and image2
	    * \throw VisionException : invalid camera matrix size
	    * \author Vincent
	    */
	    void weakCalibration(kn::Matrix<double> &P1, kn::Matrix<double> &P2, const kn::Matrix3x3d &F);

   /*
    * End of Namespace
    */
}

/*
 * End of Anti-doublon
 */
#endif

