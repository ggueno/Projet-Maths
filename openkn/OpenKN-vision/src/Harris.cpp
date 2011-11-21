/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * Harris.cpp created in 01 2009.
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
#include "Harris.hpp"

namespace kn {

  /**
   * \cond
   * \brief Compute Gaussian gradient line kernel
   * \param size  : length of the kernel ( odd )
   * \param sigma : coef used for the kernel
   * \return Vectord the kernel values
   * \throw VisionException Error : size must be odd
   */
  kn::Vectord gaussGradKernelv(const unsigned int size, const double sigma){
    if(size%2 != 1)
      throw VisionException("Error : size must be odd");
    int minusSize = -size;
    Vectord mask(size);
    double squareSigma = sigma*sigma*size*size;
    double sum = 0.0;

    for(int i=0; i<int(size); i++){
      //TODO ? remove (minusSize/2)*(minusSize/2) ?
      double squareDist = (minusSize/2)*(minusSize/2)+(minusSize/2+i)*(minusSize/2+i);
      mask[i]  = std::exp(-squareDist/(2.0*squareSigma));
      mask[i] *= -(minusSize/2+i);
      sum += std::fabs(mask[i]);
    }

    for(unsigned int i=0;i<size;i++){
      if(std::fabs(sum)>1.0e-10)
      mask[i] /= sum;//2*M_PI*squareSigma*squareSigma;
      mask[i] *= 2.0;
    }

    return mask;
  }
  /// \endcond

  /**
   * \cond
   * \brief Clamp val between 0 and 255 and return it as an unsigned char
   * \param val : double value to clamp
   * \return unsigned char from val
   */
  unsigned char clampUchar(const double val){
    if(val > 255) return 255;
    if(val < 0)   return 0;
    return val;
  }
  /// \endcond

 /**
   * \cond
   * \brief Compute derivated gaussian line convolution in x and y coordinate
   * \param src	  : source image
   * \param gradx : horizontal convolution result
   * \param grady : vertital convolution result
   * \param size  : Convolution window size
   * \param sigma : coef used for the kernel
   * \throw VisionException Error : gradx image has not the same size or channel number as the source image
   * \throw VisionException Error : grady image has not the same size or channel number as the source image
   * \throw VisionException Error : size must be odd
   */
  void gaussGradAbsFilter(const kn::Image<unsigned char> &src, kn::Image<unsigned char> &gradx, kn::Image<unsigned char> &grady,const unsigned int size, const double sigma){
    if(src.width()!=gradx.width() || src.height() != gradx.height() || src.nbChannel() != gradx.nbChannel())
      throw VisionException("Error : gradx image has not the same size or channel number as the source image");
    if(src.width()!=grady.width() || src.height() != grady.height() || src.nbChannel() != grady.nbChannel())
      throw VisionException("Error : grady image has not the same size or channel number as the source image");

    if(size%2 != 1)
      throw VisionException("Error : size must be odd");

    //compute the convolution mask
    Vectord mask=gaussGradKernelv(size,sigma);

    // application du masque
    unsigned int xBorder = mask.size()/2;
    unsigned int yBorder = mask.size()/2;

    for(unsigned int i=xBorder; i<src.width()-xBorder; i++){
      for(unsigned int j=yBorder; j<src.height()-yBorder; j++){
	for(unsigned int c=0; c<src.nbChannel(); ++c){
	  double sumx = 0.0;
	  double sumy = 0.0;
	  for(unsigned int m=0; m<mask.size(); ++m){
	    sumx += mask[m] * src.at(i+m-xBorder  ,j	      ,c);
	    sumy += mask[m] * src.at(i		  ,j+m-yBorder,c);
	  }
	  gradx.at(i,j,c) = clampUchar(std::fabs(sumx));
	  grady.at(i,j,c) = clampUchar(std::fabs(sumy));
	}
      }
    }
  }
  /// \endcond


  //TODO comment
  Matrixd gaussMask(unsigned int size){
    Matrixd mask(size,size);
    unsigned int radius=size/2+1;
    double ratio = 1./(radius*radius*radius*radius);
    for(unsigned int i=0;i<radius;i++){
      for(unsigned int j=0;j<radius;j++){
	mask.at(i,j)=(i+1.)*(j+1.)*ratio;
	mask.at(i,size-1-j)=mask.at(i,j);
	mask.at(size-1-i,j)=mask.at(i,j);
	mask.at(size-1-i,size-1-j)=mask.at(i,j);
      }
    }
    return mask;
  }

  //TODO comment
  kn::Image<double> gaussFilter(const kn::Image<double> &src, unsigned int size, unsigned int nbChannel=0){
    Image<double> res(src);

    //Gaussian kernel
    Matrixd mask=gaussMask(size);
    //reset resulting image
    res.fill(0.0);
    //set number of channel to compute to all if no specified
    if(nbChannel==0)nbChannel=src.nbChannel();

    int radius = size/2;
    //image loop
    for(unsigned int i=radius; i<src.width()-radius; i++){
      for(unsigned int j=radius; j<src.height()-radius; j++){
	for(unsigned int c=0; c<nbChannel; c++){
	  //mask loop
	  double val = 0.0;
	  for(int k=-radius; k<=radius; k++){
	    for(int l=-radius; l<=radius; l++){
	      val +=  src.at(i+k,j+l,c) * mask[k+radius][l+radius];
	    }
	  }
	  res.at(i,j,c)=val;
	}
      }
    }
    return res;
  }


