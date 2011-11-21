/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * ConvolutionKernel.cpp created in 10 2008.
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


#include <iostream>
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma warning(disable:4996)
#endif
/*
 * Internal Includes
 */
#include "ConvolutionKernel.hpp"

/*
 * Namespace
 */
namespace kn{
		/*
		 * Functions definitions
		 */
		ConvolutionKernel::ConvolutionKernel(){
			_width = 3;
			_height = 3;
			_xOrigin = 1;
			_yOrigin = 1;
			_values = new double[9];
			std::fill(_values,_values+_width*_height, 1.0);
		}
	
		ConvolutionKernel::ConvolutionKernel(unsigned int width, unsigned int height,
											 unsigned int xOrigin, unsigned int yOrigin,
											 double* values) {
			_width = width;
			_height = height;
			_xOrigin = xOrigin;
			_yOrigin = yOrigin;
			if(values != NULL){
				_values = new double[_width*_height];
				std::copy(values,values+_width*_height,_values);
			}
			else{
				unsigned int size = width * height;
				_values = new double[size];
				std::fill(_values,_values+size, 1.0);
				
			}
		}
	  
		ConvolutionKernel::ConvolutionKernel(const ConvolutionKernel & e){
			_width = e.width();
			_height = e.height();
			_xOrigin = e.xOrigin();
			_yOrigin = e.yOrigin();
			_values = new double[_width*_height];
			std::copy(e.values(),e.values()+_width*_height,_values);
			
		}


		ConvolutionKernel::~ConvolutionKernel(){
			delete[] _values;
		}
	
		double ConvolutionKernel::operator()(int x, int y) const {
			if( (x < xLowerBound()) || (x >= xUpperBound()) ||
				(y < yLowerBound()) || (y >= yUpperBound()) )
				throw ImageException("coordinates out of bounds");
			return _values[x+_xOrigin+(y+_yOrigin)*_width];
		}
	
	
		ConvolutionKernel& ConvolutionKernel::operator=(const ConvolutionKernel& k) {
			if(&k == this) return *this;
			if(_width*_height != k.width()*k.height()){
				delete[] _values;
				_values = new double[k.width()*k.height()];
			}
			_width = k.width();
			_height = k.height();
			_xOrigin = k.xOrigin();
			_yOrigin = k.yOrigin();
			std::copy(k.values(),k.values()+_width*_height,_values);
			return *this;
		}

		/*
		 * End of Namespace
		 */
}
