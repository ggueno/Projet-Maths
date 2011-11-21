/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * ConvolutionOperator.hpp created in 10 2008.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_IMAGE__CONVOLUTIONOPERATOR_HPP__
#define __OPENKN_IMAGE__CONVOLUTIONOPERATOR_HPP__


/*
 * External Includes
 */


/*
 * Internal Includes
 */

/*
 * Namespace
 */
namespace kn{
		/*
		 * Class definition
		 */
	
		/** \brief Interface for convolution operator
		 *
		 */
		class ConvolutionOperator{ 

			/*
			 * Constructor & destructors
			 */
		public:

			/** \brief Virtual destructor
			 *
			 */
			virtual ~ConvolutionOperator(){}


			/** \brief Reinitialize the operator
			 *
			 */
			virtual void initialize()=0;

			/** \brief Getting the result of the operation
			 *	\return the result of the operation
			 */
			virtual double getResult()=0;

			/** \brief Insert the computation of a new point of the kernel
			 *	\param kernelValue the value of the kernel point
			 *	\param imageValue the value of the corresponding image point
			 */
			virtual void operator()(double kernelValue, double imageValue)=0;

			/** \brief Virtual constructor by copy
			 *  \return a pointer on a new instance of the ConvolutionOperator constructed by copy
			 */
			virtual ConvolutionOperator* clone() const = 0;

		};
	
	
	

		/*
		 * End of Namespace
		 */
}

/*
 * End of Anti-doublon
 */
#endif

