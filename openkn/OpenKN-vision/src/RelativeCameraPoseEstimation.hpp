/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * RelativeCameraPoseEstimation.hpp created in 01 2009.
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
#ifndef __OPENKN_VISION__RELATIVE_CAMERA_POSE_ESTIMATION_HPP__
#define __OPENKN_VISION__RELATIVE_CAMERA_POSE_ESTIMATION_HPP__

/*
 * External Includes
 */
#include <OpenKN/math/Matrix.hpp>
#include <OpenKN/math/Matrix3x3.hpp>
#include <OpenKN/math/Vector.hpp>
#include <OpenKN/math/Vector3.hpp>
#include "ProjectiveCamera.hpp"

/*
 * Internal Includes
 */


/*
 * Namespace
 */
namespace kn {

  /**
   * \brief Computes a RT decomposition of a 3x3 Essential matrix E where R is a Rotation matrix and T a Translation.
   * From "Multiple View Geometry" 2nd Edition, Hartley Zisserman, Chapter 9 : Epipolar Geometry and the Fundamental Matrix.
   * (9.6.2 : Extraction of cameras from essential matrix.)
   * \param F : Fundamental matrix between cam1 and cam2.
   * \param K1 : Intrinsic parameter matrix (3x3) for cam1.
   * \param K2 : Intrinsic parameter matrix (3x3) for cam2.
   * \param point1 : image point correspondence from cam1.
   * \param point2 : image point correspondence from cam2.
   * \param cam1 : Resulting Projective camera \f$P1=K1[I|0]\f$
   * \param cam2 : Resulting Projective camera \f$P2=K2[R|-RC]=K2[R|t]\f$
   * \throw MathException K1 is not square matrix of size 3
   * \throw MathException K2 is not square matrix of size 3
   */
  void poseEstimationFromFundamental(const kn::Matrix3x3d &F,
  					  			     const kn::Matrix<double> K1, const kn::Matrix<double> K2,
  									 const kn::Vector3d &point1, const kn::Vector3d &point2,
  									 kn::ProjectiveCamera &cam1, kn::ProjectiveCamera &cam2);

  /*
   * End of Namespace
   */
}

/*
 * End of Anti-doublon
 */
#endif