  //TODO comment
  /**
   * \cond
   * \brief Last step to compute harris filter from the first 3 precompute channel in the \f$4^{th}\f$
   *
   * \f$ x*y - z*z - k(x+y) \f$
   * \param filteredImages Images precomputed on the first 3 channel which will receive harris computation in its \f$4^{th}\f$
   * \throw VisionException Error : src depth is not 4
   */
  void harrisCompute(kn::Image<double> &filteredImages, const double k){
    if(filteredImages.nbChannel()!=4)
      throw VisionException("Error : src depth is not 4");

    for(unsigned int i=0; i<filteredImages.width(); i++){
      for(unsigned int j=0; j<filteredImages.height(); j++){
	filteredImages.at(i,j,3) = filteredImages.at(i,j,0) * filteredImages.at(i,j,1) //x*y
	  -filteredImages.at(i,j,2) * filteredImages.at(i,j,2) //-z*z
	  -k * ( filteredImages.at(i,j,0) + filteredImages.at(i,j,1) );//-k(x+y)
      }
    }
  }
  /// \endcond


  /**
   * \cond
   * \brief Find local maxima
   * \param filteredImages  : RGBA image containing harris score on alpha channel
   * \param threshold	    : Minimal theshold to be considered as a maxima
   * \param nbPoint	    : Approximative number of point wanted (0 -> all maxima)
   * \param x		    : left value to start on filteredImages
   * \param y		    : up value to start on filteredImages
   * \param dx		    : width of subimage
   * \param dy		    : height of subimage
   * \throw VisionException Error : images size must be the same
   * \throw VisionException Error : matrix and images size must be the same
   * \throw VisionException Error : result depth is not 4
   */
  std::vector<kn::Vector3d> findHarrisPoint(kn::Image<double> filteredImages, const unsigned int nbPoint=0, double threshold=1.0e6,
      unsigned int x=0, unsigned int y=0, unsigned int dx=0,unsigned int dy=0,unsigned int border=0){
    std::vector<Vector3d> harrisResult;
    //avoid border of the image
    if(x==0){x=1+border;if(dx!=0 && dx>border)dx-=1+border;}
    if(y==0){y=1+border;if(dy!=0 && dy>border)dy-=1+border;}
    if(dx==0 || x+border+dx >= filteredImages.width())	dx=filteredImages.width() - x - border -1;
    if(dy==0 || y+border+dy >= filteredImages.height()) dy=filteredImages.height()- y - border -1;
    Vector3d myPixel;
    myPixel[2]=1.0;


    //If limited number of point
    if(nbPoint!=0){
      std::multiset<double> scores;
      std::multiset<double>::iterator iter;
      //set minimal threshold
      double min_threshold = threshold * 1.0e-2;

      //find all possible interest point
      //i.e. find all local maxima > min_thresold
      for(unsigned int i=x; i<x+dx; i++){
	for(unsigned int j=y; j<y+dy; j++){
	  if( filteredImages.at(i,j,3)>min_threshold &&
	      filteredImages.at(i,j,3)>filteredImages.at(i,j-1,3) &&
	      filteredImages.at(i,j,3)>filteredImages.at(i,j+1,3) &&
	      filteredImages.at(i,j,3)>filteredImages.at(i-1,j,3) &&
	      filteredImages.at(i,j,3)>filteredImages.at(i+1,j,3)
	    )
	    scores.insert(filteredImages.at(i,j,3));
	}
      }
      //if none return an empty vector
      if(scores.empty()){
	return harrisResult;
      }
      iter = scores.end();
      iter--;
      //else if candidate > point limit we find the theshold value corresponding
      if(scores.size()>=nbPoint){
	for (unsigned int pos=0; pos<nbPoint && iter != scores.begin(); pos++){
	  iter--;
	}
	threshold=*iter;
      }else{
	//else we set the threshold to min_threshold to consider all point
	threshold = min_threshold;
      }
    }

    //find all candidate after setting the threshold automaticaly with the previous constraint
    for(unsigned int i=x; i<x+dx; i++){
      for(unsigned int j=y; j<y+dy; j++){
	//we want the harris value to be a local maxima > threshold
	if( filteredImages.at(i,j,3)>threshold &&
	    filteredImages.at(i,j,3)>filteredImages.at(i,j-1,3) &&
	    filteredImages.at(i,j,3)>filteredImages.at(i,j+1,3) &&
	    filteredImages.at(i,j,3)>filteredImages.at(i-1,j,3) &&
	    filteredImages.at(i,j,3)>filteredImages.at(i+1,j,3) ){
	  myPixel[0] = i;
	  myPixel[1] = j;
	  harrisResult.push_back(myPixel);
	}
      }
    }
    return harrisResult;
  }
 ///\endcond

