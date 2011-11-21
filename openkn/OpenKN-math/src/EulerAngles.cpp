/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * EulerAngles.cpp created in 01 2009.
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
 * Internal Includes
 */
#include "EulerAngles.hpp"

/*
 * Namespace
 */
namespace kn {

  /*
   * \brief compute a rotation matrix from specified angles in x-y-z-axis (euler angles) in the order x, y then z
   * \param angleX : angle in x-axis in radian
   * \param angleY : angle in y-axis in radian
   * \param angleZ : angle in z-axis in radian
   * \return : the 3x3 rotation matrix
   */
   kn::Matrix3x3d eulerAngles3x3d(const double &angleX, const double &angleY, const double &angleZ){

	// x
	kn::Matrix3x3d Rx;
	Rx.setIdentity();
	Rx[1][1] =  Rx[2][2] = cos(angleX);
	Rx[1][2] = -sin(angleX);
	Rx[2][1] = -Rx[1][2];

	// y
	kn::Matrix3x3d Ry;
	Ry.setIdentity();
	Ry[0][0] =  Ry[2][2] = cos(angleY);
	Ry[0][2] =  sin(angleY);
	Ry[2][0] = -Ry[0][2];

	// z
	kn::Matrix3x3d Rz;
	Rz.setIdentity();
	Rz[0][0] = Rz[1][1] = cos(angleZ);
	Rz[0][1] = -sin(angleZ);
	Rz[1][0] = -Rz[0][1];

	// in the order Z-Y-X
	return Rz * Ry * Rx;
  }


  /*
   * End of Namespace
   */
}
