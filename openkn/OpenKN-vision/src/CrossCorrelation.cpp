/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * CrossCorrelation.cpp created in 01 2010.
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

/*
 * Internal Includes
 */
#include "CrossCorrelation.hpp"

namespace kn {

  /**
   * \cond
   * \brief Return dotProduct between 2 image
   * \param image1	: Image
   * \param pt1		: Interest point for image1
   * \param image2	: Image
   * \param pt2		: Interest point for image2
   * \param windowSize	: Size of the correlation window
   * \param channel	: Channel of the images to consider
   * \return double result from the product
   */
  double matchDotProduct(const Image<unsigned char> &image1,
      const Vector3d &pt1,
      const Image<unsigned char> &image2,
      const Vector3d &pt2,
      const Vector2i &windowSize,
      unsigned int channel=0){

    //compute average value under the window
    double average1 = 0.0;
    double average2 = 0.0;
    for(int i=-windowSize.x()/2; i<windowSize.x()/2; i++){
      for(int j=-windowSize.y()/2; j<windowSize.y()/2; j++){
	average1 += image1(pt1.x()+i,pt1.y()+j,channel);
	average2 += image2(pt2.x()+i,pt2.y()+j,channel);
      }
    }
    average1 = average1/(windowSize.x()*windowSize.y());
    average2 = average2/(windowSize.x()*windowSize.y());

    //compute dot product
    double dot = 0.0;
    for(int i=-windowSize.x()/2; i<windowSize.x()/2; i++){
      for(int j=-windowSize.y()/2; j<windowSize.y()/2; j++){
	dot += (image1(pt1.x()+i,pt1.y()+j,channel)-average1 ) * (image2(pt2.x()+i,pt2.y()+j,channel)-average2 );
      }
    }
    return dot/(windowSize.x()*windowSize.y());
  }
  /// \endcond

  double crossCorrelation(const Image<unsigned char> &image1,
      const Image<unsigned char> &image2,
      unsigned int channel){

    if(image1.nbChannel()<channel || image2.nbChannel()<channel)
      throw VisionException("Error : invalid channel value");

    if(image1.width()!=image2.width() || image1.height()!=image2.height())
      throw VisionException("Error : Images must have the same size");


    kn::Vector2i windowSize;
    windowSize.x()=image1.width()    - (1-image1.width()%2);
    windowSize.y()=image1.height() - (1-image1.height()%2);
    kn::Vector3d center;
    center.x()=windowSize.x()/2;
    center.y()=windowSize.y()/2;
    center.z()=1;


    double result = matchDotProduct(image1,center,image2,center,windowSize,channel);
    result /= std::sqrt(matchDotProduct(image1,center,image1,center,windowSize,channel));//norm image1
    result /= std::sqrt(matchDotProduct(image2,center,image2,center,windowSize,channel));//norm image2

    return result;
  }

  double crossCorrelation(const Image<unsigned char> &image1,
      const Vector3d &pt1,
      const Image<unsigned char> &image2,
      const Vector3d &pt2,
      const Vector2i &windowSize,
      unsigned int channel){

    double result = matchDotProduct(image1,pt1,image2,pt2,windowSize,channel);
    result /= std::sqrt(matchDotProduct(image1,pt1,image1,pt1,windowSize,channel));//norm image1
    result /= std::sqrt(matchDotProduct(image2,pt2,image2,pt2,windowSize,channel));//norm image2

    return result;
  }

  double crossCorrelationGS(const Image<unsigned char> &image1,
      const Vector3d &pt1,
      const Image<unsigned char> &image2,
      const Vector3d &pt2,
      const Vector2i &windowSize){

    return crossCorrelation(image1,pt1,image2,pt2,windowSize);
  }

  double crossCorrelationRGB(const Image<unsigned char> &image1,
      const Vector3d &pt1,
      const Image<unsigned char> &image2,
      const Vector3d &pt2,
      const Vector2i &windowSize){

    double score  = crossCorrelation(image1,pt1,image2,pt2,windowSize,0)+
      crossCorrelation(image1,pt1,image2,pt2,windowSize,1)+
      crossCorrelation(image1,pt1,image2,pt2,windowSize,2);
    score /= 3.0;

    return score;
  }

  std::vector< std::pair<kn::Vector3d, kn::Vector3d> > crossCorrelation(const kn::Image<unsigned char> &image1,
      std::vector<kn::Vector3d> &list1,
      const kn::Image<unsigned char> &image2,
      std::vector<kn::Vector3d> &list2,
      const kn::Vector2i &windowSize,
      double minThreshold,
      unsigned int nbChannel){

    if(nbChannel != 1 && nbChannel != 3)
      throw VisionException("Error : nbChannel must be 1 (GS) or 3 (RGB)");

    if(image1.nbChannel()!=nbChannel || image2.nbChannel()!=nbChannel){
      if(nbChannel==1)
	throw VisionException("Error : Image are not grayscale (1 channel)");
      if(nbChannel==3)
	throw VisionException("Error : Image are not RGB (3 channel)");
    }

    //return variable
    std::vector< std::pair<Vector3d, Vector3d> > pair;

    //iterator on the first list of interest point
    std::vector<Vector3d>::iterator iter1 = list1.begin();
    //iterator on the second list of interest point
    std::vector<Vector3d>::iterator iter2;

    while(iter1 != list1.end()){
      //avoid point too close from the image border
      if((*iter1).x()>windowSize.x()/2 &&
	  (*iter1).x()<image1.width()-windowSize.x()/2 &&
	  (*iter1).y()>windowSize.y()/2 &&
	  (*iter1).y()<image1.height()-windowSize.y()/2){
	double maxScore = -2.0;
	Vector3d brother;
	brother[2] = 1.0;

	//reset second iterator
	iter2 = list2.begin();
	while(iter2 != list2.end()){
	  //avoid point too close from the image border
	  if((*iter2).x()>windowSize.x()/2 &&
	      (*iter2).x()<image2.width()-windowSize.x()/2 &&
	      (*iter2).y()>windowSize.y()/2 &&
	      (*iter2).y()<image2.height()-windowSize.y()/2){
	    double score = crossCorrelation(image1,(*iter1),image2,(*iter2),windowSize);
	    //We only keep the best score
	    if(score > maxScore){
	      maxScore = score;
	      brother[0] = (*iter2).x();
	      brother[1] = (*iter2).y();
	    }
	  }
	  iter2++;
	}

	//keep the pair if correlation score is better than the threshold
	if(maxScore > minThreshold){
	  pair.push_back(std::pair<Vector3d, Vector3d>((*iter1),brother));
	}
      }
      iter1++;
    }
    return pair;
  }



  /*
   * End of Namespace
   */
}
