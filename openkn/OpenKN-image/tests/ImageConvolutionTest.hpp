/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * ImageconvolutionTest.hpp created in 09 2008.
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
#ifndef __OPENKN_IMAGE__IMAGECONVOLUTIONTEST_HPP__
#define __OPENKN_IMAGE__IMAGECONVOLUTIONTEST_HPP__

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
#include <OpenKN/image/ConvolutionAverageOperator.hpp>
#include <OpenKN/image/ImageConvolution.hpp>
#include <OpenKN/image/ImageGS.hpp>

/*
 * Class definition
 */
class ImageConvolutionTest : public CxxTest::TestSuite {
public:
	void testConstructors( void ) {
		kn::ConvolutionKernel kernel(2,2,0,0);
		kn::ConvolutionOperator* op = new kn::ConvolutionAverageOperator();
		kn::ImageConvolution8u  convo(kernel, *op);
	
		kn::ImageConvolution8u  convo2 = convo;
		TS_ASSERT_DIFFERS(&(convo.getOperator()), op);
		TS_ASSERT_DIFFERS(&(convo.getOperator()), &(convo2.getOperator()));
		delete op;
	}



 

	void testFilterInPlace(void) {
		unsigned char static_buffer[] = {20,20,20,20,
										 30,10,10,30,
										 30,10,10,30,
										 20,20,20,20};
		unsigned char * dyn_buffer = new unsigned char[16];
		memcpy(dyn_buffer,static_buffer,16*sizeof(char));
		kn::ImageGS8u i(4,4,dyn_buffer);
		kn::ConvolutionKernel kernel(2,2,0,0);
		kn::ConvolutionOperator* op = new kn::ConvolutionAverageOperator();
		kn::ImageConvolution8u  convo(kernel, *op);
		convo.filter(i);
		TS_ASSERT_EQUALS(i(0,0), 20);
		TS_ASSERT_EQUALS(i(3,0), 25);
		TS_ASSERT_EQUALS(i(0,3), 20);
		TS_ASSERT_EQUALS(i(3,3), 20);
		TS_ASSERT_EQUALS(i(1,2), 15); 
	}



	void testFilter(void) {
		unsigned char static_buffer[] = {20,20,20,20,
										 30,10,10,30,
										 30,10,10,30,
										 20,20,20,20};
		unsigned char * dyn_buffer = new unsigned char[16];
		memcpy(dyn_buffer,static_buffer,16*sizeof(char));
		kn::ImageGS8u i(4,4,dyn_buffer);
		kn::ImageGS8u res(4,4);
		kn::ConvolutionKernel kernel(2,2,0,0);
		kn::ConvolutionOperator* op = new kn::ConvolutionAverageOperator();
		kn::ImageConvolution8u  convo(kernel, *op);
	
	
		convo.filterOnCopy(i,res);
		TS_ASSERT_EQUALS(res.width(), i.width());
		TS_ASSERT_EQUALS(res.height(), i.width());
		TS_ASSERT_EQUALS(res.nbChannel(), i.nbChannel());
		
		TS_ASSERT_EQUALS(res(0,0), 20);
		TS_ASSERT_EQUALS(res(3,0), 25);
		TS_ASSERT_EQUALS(res(0,3), 20);
		TS_ASSERT_EQUALS(res(3,3), 20);
		TS_ASSERT_EQUALS(res(1,2), 15);
		
		TS_ASSERT_DIFFERS(res(3,0),i(3,0));
		TS_ASSERT_DIFFERS(res(1,2), i(1,2)); 
	}

};


/*
 * End of Anti-doublon
 */
#endif

