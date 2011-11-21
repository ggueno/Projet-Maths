/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * RadialDistortionCorrector.cpp created in 09 2011.
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/


/*
 * Internal Includes
 */
#include "RadialDistortionCorrector.hpp"
#include "Homography.hpp"
#include "VisionException.hpp"
#include<OpenKN/math/Vector.hpp>

/*
 * Namespace
 */
namespace kn{

// Computes the corrected pixel position of an input distorded pixel position.
void radialDistortionCorrector(const double &k,
                               const kn::Vector<double> &center,
                               double &iCorrected, double &jCorrected, 
                               const double &iDistorded, const double &jDistorded)
{
    double radius_i = iDistorded - center[0];
    double radius_j = jDistorded - center[1];
    double r2 = radius_i*radius_i + radius_j*radius_j; // squared radius
    
    iCorrected = center[0] + (iDistorded - center[0]) / (1.0 + k*r2);
    jCorrected = center[1] + (jDistorded - center[1]) / (1.0 + k*r2);
}



// Computes the corrected pixel position of an input distorded pixel position.
void radialDistortionCorrector(const double &k,
                               const kn::Vector<double> &center,
                               kn::Vector<double> &correctedPoint, 
                               const kn::Vector<double> &distordedPoint)
{
    // compute the corrected pixel position
    radialDistortionCorrector(k,center,correctedPoint[0],correctedPoint[1],distordedPoint[0],distordedPoint[1]);
    
    // homogeneous coordinates
    if(correctedPoint.size()>2) correctedPoint[2] = 1.0;
}



/// Apply the radial distortion of in input image, with anti-aliasing.
void radialDistortionCorrector(const double &k,
                               const kn::Vector<double> &center,
                               const kn::ImageRGB8u & distordedImage,
			                   kn::ImageRGB8u & correctedImage)
{
    kn::Vector<double> correctedPixel(3);
    kn::Vector<double> distordedPixel(3);
    correctedPixel[2] = 1.0;
    distordedPixel[2] = 1.0;
     	    
    // apply the (inverse) correction
    for(unsigned int i=0; i<correctedImage.width(); i++)
        for(unsigned int j=0; j<correctedImage.height(); j++)
        {
            correctedPixel[0] = i;
    	    correctedPixel[1] = j;

    	    radialDistortionCorrector(-k,center,distordedPixel,correctedPixel);


    	    if(distordedImage.contains((int)distordedPixel[0],(int)distordedPixel[1]))
	          {
		        unsigned char color[3];
		        distordedImage.atBilinear(distordedPixel[0],distordedPixel[1],color);
		        for(unsigned int c=0; c<3; c++)
		            correctedImage(i,j,c) = color[c];
            }
        }
}



/// Apply the radial distortion of in input image, with anti-aliasing and a scale factor. 
void radialDistortionCorrector(const double &k,
                               const kn::Vector<double> &center,
                               const kn::ImageRGB8u & distordedImage,
			                   kn::ImageRGB8u & correctedImage,
			                   const double &scale)
{
    // compute the scale homography
    kn::Matrix3x3d H;
    H.setIdentity();
    H[0][0] = 1.0/scale;
    H[1][1] = 1.0/scale;
    H[0][2] = (1.0-1.0/scale)*correctedImage.width()/2.0;
    H[1][2] = (1.0-1.0/scale)*correctedImage.height()/2.0;

    kn::Vector<double> correctedPixel(3);
    kn::Vector<double> distordedPixel(3);

    // apply the (inverse) correction
    for(unsigned int i=0; i<correctedImage.width(); i++)
        for(unsigned int j=0; j<correctedImage.height(); j++)
        {
            correctedPixel[0] = i;
    	    correctedPixel[1] = j;
    	    correctedPixel[2] = 1.0;
    	    correctedPixel = H * correctedPixel;

    	    radialDistortionCorrector(-k,center,distordedPixel,correctedPixel);

    	    if(distordedImage.contains((int)distordedPixel[0],(int)distordedPixel[1]))
	          {
		        unsigned char color[3];
		        distordedImage.atBilinear(distordedPixel[0],distordedPixel[1],color);
		        for(unsigned int c=0; c<3; c++)
		            correctedImage(i,j,c) = color[c];
            }
        }
}

	/*
	 * End of Namespace
	 */
}
