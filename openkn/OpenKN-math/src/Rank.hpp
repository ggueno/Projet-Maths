/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * Rank.hpp created in 08 2009.
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
#ifndef __OPENKN_MATH_RANK_HPP__
#define __OPENKN_MATH_RANK_HPP__


/*
 * External Includes
 */
#include <algorithm>

/*
 * Internal Includes
 */
#include "MathException.hpp"
#include "Matrix.hpp"


namespace kn{

  /**
   * \brief compute the rank of a matrix (template T should be float or double)
   * \param A_ : the input matrix (don't have to be a square matrix)
   * \return the rank of the matrix A
   */
  template <class T>
  unsigned int rank(const Matrix<T> & A_){
    // thresold to decide whether a pivot is zero or not
    const double rankZero = 1.0e-10;

    // make a copy
    Matrix<T> A(A_);

    // make A triangular
    unsigned int nbIteration = 0;
    while(nbIteration < A.rows()){

      // find the pivot
      T maxValue;
      unsigned int maxValueRow,maxValueCol;
      rankFindPivot(A,nbIteration,maxValueRow,maxValueCol,maxValue);

      // check if the "pivot" is non-null
      if(fabs(maxValue) < rankZero)
	return nbIteration; // the matrix is singular (not full rank).

      // if required, swap rows
      if(maxValueRow != nbIteration){
	// swap the non zero part of the rows
	std::swap_ranges(&(A[maxValueRow][nbIteration]),A[maxValueRow]+A.columns(),&(A[nbIteration][nbIteration]));
      }

      // if required, swap columns
      if(maxValueCol != nbIteration){
	// swap columns
	A.swapColumns(maxValueCol,nbIteration);
      }

      // row alimination (let's put some 0)
      rankRowsElimination(A,nbIteration);

      // next iteration
      ++nbIteration;
    }

    // no zero found : full rank
    return A.rows();
  }


  /**
   * \cond
   * \brief find the pivot on the submatrix defined by A and nbIteration
   * \param A : input matrix
   * \param nbIteration : the current iteration number
   * \param maxValueRow : the pivot row index
   * \param maxValueCol : the pivot column index
   * \param maxValue : the pivot absolute value
   */
  template <class T>
  void rankFindPivot(const Matrix<T> & A, const unsigned int nbIteration, 
		     unsigned int & maxValueRow, unsigned int & maxValueCol, T & maxValue){

      maxValueRow = maxValueCol = nbIteration;
      maxValue = A[nbIteration][nbIteration];

      for(unsigned int i = nbIteration ; i < A.rows(); ++i)
	for(unsigned int j = nbIteration ; j < A.columns(); ++j) {
	  T tmp = T(fabs((A[i][j])));
	  if((tmp > maxValue)){
	    maxValueRow = i;
	    maxValueCol = j;
	    maxValue = tmp;
	  }
	}
  }
  /// \endcond


  /**
   * \cond
   * \brief perform elementary operations (row_i = row_i – Aik/Akk row_k) on the matrix A to obtain a 0 sub colomn under the pivot (cf gaussian elimination)
   * \param A : input matrix
   * \param nbIteration : the current iteration number
   */
  template <class T>
  void rankRowsElimination(Matrix<T> & A, const unsigned int nbIteration){
      // for every remaining rows
      for(unsigned int i = nbIteration+1; i < A.rows(); ++i){ 
        T tmp = T(A[i][nbIteration] / A[nbIteration][nbIteration]);

	// row_i = row_i – Aik/Akk row_k
	A[i][nbIteration] = T(0);
        for(unsigned int j = nbIteration+1; j < A.columns(); ++j){ 
            A[i][j] -=  tmp * A[nbIteration][j];
        }
      }
  }
  /// \endcond



  /**
   * \cond
   * \brief this type is invalid for the rank computation. The input matrix should be converted in float or double.
   * \param A : input matrix
   * \throw mathexception : invalid matrix type
   */
  unsigned int rank(const Matrix<int> & A_){
      throw MathException("invalid input matrix type, convert your matrix in float or double" ,"rank"); 
  }
  /// \endcond


  /*
   * End of Namespace
   */
}

/*
 * End of Anti-doublon
 */
#endif
