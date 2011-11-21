/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * ConvolutionAverageOperator.hpp created in 10 2008.
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
#ifndef __OPENKN_IMAGE__CONVOLUTIONAVERAGEOPERATOR_HPP__
#define __OPENKN_IMAGE__CONVOLUTIONAVERAGEOPERATOR_HPP__


/*
 * External Includes
 */


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
		/** \brief convolution operator for average
		 *
		 */
		class ConvolutionAverageOperator : public ConvolutionOperator {
		public:
			/*
			 * Constructor & destructors
			 */
			/** \brief Default constructor
			 *
			 */
			inline ConvolutionAverageOperator(){
				sum = 0.0;
				kernelSum = 0.0;
			}

			/** \brief Constructor by copy
			 *
			 */
			inline ConvolutionAverageOperator(const ConvolutionAverageOperator& e) : ConvolutionOperator(e){
				sum = e.sum;
				kernelSum = e.kernelSum;
			}
			/** \brief Destructor
			 *
			 */
			inline ~ConvolutionAverageOperator(){}

		protected:
			double sum;					///< sum of the computed values
			double kernelSum;		///< sum of the kernel values



		public:
			/** \brief Reinitialize the operator
			 *
			 */
			inline void initialize(){
				sum = 0.0;
				kernelSum = 0.0;
			}
			
			/** \brief Getting the result of the operation
			 *	\return the result of the operation
			 *	\throw ImageException kernel sum null
			 */
			inline double getResult() {
				if(kernelSum == 0)
					throw ImageException("kernel sum null");
				return sum/kernelSum;
			}

			/** \brief Insert the computation of a new point of the kernel
			 *	\param kernelValue the value of the kernel point
			 *	\param imageValue the value of the corresponding image point
			 */
			inline void operator()(double kernelValue, double imageValue){
				sum+=kernelValue*imageValue;
				kernelSum+=kernelValue;
			}
		
			/** \brief Virtual constructor by copy
			 *	\return a pointer on a new instance of the ConvolutionAverageOperator constructed by copy
			 */
			inline ConvolutionAverageOperator* clone() const{
				return new ConvolutionAverageOperator(*this);
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