  /**
   * \cond
   * \brief Compute  result(x,y,0/1/2) = image1(x,y)^2 / image2(x,y)^2 / image1(x,y)*image2(x,y)
   * \param image1 : first image
   * \param image2 : second image of the same size as image1
   * \param result : Image of the same size of image1 and image2 but of depth 4
   * \throw VisionException Error : images size must be the same
   * \throw VisionException Error : matrix and images size must be the same
   * \throw VisionException Error : result depth is not 4
   */
  void precomputeHarris(const kn::Image<unsigned char> &image1, const kn::Image<unsigned char> &image2, kn::Image<double> &result){
    if(image1.width()!=image2.width() || image1.height() != image2.height())
      throw VisionException("Error : images size must be the same");
    if(image1.width()!=result.width() || image1.height() != result.height())
      throw VisionException("Error : matrix and images size must be the same");
    if(result.nbChannel()!=4)
      throw VisionException("Error : result depth is not 4");

    for(unsigned int i=0; i<image1.width(); i++){
      for(unsigned int j=0; j<image1.height(); j++){
	result(i,j,0) = 1 + image1(i,j,0) * image1(i,j,0);//image1 ^2
	result(i,j,1) = 1 + image2(i,j,0) * image2(i,j,0);//image2 ^2
	result(i,j,2) = 1 + image1(i,j,0) * image2(i,j,0);//image1 * image2
      }
    }
  }
  /// \endcond


  /**
   * \brief Find interest point using Harris corner detector (Homogeneous repartition possible).
   * \param image	    : Image gray scale
   * \param nbPoint	    : Wanted number of point in each partition
   * ( minimal threshold is \f$threshold * 1.0e^{-2}\f$)
   * \param nbPartx	    : Number of partition on width (if 0 no partition)
   * \param nbParty	    : Number of partition on height (if 0 then equals nbPartx)
   * \param gradConvSize    : Gradient convolution window size (auto = 0)
   * \param gaussConvSize   : Gaussian convolution window size (auto = 0)
   * \param threshold	    : Minimal value used as a threshold for valid interest point
   * \param k		    : Coefficient used in Harris filter computation
   * \return std::vector<kn::Vector3d> a vector of interest point
   * \throw VisionException Error : Image is not grayscale (1 channel)
   */
  std::vector<kn::Vector3d> harris(const kn::Image<unsigned char> &image, unsigned int nbPoint, unsigned int nbPartx,unsigned int nbParty, unsigned int gradConvSize,unsigned int gaussConvSize, const double threshold, const double k){
    if(image.nbChannel()!=1)
      throw VisionException("Error : Image is not grayscale (1 channel)");

    //convolution window size
    //TODO (or not) adaptative size of kernel
    if(gradConvSize==0)gradConvSize = 3;
    if(gaussConvSize==0)gaussConvSize=5;

    if(nbParty==0)nbParty=nbPartx;
    //resulting image from convolution
    Image<unsigned char> xGradImg(image);
    Image<unsigned char> yGradImg(image);

    //line kernel used once in x and then in y for gradient computation
    gaussGradAbsFilter(image,xGradImg,yGradImg,gradConvSize,0.8);

    unsigned int w = image.width();
    unsigned int h = image.height();
    //Image containing a grayscale filter result in each channel
    Image<double> filteredImages(w,h,4);
    //x channel will contain xgrad^2
    //y channel will contain ygrad^2
    //z channel will contain xgrad*ygrad
    precomputeHarris(xGradImg,yGradImg,filteredImages);
    //apply gaussian filtering on each channel separately
    filteredImages = gaussFilter(filteredImages,gaussConvSize,3);

    //Last step to compute harris filter from the first 3 precompute channel in the 4th
    //x*y - z*z - k(x+y)
    harrisCompute(filteredImages,k);

    //If no partition
    if(nbPartx==0 || (nbPartx==1 && nbParty==1))
      return findHarrisPoint(filteredImages,nbPoint,threshold,0,0,0,0,gaussConvSize/2);


//TODO ajout de marge sur les borne des qui  sont sur le contour de l'image.

    //complete interest point list
    std::vector<kn::Vector3d> interestPoint;
    //interest point of a subimage
    std::vector<kn::Vector3d> tmp;

    unsigned int sizex = filteredImages.width()/nbPartx;
    unsigned int sizey = filteredImages.height()/nbParty;

    for(unsigned int i=0;i<nbPartx;i++){
      for(unsigned int j=0;j<nbParty;j++){
	tmp.clear();
	tmp = findHarrisPoint(filteredImages,nbPoint,threshold,i*sizex,j*sizey,sizex,sizey,gaussConvSize/2);
	interestPoint.insert(interestPoint.begin(),tmp.begin(),tmp.end());
      }
    }

    return interestPoint;
  }

  /*
   * End of Namespace
   */
}
