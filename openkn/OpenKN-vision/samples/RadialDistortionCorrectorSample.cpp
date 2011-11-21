/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * CVtoGLSampleample.cpp created in 09 2011.
 * Mail : nozick@univ-mlv.fr
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
#include <cassert>

#include <OpenKN/image/ImageRGB.hpp>
#include <OpenKN/image/ioPPM.hpp>
#include <OpenKN/image/ioJPG.hpp>
#include <OpenKN/math/Vector.hpp>
#include <OpenKN/vision/RadialDistortionCorrector.hpp>

int main()
{
    // input images
    kn::ImageRGB8u imageDistorded;
   
    // load data
    kn::loadJPG(imageDistorded,"inputData/radialDistordedImage.jpg");
        
    // radial distortion parameters
    kn::Vector<double> center(2);
    center[0] = imageDistorded.width()/2.0;    
    center[1] = imageDistorded.height()/2.0;    
    double k = -3.0e-7;

    // radial distortion correction
    kn::ImageRGB8u imageCorrected(imageDistorded.width(),imageDistorded.height());
    radialDistortionCorrector(k,center,imageDistorded,imageCorrected);
    kn::savePPM(imageCorrected,"outputData/radialDistortionCorrected.ppm");

    kn::ImageRGB8u imageCorrectedScale(imageDistorded.width(),imageDistorded.height());
    imageCorrectedScale.fill(255);
    radialDistortionCorrector(k,center,imageDistorded,imageCorrectedScale,0.9);
    kn::savePPM(imageCorrectedScale,"outputData/radialDistortionCorrectedScale.ppm");

    return 0;
}

