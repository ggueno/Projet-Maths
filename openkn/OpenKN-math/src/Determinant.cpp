/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * determinant.cpp created in 01 2009.
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
#include "Determinant.hpp"

/*
 * Namespace
 */
namespace kn {

	float  determinant3x3(Matrix<float> &mat);
	double determinant3x3(Matrix<double> &mat);
	int    determinant3x3(Matrix<int> &mat);

	float  determinant(Matrix<float> &mat);
	double determinant(Matrix<double> &mat);
	int    determinant(Matrix<int> &mat);
	
  /*
   * End of Namespace
   */
}
