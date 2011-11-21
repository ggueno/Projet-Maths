/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * decodevideo.cpp created in 08 2009.
 * Mail : biri@univ-mlv.fr					  
 *													   
 * This file is part of the OpenKraken-video.
 *
 * The OpenKraken-video is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-video is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
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
#include <OpenKN/video/VideoStream.hpp>
#include <OpenKN/video/VideoException.hpp>
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


int main( int argc, char ** argv){
	try{
		VideoStream vs1(std::string("test.avi"));
		bool first = true;
		while(!vs1.getEndOfStreamStatus()){
			unsigned char * tmp = vs1.getFrame();
			if(tmp){
				if(first){
					savePPM("picture-test.ppm", vs1.getWidth(), vs1.getHeight(), tmp);
					first = false;
				}
			}// else it means frame is still being decoded
		}
		
		vs1.goToFrameId(0); 
		while(!vs1.getEndOfStreamStatus()){
			unsigned char * tmp = vs1.getFrame();
            if(tmp)
                std::cout << vs1.getCurrentFrameId() << " / " << vs1.getNumberOfFrame() << std::endl;
		}
		
	}catch(kn::VideoException e){
		std::cerr << e << std::endl;
	}

	return 0;
}
