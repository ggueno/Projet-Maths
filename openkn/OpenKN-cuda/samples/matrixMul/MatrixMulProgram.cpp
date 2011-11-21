/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * MatrixMulProgram.cpp created in 11 2008.
 * Mail : biri@univ-mlv.fr                    
 *                                                     
 * This file is part of the libIMAC-cuda.
 *
 * The libIMAC-cuda is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The libIMAC-cuda is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/


/*
 * Internal Includes
 */
#include "MatrixMulProgram.hpp"


extern  void initMatrixMul(CudaParams * c);
extern  void releaseMatrixMul(CudaParams * c);
extern  void runMatrixMul(CudaParams * c);


/*
 * Functions definitions
 */
void MatrixMulProgram::init() {
	initMatrixMul(&cp);
}

void MatrixMulProgram::run() {
	runMatrixMul(&cp);
}

void MatrixMulProgram::release() {
	releaseMatrixMul(&cp);
}
