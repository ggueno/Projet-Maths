/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * Homography3d.hpp created in 02 2010.
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
#ifndef __OPENKN_VISION__HOMOGRAPHY_3D_HPP__
#define __OPENKN_VISION__HOMOGRAPHY_3D_HPP__

/*
 * External Includes
 */
#include <vector>
#include <utility>

/*
 * Internal Includes
 */
#include <OpenKN/math/Matrix4x4.hpp>
#include <OpenKN/math/Vector4.hpp>

/*
 * Namespace
 */
namespace kn{

  /**
   * \brief Compute the 3d homography matrix H
   *
   * The homography is computed from a points3d3d list where every correspondance (a,a') satisfies \f$ a' = Ha\f$\n
   * Thus, a is the input data and a' is the transformed point (both in homogeneous coordinates).\n
   * Consider we have respectively A and A' two matrices (4,n) with corresponding points \f$a_{i}\f$, and \f$a'_{i}\f$ on each column \n
   * \f$ HA=A' \Longleftrightarrow H=A'A^{-1}\f$\n
   * \param points3d3d a vector of homogeneous vector4d pairs (at least 4 correspondances needed)
   * \return the homography matrix4x4d H
   * \throw VisionException at least 4 match required in point3d3d
   */
  kn::Matrix4x4d computeHomography3d(const std::vector< std::pair<kn::Vector4d,kn::Vector4d> >& points3d3d);

  /*
   * End of Namespace
   */
}

/*
 * End of Anti-doublon
 */
#endif
