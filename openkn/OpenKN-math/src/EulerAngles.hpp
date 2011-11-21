/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * EulerAngles.hpp created in 01 2009.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-math.
 *
 * The OpenKraken-math is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-math is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_MATH__EULER_ANGLES_HPP__
#define __OPENKN_MATH__EULER_ANGLES_HPP__

/*
 * External Includes
 */
#include <cmath>

/*
 * Internal Includes
 */
#include "Matrix3x3.hpp"


/*
 * Namespace
 */
namespace kn{

  /**
   * \brief compute a rotation matrix from specified angles in x-y-z-axis (euler angles) in the order x, y then z
   * \param angleX : angle in x-axis in radian
   * \param angleY : angle in y-axis in radian
   * \param angleZ : angle in z-axis in radian
   * \return : the 3x3 rotation matrix
   */
    kn::Matrix3x3d eulerAngles3x3d(const double &angleX, const double &angleY, const double &angleZ);

  /*
   * End of Namespace
   */
}

/*
 * End of Anti-doublon
 */
#endif







