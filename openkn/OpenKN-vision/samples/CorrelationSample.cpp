/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * Correlation.cpp created in 01 2010.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-vision.
 *
 * The OpenKraken-vision is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-vision is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/


#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>

#include <OpenKN/image/ImageGS.hpp>
#include <OpenKN/image/ImageRGB.hpp>
#include <OpenKN/image/ioJPG.hpp>
#include <OpenKN/image/ioPPM.hpp>
#include <OpenKN/math/Vector3.hpp>
#include <OpenKN/math/Vector2.hpp>
#include <OpenKN/vision/CrossCorrelation.hpp>
#include <OpenKN/vision/Harris.hpp>

static const std::string imgname[2]	={"inputData/imageCorrel0.ppm","inputData/imageCorrel1.ppm"};
static const std::string output[2]	={"outputData/imageCorrel0.ppm","outputData/imageCorrel1.ppm"};

/*
 * Convert an RGB image to GrayScale using luminance
 */
kn::ImageGS<unsigned char> RGBtoGS(const kn::ImageRGB<unsigned char> &image){
  kn::ImageGS<unsigned char> result(image.width(),image.height());
  for(unsigned int i=0;i<image.width();i++){
    for(unsigned int j=0;j<image.height();j++){
      result.at(i,j)=  0.299 * image.at(i,j,0) + 0.587 * image.at(i,j,1) + 0.114* image.at(i,j,2) ;
    }
  }
  return result;
}

int main(int argc, char ** argv){

  //harris point on 2 related images
  std::vector< kn::Vector3d > list1,list2;
  //load image rgb
  kn::ImageRGB<unsigned char> input1,input2;
//  kn::loadJPG(input1,imgname[0]);
//  kn::loadJPG(input2,imgname[1]);
  kn::loadPPM(input1,imgname[0]);
  kn::loadPPM(input2,imgname[1]);

  //convert to gs and compute harris
  kn::ImageGS<unsigned char> inputGS1 = RGBtoGS(input1);
  list1 = harris(inputGS1,200);
  kn::ImageGS<unsigned char> inputGS2 = RGBtoGS(input2);
  list2 = harris(inputGS2,200);
  std::cout<<"Interest points found on image 1 : "<<list1.size()<<std::endl;
  std::cout<<"Interest points found on image 2 : "<<list2.size()<<std::endl;
  std::cout<<"Number of correlation to compute : "<<list1.size()*list2.size()<<std::endl;

  //correlation
  //std::vector< std::pair<kn::Vector3d, kn::Vector3d> > match = crossCorrelation(inputGS1,list1,inputGS2,list2,11,0.95,1);//GS
  kn::Vector2i windowSize;
  windowSize[0] = windowSize[1] = 11;
  std::vector< std::pair<kn::Vector3d, kn::Vector3d> > match = crossCorrelation(input1,list1,input2,list2,windowSize,.95,3);//Color
  std::cout<<"Matching point found : "<<match.size()<<std::endl;

  //save image with point
  //first half all image component value
    for(unsigned int w=0;w<input1.width();w++){
      for(unsigned int h=0;h<input1.height();h++){
	for(unsigned int k=0;k<input1.nbChannel();k++){
	  input1.at(w,h,k) = input1.at(w,h,k)/3;
	  input2.at(w,h,k) = input2.at(w,h,k)/3;
	}
      }
    }

    //Put red dot for each interest point
    for(unsigned int nbpt=0;nbpt<match.size();nbpt++){
      input1.at(match.at(nbpt).first.x(),match.at(nbpt).first.y(),0) = 255;
      input1.at(match.at(nbpt).first.x(),match.at(nbpt).first.y(),1) = 0;
      input1.at(match.at(nbpt).first.x(),match.at(nbpt).first.y(),2) = 0;

      input2.at(match.at(nbpt).second.x(),match.at(nbpt).second.y(),0) = 255;
      input2.at(match.at(nbpt).second.x(),match.at(nbpt).second.y(),1) = 0;
      input2.at(match.at(nbpt).second.x(),match.at(nbpt).second.y(),2) = 0;
    }
    savePPM(input1,output[0]);
    savePPM(input2,output[1]);
  return 0;
}


