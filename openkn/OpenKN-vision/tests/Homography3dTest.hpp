/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * HomographyTest3d.hpp created in 03 2010.
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
#ifndef __OPENKN__HOMOGRAPHY3DTEST_HPP__
#define __OPENKN__HOMOGRAPHY3DTEST_HPP__

/*
 * External Includes
 */
#include <cxxtest/TestSuite.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>
/*
 * Internal Includes
 */
#include <OpenKN/vision/Homography3d.hpp>
#include <OpenKN/math/Vector4.hpp>
#include <OpenKN/math/Matrix4x4.hpp>
#include <OpenKN/math/MathIO.hpp>
#include <OpenKN/math/Rank.hpp>

/*
 * Class definition
 */


class Homography3dTest : public CxxTest::TestSuite {
  public:
    void testComputeHomography3DException( void ) {
      std::vector< std::pair<kn::Vector4d,kn::Vector4d> > points;
      TS_ASSERT_THROWS(kn::computeHomography3d(points), kn::VisionException)
    }

    void testComputeHomography3d( void ) {

      std::vector< std::pair<kn::Vector4d,kn::Vector4d> > points3d3d;

      kn::Vector4d point3d;
      point3d[3]=1.0;

      //x axis
      kn::Matrix4x4d rot,scale,trans;
      kn::loadMatrix(rot,"inputData/matrix4x4_rotate.mat");
      kn::loadMatrix(scale,"inputData/matrix4x4_scale.mat");
      kn::loadMatrix(trans,"inputData/matrix4x4_translate.mat");

      //Homography -> Rotate , scale , translate
      kn::Matrix4x4d homog;
      homog = rot*scale*trans;
      homog.roundZero(10e-10);

#ifdef DEBUG
      std::cout<<std::endl<<"Homog "<<std::endl<<homog<<std::endl;

      // correspondance 1
      point3d[0] =  0.0; point3d[1] =  0.0; point3d[2] =  0.0;
      points3d3d.push_back(std::pair<kn::Vector4d,kn::Vector4d>(point3d,homog*point3d));
      // correspondance 2
      point3d[0] =  1.0; point3d[1] =  0.0; point3d[2] =  0.0;
      points3d3d.push_back(std::pair<kn::Vector4d,kn::Vector4d>(point3d,homog*point3d));
      // correspondance 3
      point3d[0] =  0.0; point3d[1] =  1.0; point3d[2] =  0.0;
      points3d3d.push_back(std::pair<kn::Vector4d,kn::Vector4d>(point3d,homog*point3d));
      // correspondance 4
      point3d[0] =  0.0; point3d[1] =  0.0; point3d[2] =  1.0;
      points3d3d.push_back(std::pair<kn::Vector4d,kn::Vector4d>(point3d,homog*point3d));
#endif

      //Random correspondance
      srand(0);
      while(points3d3d.size()<20){
	for(unsigned int i=0;i<3;i++)
	  point3d[i]=(rand()%1000)-500;
	points3d3d.push_back(std::pair<kn::Vector4d,kn::Vector4d>(point3d,homog*point3d));
      }

      // compute homography
      kn::Matrix4x4d Hnormalized(kn::computeHomography3d(points3d3d));
      Hnormalized.roundZero(1.0e-10);

#ifdef DEBUG
      std::cout<<std::endl<<"Homog "<<std::endl<<Hnormalized<<std::endl;
#endif


      // test
      kn::Vector4d pixel;
      for(unsigned int i=0; i<points3d3d.size(); i++){
	pixel = Hnormalized * points3d3d[i].first;
	pixel.setHomogeneousNormalForm();
	pixel = pixel - points3d3d[i].second;

	TS_ASSERT_DELTA(pixel[0], 0.0, 1.0e-9);
	TS_ASSERT_DELTA(pixel[1], 0.0, 1.0e-9);
	TS_ASSERT_DELTA(pixel[2], 0.0, 1.0e-9);
      }

      //Test with projective matrix
      kn::loadMatrix(homog,"inputData/matrix4x4_proj.mat");

      std::vector< std::pair<kn::Vector4d,kn::Vector4d> >::iterator iter = points3d3d.begin();
      while(iter < points3d3d.end()){
	iter->second=homog*iter->first;
	iter++;
      }
      // compute homography
      Hnormalized = kn::computeHomography3d(points3d3d);
      Hnormalized.roundZero(1.0e-10);

#ifdef DEBUG
      std::cout<<std::endl<<"Homog projective"<<std::endl<<Hnormalized<<std::endl;
#endif
      // test
      for(unsigned int i=0; i<points3d3d.size(); i++){
	pixel = Hnormalized * points3d3d[i].first;
	pixel.setHomogeneousNormalForm();
	points3d3d[i].second.setHomogeneousNormalForm();
	pixel = pixel - points3d3d[i].second;

	TS_ASSERT_DELTA(pixel[0], 0.0, 1.0e-9);
	TS_ASSERT_DELTA(pixel[1], 0.0, 1.0e-9);
	TS_ASSERT_DELTA(pixel[2], 0.0, 1.0e-9);
      }
      

      //test with rank 4 matrix
      kn::loadMatrix(homog,"inputData/matrix4x4_rank4.mat");
      TS_ASSERT_EQUALS(kn::rank(homog),(int)4);

      iter = points3d3d.begin();
      while(iter < points3d3d.end()){
	iter->second=homog*iter->first;
	iter++;
      }
      // compute homography
      Hnormalized = kn::computeHomography3d(points3d3d);
      Hnormalized.roundZero(1.0e-10);

#ifdef DEBUG
      std::cout<<std::endl<<"Homog projective"<<std::endl<<Hnormalized<<std::endl;
#endif
      // test
      for(unsigned int i=0; i<points3d3d.size(); i++){
	pixel = Hnormalized * points3d3d[i].first;
	pixel.setHomogeneousNormalForm();
	points3d3d[i].second.setHomogeneousNormalForm();
	pixel = pixel - points3d3d[i].second;

	TS_ASSERT_DELTA(pixel[0], 0.0, 1.0e-9);
	TS_ASSERT_DELTA(pixel[1], 0.0, 1.0e-9);
	TS_ASSERT_DELTA(pixel[2], 0.0, 1.0e-9);
      }

    }

};

/*
 * End of Anti-doublon
 */
#endif
