/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * CudaManagerTest.hpp created in 09 2009.
 * Mail : biri@univ-mlv.fr					  
 *													   
 * This file is part of the OpenKraken-cuda.
 *
 * The OpenKraken-cuda is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-cuda is distributed in the hope that it will be useful,
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
#ifndef __OpenKN_CUDA__CUDATEST_HPP__
#define __OpenKN_CUDA__CUDATEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/cuda/CudaManager.hpp>

/*
 * Class definition
 */

class CudaManagerTest : public CxxTest::TestSuite {
public:
	void testCudaManagerStart( void ) {
		kn::CudaManager::getInstance().start();
		TS_ASSERT(!kn::CudaManager::getInstance().isStopped());		
	}

	void testCudaManagerStop( void ) {
		kn::CudaManager::getInstance().stop();
		kn::CudaManager::getInstance().waitEnd();
		TS_ASSERT(kn::CudaManager::getInstance().isStopped());		
	}

};


/*
 * End of Anti-doublon
 */
#endif
