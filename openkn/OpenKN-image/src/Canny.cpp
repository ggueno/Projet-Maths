/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * Canny.cpp created in 03 2009.
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

#include <cmath>
#include <queue>
/*
 * Internal Includes
 */
#include "Canny.hpp"


/*
 * Namespace
 */
namespace kn{

    
	void canny(kn::ImageGS8u &inputImage, kn::ImageGS8u &outputImage, unsigned int lowerThres, unsigned int upperThres){

		//Compute norme and direction of gradient
		char kernelGradientX[9] = {1,0,-1,2,0,-2,1,0,-1};//kernel for gradient in X
		char kernelGradientY[9] = {1,2,1,0,0,0,-1,-2,-1};//kernel for gradient in Y 
		ImageGSf direction(inputImage.width(),inputImage.height());//map of gradient direction
		ImageGS8u  norme(inputImage.width(),inputImage.height());//map of gradient norme (sobel)
		
		for(unsigned int j = 1; j < inputImage.height()-1; j++){
			for(unsigned int i = 1; i < inputImage.width()-1; i++){
				//convolution for both x gradient and y gradient
				int gradientX = 0;
				int gradientY = 0;
				for(int dy = -1; dy < 2; dy++){
					for(int dx = -1; dx < 2; dx++){
						gradientX+=inputImage(i+dx, j+dy)*kernelGradientX[(1+dx)+(1+dy)*3];
						gradientY+=inputImage(i+dx, j+dy)*kernelGradientY[(1+dx)+(1+dy)*3];
					}
				}
				//computation of norme of gradient
				norme(i,j) = std::sqrt(gradientX*gradientX+gradientY*gradientY);
				//computation of direction of gradient
				direction(i,j) = std::atan2(gradientY,gradientX);
				//restrict the direction of gradient between 0 and PI
				if(direction(i,j) < 0)direction(i,j)+=M_PI; 
			}
		}
		
		//bouding angles for changing masks of maxima detection
		double part0 = M_PI/8;
		double part1 = 3*M_PI/8;
		double part2 = 5*M_PI/8;
		double part3 = 7*M_PI/8;

		//Computation of gradient norme local maxima in regard of gradient direction
		for(unsigned int j = 0; j < inputImage.height(); j++){
			for(unsigned int i = 0; i < inputImage.width(); i++){
				if(j == 0 || i == 0 || j == inputImage.height()-1 || i == inputImage.width()-1 || norme(i,j)<=lowerThres){
					outputImage(i,j) = 0;
					continue;
				}
				if(direction(i,j) > part3 || direction(i,j) < part0){
					if(norme(i,j)>norme(i-1,j) && norme(i,j)>norme(i+1,j))
						outputImage(i,j) = norme(i,j);
					else 
						outputImage(i,j) = 0;
				}else if(direction(i,j) > part2){
					if(norme(i,j)>norme(i-1,j+1) && norme(i,j)>norme(i+1,j-1))
						outputImage(i,j) = norme(i,j);
					else 
						outputImage(i,j) = 0;
				}else if(direction(i,j) > part1){
					if(norme(i,j)>norme(i,j+1) && norme(i,j)>norme(i,j-1))
						outputImage(i,j) = norme(i,j);
					else 
						outputImage(i,j) = 0;
				} else{
					if(norme(i,j)>norme(i+1,j+1) && norme(i,j)>norme(i-1,j-1))
						outputImage(i,j) = norme(i,j);
					else 
						outputImage(i,j) = 0;
				}
			}
		}

		//Hysteresis by flooding
		for(unsigned int j = 1; j < inputImage.height()-1; j++){
			for(unsigned int i = 1; i < inputImage.width()-1; i++){
				if(outputImage(i,j) >= upperThres){
					std::queue<unsigned int> fifo;
					fifo.push(i+j*inputImage.width());
					while(!fifo.empty()){
						unsigned int ind = fifo.front();
						fifo.pop();
						unsigned int x = ind%inputImage.width();
						unsigned int y = ind/inputImage.width();
						for(int dy = -1; dy < 2; dy++){
							for(int dx = -1; dx < 2; dx++){
								if(outputImage(x+dx,y+dy) > lowerThres && outputImage(x+dx,y+dy) < upperThres){
									outputImage(x+dx,y+dy) = upperThres;
									fifo.push(x+dx+(y+dy)*inputImage.width());
								}
							}
						}
					}
				}
			}
		}
		for(unsigned int j = 1; j < inputImage.height()-1; j++){
			for(unsigned int i = 1; i < inputImage.width()-1; i++){
				if(outputImage(i,j) >= upperThres)
					outputImage(i,j) = 255;
				else 
					outputImage(i,j) = 0;
			}
		}
	}

    /*
     * End of Namespace
     */
}


