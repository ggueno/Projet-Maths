/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * choleskyDecomposition.hpp created in 02 2010.
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
#ifndef __OPENKN_MATH_CHOLESKY_DECOMPOSITION_HPP__
#define __OPENKN_MATH_CHOLESKY_DECOMPOSITION_HPP__


/*
 * External Includes
 */


/*
 * Internal Includes
 */
#include "MathException.hpp"
#include "Matrix.hpp"


namespace kn{

  /**
   * \brief decompose the matrix A into \f$ A = L.L^\top \f$ where L is lower triangular matrix and A is a square symetric matrix.
   * \param A : the input matrix : should be square and symetric.
   * \return L : a lower triangular matrix with \f$ A = L.L^\top \f$
   * \throw mathexception : invalid input matrix (shloud be square and symetric)
   */
   kn::Matrix<double> choleskyDecomposition(const kn::Matrix<double> &A);



  /*
   * End of Namespace
   */
}

/*
 * End of Anti-doublon
 */
#endif




