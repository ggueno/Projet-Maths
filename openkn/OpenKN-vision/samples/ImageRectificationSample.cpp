/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * ImageRectificationSample.cpp created in 04 2010.
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

/*
 * External Includes
 */
#include <cassert>

/*
 * Internal Includes
 */
#include <OpenKN/image/ImageRGB.hpp>
#include <OpenKN/image/ioJPG.hpp>
#include <OpenKN/image/DrawCircle.hpp>
#include <OpenKN/image/DrawLine.hpp>

#include <OpenKN/vision/EpipolarGeometry.hpp>
#include <OpenKN/vision/ImageRectification.hpp>

#include <OpenKN/math/MathIO.hpp>
#include <OpenKN/math/Matrix3x3.hpp>

#include <OpenKN/math/Vector.hpp>

const bool debug = true;

int main()
{
    // input images
    kn::ImageRGB8u image1;
    kn::ImageRGB8u image2;
    
    // load images
    kn::loadJPG(image1,"inputData/maid0.jpg");
    kn::loadJPG(image2,"inputData/maid1.jpg");
    
    // load correspondance list
    std::vector<kn::Vector3d> list1;
    std::vector<kn::Vector3d> list2;
    kn::loadVectorList (list1,"inputData/maid0.list");
    kn::loadVectorList (list2,"inputData/maid1.list");
    
    // make a pair list 
    assert(list1.size() == list2.size());
    std::vector< std::pair<kn::Vector3d,kn::Vector3d> > pairList;
    for(unsigned int i=0; i<list1.size(); ++i) 
        pairList.push_back(std::pair< kn::Vector3d, kn::Vector3d > (list1[i],list2[i]));

    // debug
    if(debug){
        // draw and save selected points
        for(unsigned int i=0; i<list1.size();  ++i) {
            kn::drawDisc(image1, list1[i][0],list1[i][1], 3, 255,0,0);
            kn::drawDisc(image2, list2[i][0],list2[i][1], 3, 255,0,0);
        }
        kn::saveJPG(image1,"outputData/imageRectificationInput1.jpg");
        kn::saveJPG(image2,"outputData/imageRectificationInput2.jpg");

        // compute the fundamental matrix
        kn::Matrix3x3d F = kn::computeFundamentalMatrixNormalized(pairList);
        //std::cout << "F\n"  << F ; 
    
        // draw epipolar lines
        for(unsigned int i=0; i<list1.size();  ++i) {
           kn::drawLine(image1, (list2[i]*F).begin(), 0,0,255);
           kn::drawLine(image2, (F*list1[i]).begin(), 0,0,255);
        }    
        kn::saveJPG(image1,"outputData/imageRectificationEpipolar1.jpg");
        kn::saveJPG(image2,"outputData/imageRectificationEpipolar2.jpg");
    }

    // image rectification
    kn::Matrix3x3d H1;
    kn::Matrix3x3d H2;
    imageRectification(pairList, image1.width(), image1.height(), H1, H2);

    // apply the rectification
    kn::ImageRGB8u outputImage1(image1.width(),image1.height());
    kn::ImageRGB8u outputImage2(image2.width(),image2.height());
    imageRectify(image1,image2,outputImage1,outputImage2,H1,H2);
    
    // save the result
    kn::saveJPG(outputImage1,"outputData/imageRectified1.jpg");
    kn::saveJPG(outputImage2,"outputData/imageRectified2.jpg"); 
    
    // the same on bigger output images1
    double scale = 2.0;
    kn::ImageRGB8u outputImageBig1(scale*image1.width(),scale*image1.height());
    kn::ImageRGB8u outputImageBig2(scale*image1.width(),scale*image1.height());
    
    // center the result (optional, but useful)
    kn::Matrix3x3d Hcenter;
    Hcenter.setIdentity();
    Hcenter[0][2] = image1.width()*(scale-1.0)/2.0;
    Hcenter[1][2] = image1.height()*(scale-1.0)/2.0;
    H1 = Hcenter * H1;
    H2 = Hcenter * H2;
    
    // apply the rectification
    imageRectify(image1,image2,outputImageBig1,outputImageBig2,H1,H2);
    
    // save the result
    kn::saveJPG(outputImageBig1,"outputData/imageRectifiedBig1.jpg");
    kn::saveJPG(outputImageBig2,"outputData/imageRectifiedBig2.jpg"); 

    return 0;
}

