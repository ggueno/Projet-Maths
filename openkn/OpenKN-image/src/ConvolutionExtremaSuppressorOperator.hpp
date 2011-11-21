/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * ConvolutionExtremaSuppressorOperator.hpp created in 10 2008.
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
#ifndef __OPENKN_IMAGE__CONVOLUTIONEXTREMASUPPRESSOROPERATOR_HPP__
#define __OPENKN_IMAGE__CONVOLUTIONEXTREMASUPPRESSOROPERATOR_HPP__


/*
 * External Includes
 */
#include<limits>

/*
 * Internal Includes
 */
#include "ImageException.hpp"
#include "ConvolutionOperator.hpp"

/*
 * Namespace
 */
namespace kn{
		/*
		 * Class definition
		 */
		/** \brief convolution operator for ExtremaSuppressor
		 *
		 */
		class ConvolutionExtremaSuppressorOperator : public ConvolutionOperator {
		public:
			/*
			 * Constructor & destructors
			 */
			/** \brief Default constructor
			 *
			 */
			inline ConvolutionExtremaSuppressorOperator(){
				initialize();
			}
			
			/** \brief Constructor by copy
			 *
			 */
			inline ConvolutionExtremaSuppressorOperator(const ConvolutionExtremaSuppressorOperator& e) : ConvolutionOperator(e){
				max = e.max;
				min = e.min;
				val = e.val;
			}
			/** \brief Destructor
			 *
			 */
			inline ~ConvolutionExtremaSuppressorOperator(){}

		protected:
			double min;
			double max;
			double val;


		public:
			/** \brief Reinitialize the operator
			 *
			 */
			inline void initialize(){
				max = std::numeric_limits<double>::min(); 
				min = std::numeric_limits<double>::max(); 
				val = -1;
			}
			
			/** \brief Getting the result of the operation
			 *	\return the result of the operation
			 *	\throw ImageException kernel sum null
			 */
			inline double getResult() {
				if(val==-1)
					throw ImageException("kernel bad initialization");
				return val<min?min:val>max?max:val;
			}

			/** \brief Insert the computation of a new point of the kernel
			 *	\param kernelValue the value of the kernel point
			 *	\param imageValue the value of the corresponding image point
			 */
			inline void operator()(double kernelValue, double imageValue){
				if(kernelValue == 0.0){
					max = std::max(max, imageValue);
					min = std::min(min, imageValue);
				}else if(kernelValue == 1.0){
					val=imageValue;
				}
			}
		
			/** \brief Virtual constructor by copy
			 *	\return a pointer on a new instance of the ConvolutionExtremaSuppressorOperator constructed by copy
			 */
			inline ConvolutionExtremaSuppressorOperator* clone() const{
				return new ConvolutionExtremaSuppressorOperator(*this);
			}
		};

		/*
		 * End of Namespace
		 */
}

/*
 * End of Anti-doublon
 */
#endif

