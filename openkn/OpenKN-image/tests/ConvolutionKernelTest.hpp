/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * ConvolutionKernelTest.hpp created in 09 2008.
 * Mail : biri@univ-mlv.fr                    
 *                                                     
 * This file is part of the OpenKraken-image.
 *
 * The OpenKraken-image is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-image is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_IMAGE__CONVOLUTIONKERNELTEST_HPP__
#define __OPENKN_IMAGE__CONVOLUTIONKERNELTEST_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <cstring>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/image/ConvolutionKernel.hpp>

/*
 * Class definition
 */

class ConvolutionKernelTest : public CxxTest::TestSuite {
public:

   void testConstructorWith4Parameters( void ) {
        kn::ConvolutionKernel kernel(2,4,0,1);
        TS_ASSERT_EQUALS(kernel.width(),2);
        TS_ASSERT_EQUALS(kernel.height(),4);
        TS_ASSERT_EQUALS(kernel.xOrigin(),0);
        TS_ASSERT_EQUALS(kernel.yOrigin(),1);
        TS_ASSERT_EQUALS(kernel.values()[0],1.0);
   }


 void testConstructorWith5Parameters( void ) {
 		double static_buffer[] = {1,2,3,4,5,6,7,8};
        double * dyn_buffer = new double[8];
        memcpy(dyn_buffer,static_buffer,8*sizeof(double));
        
        kn::ConvolutionKernel kernel(2,4,0,1,dyn_buffer);
        TS_ASSERT_EQUALS(kernel.width(),2);
        TS_ASSERT_EQUALS(kernel.height(),4);
        TS_ASSERT_EQUALS(kernel.xOrigin(),0);
        TS_ASSERT_EQUALS(kernel.yOrigin(),1);
        TS_ASSERT_EQUALS(kernel.values()[4],5);
     
    }


   void testConstructorByCopy( void ) {
        kn::ConvolutionKernel kernel(2,4,0,1);
	kn::ConvolutionKernel kernel2(kernel);
       	TS_ASSERT_EQUALS(kernel2.width(),2);
        TS_ASSERT_EQUALS(kernel2.height(),4);
        TS_ASSERT_EQUALS(kernel2.xOrigin(),0);
        TS_ASSERT_EQUALS(kernel2.yOrigin(),1);
        TS_ASSERT_EQUALS(kernel2.values()[0],1.0);
 	TS_ASSERT_DIFFERS(kernel.values(), kernel2.values());
    }

    void testAccessorsAndKernelCoords(void){
	    double static_buffer[] = {1.0,2.0,
		    		      3.0,4.0,
	      			      5.0,6.0,
				      7.0,8.0};
	    double * dyn_buffer = new double[8];
	    memcpy(dyn_buffer,static_buffer,8*sizeof(double));
	    kn::ConvolutionKernel kernel(2,4,0,1,dyn_buffer);
	    TS_ASSERT_EQUALS(kernel.xLowerBound(),0);
	    TS_ASSERT_EQUALS(kernel.xUpperBound(),2);
	    TS_ASSERT_EQUALS(kernel.yLowerBound(),-1);
	    TS_ASSERT_EQUALS(kernel.yUpperBound(),3);
	    TS_ASSERT_EQUALS(kernel(0,1), 5.0);
	    TS_ASSERT_EQUALS(kernel(1,2), 8.0);
	    TS_ASSERT_EQUALS(kernel(1,-1), 2.0);
	    
	    kn::ConvolutionKernel kernel2(2,2,-1,3);
	    TS_ASSERT_EQUALS(kernel2.xLowerBound(),1);
	    TS_ASSERT_EQUALS(kernel2.xUpperBound(),3);
	    TS_ASSERT_EQUALS(kernel2.yLowerBound(),-3);
	    TS_ASSERT_EQUALS(kernel2.yUpperBound(),-1);
    }
    
}; 


/*
 * End of Anti-doublon
 */
#endif

