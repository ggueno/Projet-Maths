/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * ConvolutionMaxOperator.hpp created in 10 2008.
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
#ifndef __OPENKN_IMAGE__CONVOLUTIONMAXOPERATOR_HPP__
#define __OPENKN_IMAGE__CONVOLUTIONMAXOPERATOR_HPP__


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
		/** \brief convolution operator for Max
		 *
		 */
		class ConvolutionMaxOperator : public ConvolutionOperator {
		public:
			/*
			 * Constructor & destructors
			 */
			/** \brief Default constructor
			 *
			 */
			inline ConvolutionMaxOperator(){
				initialize();
			}
			
			/** \brief Constructor by copy
			 *
			 */
			inline ConvolutionMaxOperator(const ConvolutionMaxOperator& e) : ConvolutionOperator(e){
				max = e.max;
				kernelSum = e.kernelSum;
			}
			/** \brief Destructor
			 *
			 */
			inline ~ConvolutionMaxOperator(){}

		protected:
			double max;		
			double kernelSum; 


		public:
			/** \brief Reinitialize the operator
			 *
			 */
			inline void initialize(){
				max = std::numeric_limits<double>::min(); 
				kernelSum = 0.0;
			}
			
			/** \brief Getting the result of the operation
			 *	\return the result of the operation
			 *	\throw ImageException kernel sum null
			 */
			inline double getResult() {
				if(kernelSum == 0)
					throw ImageException("kernel sum null");
				return max;
			}

			/** \brief Insert the computation of a new point of the kernel
			 *	\param kernelValue the value of the kernel point
			 *	\param imageValue the value of the corresponding image point
			 */
			inline void operator()(double kernelValue, double imageValue){
				max = std::max(max, imageValue*kernelValue);
				kernelSum+=kernelValue;
			}
		
			/** \brief Virtual constructor by copy
			 *	\return a pointer on a new instance of the ConvolutionMaxOperator constructed by copy
			 */
			inline ConvolutionMaxOperator* clone() const{
				return new ConvolutionMaxOperator(*this);
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

