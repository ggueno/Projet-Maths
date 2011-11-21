/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * ImageConvolution.hpp created in 10 2008.
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
#ifndef __OPENKN_IMAGE__IMAGECONVOLUTION_HPP__
#define __OPENKN_IMAGE__IMAGECONVOLUTION_HPP__


/*
 * External Includes
 */
#include <iostream>

/*
 * Internal Includes
 */
#include "Image.hpp"
#include "ImageProcessing.hpp"
#include "ConvolutionKernel.hpp"
#include "ConvolutionOperator.hpp"

/*
 * Namespace
 */
namespace kn{
	
 
		/*
		 * Class definition
		 */
 
		/** \brief Generic image convolution
		 *
		 */
		template<typename T> 
		class ImageConvolution : public ImageProcessing<T>{
			/*
			 * Constructor & destructors
			 */		 
		
		public:
			/** \brief Constructor to build a image convolution operator, with specified kernel and operator
			 * the operator IS NOT COPYIED
			 * \param kernel the specified kernel to use
			 * \param op the specified operator to use
			 */
			ImageConvolution(const ConvolutionKernel & kernel, const ConvolutionOperator & op);
			
			
			/** \brief Copy Constructor
			 *	\param e Error to clone
			 */
			ImageConvolution(const ImageConvolution & e);


			/** \brief dealoccates image convolution data
			 *
			 */
			~ImageConvolution();
			
		protected :
			/** \brief the kernel used by the convolution
			 */
			ConvolutionKernel kernel;
		
			/** \brief the operator used by the convolution
			 */
			ConvolutionOperator * op;
			
			/** \brief Convolution applied on image, and stocked in temporary array
			 *	\param img Image to convol
			 *	\param convo Temporary array for stocking the convolution
			 */
			void computeConvolution(const Image<T> & img, Image<T>& convo);
			
			
			
		public :
			/** \brief convolution applied on copy of image
			 *	\param img Image to convol
			 *	\param result resulting image, after convolution 
			 */
			void filterOnCopy(const Image<T> & img, Image<T> & result);
		
			/** \brief Convolution applied in place on image
			 *	\param img Image to convol
			 */
			void filter(Image<T> & img);
			 
			/** \brief getting the kernel used by the convolution
			 *	\return the kernel used by the convolution
			 */
			const ConvolutionKernel& getKernel() const;
			 
			
			/** \brief getting the operator used by the convolution
			 *	\return the operator used by the convolution
			 */
			const ConvolutionOperator& getOperator() const;

		};

		/*
		 * Templates definitions
		 */

		/*
		 * Functions definitions
		 */
		template<typename T>
		ImageConvolution<T>::ImageConvolution(const ConvolutionKernel & kernel,
											  const ConvolutionOperator& op) {
			this->kernel = kernel;
			this->op = op.clone();
		}

		template<typename T>
		ImageConvolution<T>::ImageConvolution(const ImageConvolution& e) {
			this->kernel = e.getKernel();
			this->op = e.getOperator().clone();
		}

		template<typename T>
		ImageConvolution<T>::~ImageConvolution() {
			delete op;
		}

		template<typename T>
		void ImageConvolution<T>::computeConvolution(const Image<T>& img, Image<T>& tmpImg){
			for(size_t j = 0; j < img.height(); j++){
				int yLow = kernel.yLowerBound();
				yLow = (yLow < -(int)j) ? -(int)j : yLow;
				int yUp = kernel.yUpperBound();
				yUp = (yUp > (int)img.height() - (int)j) ? (int)img.height() - (int)j : yUp;
				
				for(size_t i = 0; i < img.width(); i++){
					int xLow = kernel.xLowerBound();
					xLow = (xLow < -(int)i) ? -(int)i : xLow;
					int xUp = kernel.xUpperBound();
					xUp = (xUp > (int)img.width() - (int)i) ? (int)img.width() - (int)i : xUp;
					for(unsigned int d = 0; d < img.nbChannel(); d++) {
						op->initialize();
							
						for(int y = yLow; y < yUp; y++){
							for(int x = xLow; x < xUp; x++){
								try {
									(*op)(kernel(x,y), double(img(i+x, j+y)[d]));
								}
								catch(ImageException& /*ie*/){
									// This case can not append
								}
							}
						}
						tmpImg(i,j)[d] = (T) op->getResult();
					}
				}
			}
		}

 
		template<typename T>
		void ImageConvolution<T>::filter(Image<T>& img){
			Image<T> tmpImg(img.width(),img.height(),img.nbChannel());
			computeConvolution(img,tmpImg);
			std::copy(tmpImg.begin(), tmpImg.end(), img.begin());
		}


		template<typename T>
		void ImageConvolution<T>::filterOnCopy(const Image<T>& img, Image<T> & result){
			Image<T> tmpImg(img.width(),img.height(),img.nbChannel());
			computeConvolution(img,tmpImg);
			std::copy(tmpImg.begin(), tmpImg.end(), result.begin());
		}

		template<typename T>
		const ConvolutionKernel& ImageConvolution<T>::getKernel()const {
			return kernel;
		}

		template<typename T>
		const ConvolutionOperator& ImageConvolution<T>::getOperator()const {
			return *op;
		}

		/*
		 * Types definition
		 */
		typedef ImageConvolution<float> ImageConvolutionf;
		typedef ImageConvolution<double> ImageConvolutiond;
		typedef ImageConvolution<unsigned char> ImageConvolution8u;
		typedef ImageConvolution<unsigned short int> ImageConvolution16u;
		typedef ImageConvolution<unsigned int> ImageConvolution32u;
		typedef ImageConvolution<unsigned long int> ImageConvolution64u;
		typedef ImageConvolution<char> ImageConvolution8s;
		typedef ImageConvolution<short int> ImageConvolution16s;
		typedef ImageConvolution<int> ImageConvolution32s;
		typedef ImageConvolution<long int> ImageConvolution64s;





		/*
		 * End of Namespace
		 */
}
 
/*
 * End of Anti-doublon
 */
#endif

