/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * LIN_image_computing_sample.cpp created in 01 2009.
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
 * External Includes
 */
#include <iostream>
#include <string>
#include <OpenKN/image/Image.hpp>
#include <OpenKN/image/ioPPM.hpp>
#include <OpenKN/image/ioTGA.hpp>
#include <OpenKN/image/ioJPG.hpp>
#include <OpenKN/image/Canny.hpp>
#include <OpenKN/image/ImageConvolution.hpp>
#include <OpenKN/image/ConvolutionAverageOperator.hpp>
#include <OpenKN/image/ConvolutionKernel.hpp>
//#include <cstdlib>

/*
 * Internal Includes
 */

using namespace kn;

class ConvolutionMaxOperator : public ConvolutionOperator {
	public:
		inline ConvolutionMaxOperator(){
			max = -1.0;
		}
		inline ConvolutionMaxOperator(const ConvolutionMaxOperator& e) : ConvolutionOperator(e){
			max = e.max;
		}
		inline ~ConvolutionMaxOperator(){}

	protected:
		double max;					//  max of the computed values

	public:
		inline void initialize(){
			max = -1.0;
		}

		inline double getResult() {
			if(max == -1.0)
				throw ImageException("max could not be computed");
			return max;
		}

		/** \brief Insert the computation of a new point of the kernel
			*	\param kernelValue the value of the kernel point
			*	\param imageValue the value of the corresponding image point
			*/
		inline void operator()(double kernelValue, double imageValue){
			double val = kernelValue*imageValue;
			if (val > max) max = val;
		}

		inline ConvolutionMaxOperator* clone() const{
			return new ConvolutionMaxOperator(*this);
		}
};



/// This sample tests loading and saving ppm and simple image transformation
/// This sample shows how to load image, transform it, and save it
int main(int argc, char** argv) {
	int checker_file;
	bool save_ok;
	
	// ============= PART 1 : Loading a PPM file, blur it and save it
	try {
		// Loading IMAGE using loader framework
		Image<unsigned char> my_image;
		checker_file = kn::loadPPM(my_image,"./ImageComputingData/Jackson_Pollock-Convergence.ppm");
		if (checker_file != 3) {
			std::cerr<<"ERROR in reading PPM file. Number of components must be 3 but we found "<<checker_file<<std::endl;
		}

		// Convolution creation
		// The first argument define the mask of the kernel. The second one is the way you combine
		// the different elements of the kernel (associated with pixel of the original image) to
		// compute the final pixel (in the final image)
		ImageConvolution<unsigned char> *my_convol
			= new ImageConvolution<unsigned char>(ConvolutionKernel(),ConvolutionAverageOperator());

		// Do the convolution
		my_convol->filter(my_image);

		save_ok = kn::savePPM(my_image,"./ImageComputingData/export.ppm");
		if (!save_ok) {
			std::cerr<<"Saving have been impossible ! This should not append"<<std::endl;
		}

		delete(my_convol);

		// ============= PART 1 : Loading a TGA file, pixelize it and save it

		Image<unsigned char> my_image_2;

		checker_file = kn::loadTGA(my_image_2,"./ImageComputingData/Jackson_Pollock-Convergence.tga");
		if (checker_file != kn::COLOR_TGA) {
			std::cerr<<"ERROR in reading tga file. Type must be COLOR_TGA"<<std::endl;
		}

		my_convol = new ImageConvolution<unsigned char>(ConvolutionKernel(7,7,3,3),ConvolutionMaxOperator());
		// Do the convolution
		my_convol->filter(my_image);

		save_ok = kn::savePPM(my_image,"./ImageComputingData/export_2.ppm");
		if (!save_ok) {
			std::cerr<<"Saving have been impossible ! This should not append"<<std::endl;
		}

		delete(my_convol);
	


		// ============= PART 1 : Loading a JPG file, apply edge extraction by canny and save it

			Image<unsigned char> my_image_3;

			checker_file = kn::loadJPG(my_image_3,"./ImageComputingData/shanghai.jpg");

			ImageGS8u gs(my_image_3.width(), my_image_3.height());
			for(int j = 0; j<my_image_3.height();j++){
				for(int i = 0; i < my_image_3.width();i++){
					int val=0;
					for(int d = 0; d < my_image_3.nbChannel(); d++){
						val+=my_image_3(i,j,d);
					}
					gs(i,j) = val/my_image_3.nbChannel();
				}
			}
			ImageGS8u gsres(my_image_3.width(), my_image_3.height());
			my_convol= new ImageConvolution<unsigned char>(ConvolutionKernel(),ConvolutionAverageOperator());

			// Do the convolution
			my_convol->filter(gs);

			kn::canny(gs, gsres, 50, 150);
			save_ok = kn::savePPM(gsres,"./ImageComputingData/export_3.ppm");
			if (!save_ok) {
				std::cerr<<"Saving have been impossible ! This should not append"<<std::endl;
			}
			delete(my_convol);
	
		
	}
	catch (ImageException e) {
		std::cerr<<"There has been a Image Error : "<<std::endl<<e.errorString()<<std::endl;
	}

	// Definition of a new ConvolutionOperator ...
	return 0;
}
