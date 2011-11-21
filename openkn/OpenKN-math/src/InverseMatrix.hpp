/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * InverseMatrix.hpp created in 11 2008.
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
#ifndef __OPENKN_MATH__INVERSE_MATRIX_HPP__
#define __OPENKN_MATH__INVERSE_MATRIX_HPP__

#include "SVD.hpp"
#include "GaussianElimination.hpp"

namespace kn{

  /**
   * \brief Compute the inverse of a given square matrix
   * The inverse is given by A^(-1) = V*[1/D]*U^(t)
   * with V, D and U computed with the SVD
   * \param m a square matrix
   * \return the inverse of the input matrix
   * \throw MathException the parameter is not a square matrix
   */
  Matrix<double> inverseMatrixSVD(const Matrix<double>& m);

  /**
   * \brief Compute the pseudo-inverse of a given singular matrix
   * The pseudo-inverse is given by A^(+) = (A^(T)*A)^(-1)*A^(T)
   * (A^(T)*A)^(-1) is computed using SVD inverting process
   * \param m a matrix
   * \return the pseudo-inverse of the input matrix
   */
  Matrix<double> pseudoInverseMatrixSVD(const Matrix<double>& m);

  /**
   * \brief Compute the inverse of a given square matrix
   * The inverse is computed with a gaussian elimination
   * \param m a square matrix
   * \param total true to perform a total elimation (including rows permutations : slower, more accurate), false for a partial elimation.
   * \return the inverse of the input matrix
   * \throw MathException the parameter is not a square matrix
   */
  Matrix<double> inverseMatrixGaussianElimination(const Matrix<double>& m, const bool total = false);

  /**
   * \brief Compute the pseudo-inverse of a given singular matrix
   * The pseudo-inverse is given by A^(+) = (A^(T)*A)^(-1)*A^(T)
   * (A^(T)*A)^(-1) is computed using a gaussian elimation inverting process
   * \param m a matrix
   * \param total true to perform a total elimation (including rows permutations : slower, more accurate), false for a partial elimation.
   * \return the pseudo-inverse of the input matrix
   */
  Matrix<double> pseudoInverseMatrixGaussianElimination(const Matrix<double>& m, const bool total = false);


}

#endif
