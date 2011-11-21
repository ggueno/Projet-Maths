/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * LIN_V4L2Webcam_sample.cpp created in 09 2008.
 * Mail : biri@univ-mlv.fr                    
 *                                                     
 * This file is part of the OpenKraken-controller.
 *
 * The OpenKraken-controller is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-controller is distributed in the hope that it will be useful,
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
#include <cstdlib>

/*
 * Internal Includes
 */
#include <OpenKN/controller/LIN_V4L2Webcam.hpp>


bool savePPM(const char * const fn, 
	     const unsigned int& w, 
	     const unsigned int& h,
	     const unsigned char * data){
  FILE * f = fopen(fn, "w");
  if(f==NULL){
    fprintf(stderr,"Error in function readPPM : %s doesn't exist\n",fn);
    return false; 
  }
  fputs("P6\n",f);


  char tmpstr[64];
  sprintf(tmpstr,"%d %d\n",w,h);

  fputs(tmpstr,f);
  fputs("255\n",f);
  for(unsigned int i = 0; i < w*h*3; ++i){
    fputc(data[i],f);
  }

  return true;

}



int main(int argc, char** argv){

  // Define webcam parameters
    kn::V4L2WebcamParams V4L2defaultparamstest("/dev/video0",1600,1200);
    kn::V4L2Webcam webcam;
  try{


    webcam.openDevice(V4L2defaultparamstest);
    
    std::cout << "Webcam width : " << webcam.width() << std::endl;
    std::cout << "Webcam height : " << webcam.height() << std::endl;
    

    // Reset Brightness value
    std::cout << "Reset Brightness" << std::endl;
    webcam.resetControlValue(kn::WEBCAM_BRIGHTNESS);
    std::cout << "Set exposure to " << kn::WEBCAM_EXPOSURE_OFF << std::endl;
    webcam.toggleControlValue(kn::WEBCAM_EXPOSURE_AUTO,kn::WEBCAM_EXPOSURE_OFF);

    // Grab 10 images just for check
    for(int i = 0; i < 2; ++i){
      webcam.getImage();
    }

    // Set Brightness to 10
    std::cout << "Set brightness to ";
    webcam.setControlValue(kn::WEBCAM_BRIGHTNESS, 80);
    std::cout << webcam.getControlValue(kn::WEBCAM_BRIGHTNESS) << std::endl;
    
    savePPM("webcamcapture.ppm",webcam.width(),webcam.height(),webcam.getImage());

    webcam.resetControlValue(kn::WEBCAM_BRIGHTNESS);
	    
    webcam.closeDevice();

    sleep(2);

    std::cout << "New capture " << std::endl;

    kn::V4L2WebcamParams V4L2defaultparamstest2("/dev/video0",640,480);
    webcam.openDevice(V4L2defaultparamstest2);

    for(int i = 0; i < 10; ++i){
      webcam.getImage();
    }
    savePPM("webcamcapture2.ppm",webcam.width(),webcam.height(),webcam.getImage());
    webcam.closeDevice();

  }catch(kn::ControllerException e){
    std::cerr << e << std::endl;
    exit(0);
  }
  

  
  return 0;

}
