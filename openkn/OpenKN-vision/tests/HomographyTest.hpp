/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * HomographyTest.hpp created in 03 2009.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN__HOMOGRAPHYTEST_HPP__
#define __OPENKN__HOMOGRAPHYTEST_HPP__

/*
 * External Includes
 */
#include <cxxtest/TestSuite.h>
#include <iostream>
#include <string>

/*
 * Internal Includes
 */
#include <OpenKN/vision/Homography.hpp>
#include <OpenKN/math/Vector3.hpp>
#include <OpenKN/math/Matrix3x3.hpp>


/*
 * Class definition
 */

class HomographyTest : public CxxTest::TestSuite {
public:
    void testComputeHomographyNormalizedException( void ) {

        const std::vector< std::pair<kn::Vector3d,kn::Vector3d> > points;
        TS_ASSERT_THROWS(kn::computeHomography(points, true), kn::VisionException)
            }

    void testComputeHomographyUnnormalizedException( void ) {

        const std::vector< std::pair<kn::Vector3d,kn::Vector3d> > points;
        TS_ASSERT_THROWS(kn::computeHomography(points, false), kn::VisionException)
            }


    void testComputeHomographyNormalized( void ) {

        std::vector< std::pair<kn::Vector3d,kn::Vector3d> > myList;

        kn::Vector3d pixel1;
        kn::Vector3d pixel2;

        // correspondance 1
        pixel1[0] =  0.0; pixel1[1] =  0.0; pixel1[2] =  1.0;
        pixel2[0] = 10.0; pixel2[1] =  0.0; pixel2[2] =  1.0;
        myList.push_back(std::pair<kn::Vector3d,kn::Vector3d>(pixel1,pixel2));

        // correspondance 2
        pixel1[0] = 10.0; pixel1[1] =  0.0; pixel1[2] =  1.0;
        pixel2[0] = 30.0; pixel2[1] =  0.0; pixel2[2] =  1.0;
        myList.push_back(std::pair<kn::Vector3d,kn::Vector3d>(pixel1,pixel2));

        // correspondance 3
        pixel1[0] = 10.0; pixel1[1] = 10.0; pixel1[2] =  1.0;
        pixel2[0] = 30.0; pixel2[1] = 30.0; pixel2[2] =  1.0;
        myList.push_back(std::pair<kn::Vector3d,kn::Vector3d>(pixel1,pixel2));

        // correspondance 4
        pixel1[0] =  0.0; pixel1[1] = 10.0; pixel1[2] =  1.0;
        pixel2[0] = 10.0; pixel2[1] = 30.0; pixel2[2] =  1.0;
        myList.push_back(std::pair<kn::Vector3d,kn::Vector3d>(pixel1,pixel2));

        // compute homography
        kn::Matrix3x3d Hnormalized(kn::computeHomography(myList,true));
        Hnormalized /= Hnormalized[2][2];

        // the result should be :
        // 2 0 10
        // 0 3  0
        // 0 0  1

        // result
        kn::Matrix3x3d result;
        result.setIdentity();
        result[0][0] = 2.0;
        result[0][2] = 10.0;
        result[1][1] = 3.0;
        for(unsigned int i=0; i<result.rows(); ++i)
            for(unsigned int j=0; j<result.columns(); ++j)
                TS_ASSERT_DELTA(result[i][j], Hnormalized[i][j], 1.0e-9);

    	// test
    	kn::Vector3d pixel;
    	for(unsigned int i=0; i<myList.size(); i++)
    	  {
    	    pixel = Hnormalized * myList[i].first;
    	    pixel.setHomogeneousNormalForm();
    	    pixel = pixel - myList[i].second;

                TS_ASSERT_DELTA(pixel[0], 0.0, 1.0e-9);
                TS_ASSERT_DELTA(pixel[1], 0.0, 1.0e-9);
            }
    }


    void testComputeHomographyUnnormalized( void ) {

        std::vector< std::pair<kn::Vector3d,kn::Vector3d> > myList;
        
        kn::Vector3d pixel1;
        kn::Vector3d pixel2;

        // correspondance 1
        pixel1[0] =  0.0; pixel1[1] =  0.0; pixel1[2] =  1.0;
        pixel2[0] = 10.0; pixel2[1] =  0.0; pixel2[2] =  1.0;
        myList.push_back(std::pair<kn::Vector3d,kn::Vector3d>(pixel1,pixel2));
        
        // correspondance 2
        pixel1[0] = 10.0; pixel1[1] =  0.0; pixel1[2] =  1.0;
        pixel2[0] = 30.0; pixel2[1] =  0.0; pixel2[2] =  1.0;
        myList.push_back(std::pair<kn::Vector3d,kn::Vector3d>(pixel1,pixel2));

        // correspondance 3
        pixel1[0] = 10.0; pixel1[1] = 10.0; pixel1[2] =  1.0;
        pixel2[0] = 30.0; pixel2[1] = 30.0; pixel2[2] =  1.0;
        myList.push_back(std::pair<kn::Vector3d,kn::Vector3d>(pixel1,pixel2));

        // correspondance 4
        pixel1[0] =  0.0; pixel1[1] = 10.0; pixel1[2] =  1.0;
        pixel2[0] = 10.0; pixel2[1] = 30.0; pixel2[2] =  1.0;
        myList.push_back(std::pair<kn::Vector3d,kn::Vector3d>(pixel1,pixel2));

        // compute homography
        kn::Matrix3x3d Hunnormalized(kn::computeHomography(myList,false));
        Hunnormalized /= Hunnormalized[2][2];

        // the result should be :
        // 2 0 10
        // 0 3  0
        // 0 0  1
        
        // result
        kn::Matrix3x3d result;
        result.setIdentity();
        result[0][0] = 2.0;
        result[0][2] = 10.0;
        result[1][1] = 3.0;
        for(unsigned int i=0; i<result.rows(); ++i)
            for(unsigned int j=0; j<result.columns(); ++j)
                TS_ASSERT_DELTA(result[i][j], Hunnormalized[i][j], 1.0e-9);

        // test
        kn::Vector3d pixel;
        for(unsigned int i=0; i<myList.size(); i++)
        {
            pixel = Hunnormalized * myList[i].first;
            pixel.setHomogeneousNormalForm();
            pixel = pixel - myList[i].second;

	        TS_ASSERT_DELTA(pixel[0], 0.0, 1.0e-9);
	        TS_ASSERT_DELTA(pixel[1], 0.0, 1.0e-9);
	    }
    }

};


/*
 * End of Anti-doublon
 */
#endif
