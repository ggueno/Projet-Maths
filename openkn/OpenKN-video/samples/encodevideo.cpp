/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * encodevideo.cpp created in 08 2009.
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
#include <cstring>
#include <cstdlib>

/*
 * Internal Includes
 */
#include <OpenKN/video/VideoStream.hpp>
#include <OpenKN/video/VideoException.hpp>



int main( int argc, char ** argv){

    int w = 640,h=480;
    int nb = 100;
    unsigned char ** img = new unsigned char* [nb];
    for(int i = 0;i < nb; ++i){
        img[i] = new unsigned char [w*h*3];
        if(i%3==0)
            memset(img[i],255,w*h*3*sizeof(unsigned char));
        else
            if(i%2==0)
                memset(img[i],0,w*h*3*sizeof(unsigned char));
            else
                memset(img[i],128,w*h*3*sizeof(unsigned char));
                
            
    }

    VideoStream::encode("test.mpeg",img,nb,w,h);

    return 0;
}
