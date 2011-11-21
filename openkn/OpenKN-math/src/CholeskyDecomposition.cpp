/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * choleskyDecomposition.cpp created in 02 2010.
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
 * External Includes
 */
#include <cmath>

/*
 * Internal Includes
 */
#include "CholeskyDecomposition.hpp"


/*
 * Namespace
 */
namespace kn{

	// for more information about cholesky decomposition, you can refer to the "numerical recipes".
	kn::Matrix<double> choleskyDecomposition(const kn::Matrix<double> &A)
	{
	  // A should be square
	  if(A.rows() != A.columns())
	      throw MathException("Ivalid input matrix : shloud be square (and symetric)" ,"choleskyDecomposition");

	  kn::Matrix<double> L(A.rows(),A.columns(), 0.0);

	  for(int j=0; j<(int)A.columns(); ++j)
	    for(int i=j; i<(int)A.rows(); ++i)
	      {
		double sum = A[i][j];

		for(int k=0; k<j; ++k)
		  sum -= L[i][k] * L[j][k];

		if(i == j){
		  // diagonal element
		  if(sum <= 0.0) // if not positive defined : error
		      throw MathException("Ivalid input matrix : shloud be symetric (and square)" ,"choleskyDecomposition");
		  L[i][i] = sqrt(sum);
		}else{
		  // non diagonal element
		  L[i][j] = sum / L[j][j];
		}
	      }

	  return L;
	}


  /*
   * End of Namespace
   */
}




