/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * MatrixMulProgram.hpp created in 11 2008.
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
#ifndef __LIBIMAC_CUDA__MATRIXMULPROGRAM_HPP__
#define __LIBIMAC_CUDA__MATRIXMULPROGRAM_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <OpenKN/cuda/CudaProgram.hpp>

/*
 * Internal Includes
 */
#include <matrixMul.h>

/*
 * Class definition
 */

/** \brief Interface for Cuda programs
 *
 */
class MatrixMulProgram : public kn::CudaProgram {
public :	
	/* \brief Initialize cuda program, memory allocations...
	 */
	void init();

	/* \brief Run cuda program
	 */
	void run();

	/* \brief release the GPU
	 */
	void release();


public :
	CudaParams cp;
};

/*
 * End of Anti-doublon
 */
#endif
