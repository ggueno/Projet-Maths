/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * ConvolutionMinOperatorTest.hpp created in 09 2008.
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
#ifndef __OPENKN_IMAGE__CONVOLUTIONMINOPERATORTEST_HPP__
#define __OPENKN_IMAGE__CONVOLUTIONMINOPERATORTEST_HPP__

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
#include <OpenKN/image/ConvolutionMinOperator.hpp>

/*
 * Class definition
 */

class ConvolutionMinOperatorTest : public CxxTest::TestSuite {
public:

   void testConstructors( void ) {
        kn::ConvolutionMinOperator op;
	op(1.0,1.0);
	op(1.0,2.0);
	op(1.0,3.0);
	
	kn::ConvolutionMinOperator op2 = op;

        TS_ASSERT_EQUALS(op.getResult(), op2.getResult());
        TS_ASSERT_EQUALS(op.getResult(),1.0);
   	
	op(1.0, -2.0);
	TS_ASSERT_DIFFERS(op.getResult(), op2.getResult());
	TS_ASSERT_EQUALS(op.getResult(), -2.0);
        
   }


    void testFuncterAndResult( void ) {
	 kn::ConvolutionMinOperator op;
	 op(1.0,3.0);
	 op(1.0,2.0);
	 op(1.0,1.0);
	 TS_ASSERT_EQUALS(op.getResult(),1.0);   
	 op.initialize();
	 op(1.0,3.0);
	 op(2.0,2.0);
	 op(0.0,1.0);
	 TS_ASSERT_EQUALS(op.getResult(),3.0);   
    }


    void testClone( void ) {
	kn::ConvolutionMinOperator av;
	av(1.0,1.0);
	av(1.0,2.0);
	av(1.0,3.0);
	kn::ConvolutionOperator* pop = &av;
	kn::ConvolutionOperator* pav = pop->clone();
	
	TS_ASSERT_EQUALS(av.getResult(), 1.0);
	TS_ASSERT_EQUALS(pop->getResult(), 1.0);
	TS_ASSERT_EQUALS(pav->getResult(), 1.0);
	TS_ASSERT_DIFFERS(pav, pop);
    }

    
    
}; 


/*
 * End of Anti-doublon
 */
#endif

