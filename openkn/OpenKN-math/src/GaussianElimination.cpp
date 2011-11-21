/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * GaussianElimination.cpp created in 08 2009.
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
#include "GaussianElimination.hpp"

/*
 * Namespace
 */
namespace kn{

	
	unsigned int gaussianElimination(Matrix<float> & A, Vector<float> &b, Vector<float> &x, const bool total);
	unsigned int gaussianElimination(Matrix<double> & A, Vector<double> &b, Vector<double> &x, const bool total);
	
	unsigned int gaussianEliminationPartial(Matrix<float> & A, Vector<float> &b, Vector<float> &x);
	unsigned int gaussianEliminationPartial(Matrix<double> & A, Vector<double> &b, Vector<double> &x);
	
	unsigned int gaussianEliminationTotal(Matrix<float> & A, Vector<float> &b, Vector<float> &x);
	unsigned int gaussianEliminationTotal(Matrix<double> & A, Vector<double> &b, Vector<double> &x);
	
	unsigned int gaussianEliminationInverseMatrix(const Matrix<float> & A, Matrix<float> & Ainverse, const bool total);
	unsigned int gaussianEliminationInverseMatrix(const Matrix<double> & A, Matrix<double> & Ainverse, const bool total);

	unsigned int gaussianEliminationInverseMatrixPartial(const Matrix<float> & A_, Matrix<float> & Ainverse);
	unsigned int gaussianEliminationInverseMatrixPartial(const Matrix<double> & A_, Matrix<double> & Ainverse);
	
	unsigned int gaussianEliminationInverseMatrixTotal(const Matrix<float> & A_, Matrix<float> & Ainverse);
	unsigned int gaussianEliminationInverseMatrixTotal(const Matrix<double> & A_, Matrix<double> & Ainverse);
	
	
	
  /*
   * End of Namespace
   */
}
