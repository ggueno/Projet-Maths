/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * HarrisSample.cpp created in 04 2009.
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
#include <string>

#include <OpenKN/image/ImageGS.hpp>
#include <OpenKN/image/ImageRGB.hpp>
#include <OpenKN/image/ioJPG.hpp>
#include <OpenKN/image/ioPPM.hpp>
#include <OpenKN/math/Vector3.hpp>
#include <OpenKN/vision/Harris.hpp>

static const std::string imgname[5]	={"inputData/maid0.jpg","inputData/maid1.jpg","inputData/maid2.jpg","inputData/imageHarris3.ppm","inputData/imageHarris4.ppm"};
static const std::string output[5]	={"outputData/imageHarris0.ppm","outputData/imageHarris1.ppm","outputData/imageHarris2.ppm","outputData/imageHarris3.ppm","outputData/imageHarris4.ppm"};
#ifdef DEBUG
static const std::string listname[5]	={"outputData/listHarris0.list","outputData/listHarris1.list","outputData/listHarris2.list","outputData/listHarris3.list","outputData/listHarris4.list"};
static const std::string outputgs[5]	={"outputData/imageHarrisgs0.ppm","outputData/imageHarrisgs1.ppm","outputData/imageHarrisgs2.ppm","outputData/imageHarrisgs3.ppm","outputData/imageHarrisgs4.ppm"};
#endif

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
  //Compute harris on 3 related images
  for(unsigned int i=0;i<5;i++){
    std::vector< kn::Vector3d >harrisPt;
    //load image rgb
    kn::ImageRGB<unsigned char> input;
    if(i>=3)kn::loadPPM(input,imgname[i]);
    else kn::loadJPG(input,imgname[i]);
    //convert to gs and save
    kn::ImageGS<unsigned char> inputGS = RGBtoGS(input);
#ifdef DEBUG
    kn::savePPM(inputGS,outputgs[i]);
#endif
    //apply Harris Homogeneous
    harrisPt = harris(inputGS);
#ifdef DEBUG
    //save point list
    std::ofstream pointFile(listname[i].c_str());
    if(!pointFile.is_open()){
      std::cerr<<"error opening file : "<<listname[i];
    }else{
      for(unsigned int nbpt=0;nbpt<harrisPt.size();nbpt++){
	pointFile<<harrisPt.at(nbpt)<<std::endl;
      }
      pointFile.close();
    }
#endif

    //save image with point
    //first half all image component value
    for(unsigned int w=0;w<input.width();w++){
      for(unsigned int h=0;h<input.height();h++){
	for(unsigned int k=0;k<input.nbChannel();k++){
	  input.at(w,h,k) = input.at(w,h,k)/3;
	}
      }
    }
    std::cout<<"Harris point for image \""<<imgname[i]<<"\" : "<<harrisPt.size()<<std::endl;
    //Put red dot for each interest point
    for(unsigned int nbpt=0;nbpt<harrisPt.size();nbpt++){
      input.at(harrisPt.at(nbpt).x(),harrisPt.at(nbpt).y(),0) = 255;
      input.at(harrisPt.at(nbpt).x(),harrisPt.at(nbpt).y(),1) = 0;
      input.at(harrisPt.at(nbpt).x(),harrisPt.at(nbpt).y(),2) = 0;
    }
    savePPM(input,output[i]);
  }
  return 0;
}

