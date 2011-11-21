/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * ConvolutionAbsoluteSumOperator.hpp created in 10 2008.
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
#ifndef __OPENKN_IMAGE__CONVOLUTION_ABSOLUTE_SUM_OPERATOR_HPP__
#define __OPENKN_IMAGE__CONVOLUTION_ABSOLUTE_SUM_OPERATOR_HPP__


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
		/** \brief convolution operator for absolute sum
		 *
		 */
		class ConvolutionAbsoluteSumOperator : public ConvolutionOperator {
		public:
			/*
			 * Constructor & destructors
			 */
			/** \brief Default constructor
			 *
			 */
			inline ConvolutionAbsoluteSumOperator(){
				sum = 0.0;
			}

			/** \brief Constructor by copy
			 *
			 */
			inline ConvolutionAbsoluteSumOperator(const ConvolutionAbsoluteSumOperator& e) : ConvolutionOperator(e){
				sum = e.sum;
			}
			/** \brief Destructor
			 *
			 */
			inline ~ConvolutionAbsoluteSumOperator(){}

		protected:
			double sum;			///< sum of the computed values

		public:
			/** \brief Reinitialize the operator
			 *
			 */
			inline void initialize(){
				sum = 0.0;
			}

			/** \brief Getting the result of the operation
			 *	\return the result of the operation
			 */
			inline double getResult() {
			  if(sum<0.0)return sum;
			  else return -sum;
			  return sum;
			}

			/** \brief Insert the computation of a new point of the kernel
			 *	\param kernelValue the value of the kernel point
			 *	\param imageValue the value of the corresponding image point
			 */
			inline void operator()(double kernelValue, double imageValue){
				sum+=kernelValue*imageValue;
			}

			/** \brief Virtual constructor by copy
			 *	\return a pointer on a new instance of the ConvolutionAbsoluteSumOperator constructed by copy
			 */
			inline ConvolutionAbsoluteSumOperator* clone() const{
				return new ConvolutionAbsoluteSumOperator(*this);
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

