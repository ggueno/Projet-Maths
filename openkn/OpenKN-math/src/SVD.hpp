/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * SVD.hpp created in 10 2008.
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
#ifndef __OPENKN_MATH__SVD_HPP__
#define __OPENKN_MATH__SVD_HPP__

#include "Matrix.hpp"

namespace kn{

  /**
   * \brief Construct the Singular value Decomposition of a matrix M
   * The SVD is given as A = UwV^T
   * In our case, U will replace A
   * The following used algorithm comes from Numerical Recipes Second Edition (1992)
   * \param a the input matrix that will be replaced by U (size m x n)
   * \param w the diagonal matrix constructed as a vector with the singular values (size n)
   * \param v the orthogonal matrix (not transposed) (size n)
   * \throw MathException invalid size of w or v
   */
  void decompositionSVD(Matrix<double>& a,
      Vector<double>& w,
      Matrix<double>& v);


  /**
   * \brief Put in decreasing order the singular values (vector w)
   * The sorting algorithm used is the bubble sort
   * \param u the input matrix that will be replaced by U (size m x n)
   * \param w the diagonal matrix constructed as a vector with the singular values (size n)
   * \param v the orthogonal matrix (not transposed) (size n x n)
   * \throw MathException invalid size of w or v
   */
  void sortSingularValuesSVD(Matrix<double>& u,
      Vector<double>& w,
      Matrix<double>& v);

  /**
   * \brief Resolve the system (uwv)x=b with uwv the singular value decomposition of a matrix A
   * The following used algorithm comes from Numerical Recipes Second Edition (1992)
   * \param u the input matrix that will be replaced by U (size m x n)
   * \param w the diagonal matrix constructed as a vector with the singular values (size n)
   * \param v the orthogonal matrix (not transposed) (size n x n)
   * \param b the solutions vector (size m)
   * \param x the output solutions vector (size n)
   * \throw MathException invalid size of w, v, b or x
   */
  void solveSVD(const Matrix<double>& u,
      const Vector<double>& w,
      const Matrix<double>& v,
      const Vector<double>& b,
      Vector<double>& x);

}
#endif
