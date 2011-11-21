/*************************************************************************** \
* Copyright (C) by University Paris-Est - MISS team
* ImageRectification.cpp created in 04 2010.
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
#include <cmath>
#include <iostream>
#include <cassert>

/*
* Internal Includes
*/
#include <ImageRectification.hpp>
#include <EpipolarGeometry.hpp>
#include <Homography.hpp>

#include <OpenKN/math/Vector.hpp>
#include <OpenKN/math/Matrix.hpp>
#include <OpenKN/math/Matrix3x3.hpp>
#include <OpenKN/math/Solver.hpp>
#include <OpenKN/math/Rank.hpp>


/*
* Namespace
*/
namespace kn{


       /*
	* \brief computes 2 homographies H1 and H2 designed for an image rectification of a pair of image, i.e. the epipolar lines are horizontal and aligned, this method uses a set of corresponding points between the 2 images to minimize the rectified images distorsion, note that the input images don't have to have the same resolution, this method is detailed in "Multiple view geometry", 2nd ed, page 307.
	* \param pairList : a set of corresponding points between image1 and image2, at least 8 points to compute the epipolar relation between the 2 images.
	* \param imageWidth2 : resolution of the image2
	* \param imageHeight2 : resolution of the image2
	* \param H1 : the homography to compute (to rectify image1)
	* \param H2 : the homography to compute (to rectify image2)
	* \throw VisionException too few corresponding points
	*/
        kn::Matrix3x3d  imageRectification(const std::vector< std::pair<kn::Vector3d,kn::Vector3d> > &pairList,
					   const unsigned int imageWidth2,
					   const unsigned int imageHeight2,
					   kn::Matrix3x3d &H1,
					   kn::Matrix3x3d &H2)
	{
	    // compute the fundamental matrix
	    kn::Matrix<double> F = kn::computeFundamentalMatrix(pairList);

	    // compute the epipoles
	    kn::Vector3d e1, e2;
	    kn::computeEpipoles(F, e1, e2);

	    // compute H2 
	    H2 = computeH2(e2,imageWidth2,imageHeight2);

	    // compute H1
	    H1 = computeH1(F,e2,H2,pairList);
	    //std::cout << "H1.e1 : " << H1*e1 << std::endl;
	    //std::cout << "H2.e2 : " << H2*e2 << std::endl;

	    return F;
	}


	/*
	* \brief computes 2 homographies H1 and H2 designed for an image rectification of a pair of image, i.e. the epipolar lines are horizontal and aligned, this method uses a set of corresponding points between the 2 images to minimize the rectified images distorsion, note that the input images don't have to have the same resolution, this method is detailed in "Multiple view geometry", 2nd ed, page 307.
	* \param F : fundamental matrix between image1 and image2
	* \param imageWidth1  : resolution of the image1
	* \param imageHeight1 : resolution of the image1
	* \param imageWidth2  : resolution of the image2
	* \param imageHeight2 : resolution of the image2
	* \param H1 : the homography to compute (to rectify image1)
	* \param H2 : the homography to compute (to rectify image2)
	*/
	void stereoscopicImageRectification(const kn::Matrix3x3d &F,
					    const unsigned int imageWidth1,
					    const unsigned int imageHeight1,
					    const unsigned int imageWidth2,
					    const unsigned int imageHeight2,
					    kn::Matrix3x3d &H1,
					    kn::Matrix3x3d &H2)
	{
	  // compute the epipoles
	  kn::Vector3d e1, e2;
	  kn::computeEpipoles(F, e1, e2);

	  // compute H2 
	  H2 = computeH2(e2,imageWidth2,imageHeight2);

	  // compute H1
	  H1 = computeH1stereoscopic(F,e2,H2,imageWidth1,imageHeight1);
	}


       /*
	* \brief computes the homography fo the second image
	* \param e2 : epipol in image2
	* \param imageWidth2 : resolution of the image2
	* \param imageHeight2 : resolution of the image2
	* \return H2 : the homography to rectify image2
	*/
	kn::Matrix3x3d computeH2(kn::Vector3d e2, const unsigned int imageWidth2, const unsigned int imageHeight2)
	{
	    // translation
	    kn::Matrix3x3d T;
	    T.setIdentity();
	    T[0][2] = -(imageWidth2/2.0);
	    T[1][2] = -(imageHeight2/2.0);

	    // apply the translation to e2
	    e2 = T * e2;

	    // rotation
	    double angle = acos(fabs(e2[0])/sqrt(e2[0]*e2[0]+e2[1]*e2[1]));
	    if(e2[0]*e2[1] > 0) angle = -angle;
	    kn::Matrix3x3d R;
	    R.setIdentity();
	    R[0][0] = R[1][1] = cos(angle);
	    R[0][1] = -sin(angle);
	    R[1][0] = -R[0][1];

	    // G
	    double f = (R*e2)[0];
	    kn::Matrix3x3d G;
	    G.setIdentity();
	    G[2][0] = -1.0 / f;

	    // center the result
	    kn::Matrix3x3d T2;
	    T2.setIdentity();

	    T2[0][2] = imageWidth2/2.0;
	    T2[1][2] = imageHeight2/2.0;

	    return T2*G*R*T;
	}



	/*
	* \cond
	* \brief computes the homography fo the second image
	* \param e2 : epipol in image2
	* \param F : fundamental matrix between image1 and image2
	* \param H2 : an homography that maps e1 to infinity
	* \return H0 : an homography that (epipolarly) matches H2
	*/
	kn::Matrix3x3d matchingHomographyH1(kn::Vector3d e2, const kn::Matrix3x3d &F, const kn::Matrix3x3d H2)
	{
	  // compute M
	  kn::Matrix3x3d eCross;
	  eCross.cross3x3(e2);
	  kn::Matrix3x3d M = eCross * F; // this form is rank 2

	  // make M rank 3 : multiple view geometry 2nd ed pp 256
	  kn::Matrix3x3d nonSingular;
	  kn::Vector3d v;
	  v.fill(1.0); // any arbitrary vector v
	  nonSingular.setRow(0,e2[0]*v);
	  nonSingular.setRow(1,e2[1]*v);
	  nonSingular.setRow(2,e2[2]*v);
	  M += nonSingular;
	  assert(kn::rank(M) > 2 && "else, choose another nonSingular matrix");

	  // H0
	  return H2 * M;
       }


       /*
	* \brief computes the homography fo the first image
	* \param F : fundamental matrix
	* \param e2 : epipol in image2
	* \param H2 : homography to rectify the second image (should be already computed)
	* \param pairList : a set of corresponding points between image1 and image2, used to minimize the rectified images distorsion
	* \return H1 : the homography to rectify image1
	*/
	kn::Matrix3x3d computeH1(const kn::Matrix3x3d &F,
				const kn::Vector3d &e2,
				const kn::Matrix3x3d &H2,
				const std::vector< std::pair<kn::Vector3d,kn::Vector3d> > &pairList)
	{
	    // H0
	    kn::Matrix3x3d H0 = matchingHomographyH1(e2,F,H2);

	    // Ha
	    kn::Vector<double> x(3);
	    kn::Matrix<double> A(pairList.size(),3);
	    kn::Vector<double> b(pairList.size());

	    kn::Vector3d xTmp;
	    for(unsigned int i=0; i<pairList.size(); ++i)
		{
		    // A
		    xTmp = H0*pairList[i].first;
		    xTmp.setHomogeneousNormalForm();
		    A.setRow(i,xTmp);

		    // b
		    xTmp = H2*pairList[i].second;
		    xTmp.setHomogeneousNormalForm();
		    b[i] = xTmp[0];
		}

	    kn::solveSystemSVD(A,x,b);
	    kn::Matrix3x3d Ha;
	    Ha.setIdentity();
	    Ha.setRow(0,x);

	    // final H1
	    return  Ha * H0;
	}



	/*
	* \brief computes the homography fo the first image
	* \param F : fundamental matrix
	* \param e2 : epipol in image2
	* \param H2 : homography to rectify the second image (should be already computed)
	* \param pairList : a set of corresponding points between image1 and image2, used to minimize the rectified images distorsion
	* \return H1 : the homography to rectify image1
	*/
	kn::Matrix3x3d computeH1stereoscopic(const kn::Matrix3x3d &F,
					     const kn::Vector3d &e2,
					     const kn::Matrix3x3d &H2,
					     const unsigned int imageWidth1,
					     const unsigned int imageHeight1)
	{
	  // H0
	  kn::Matrix3x3d H0 = matchingHomographyH1(e2,F,H2);

	  // vertical scale
	  kn::Vector3d tmpTop;
	  tmpTop[0] = imageWidth1/2.0;
	  tmpTop[1] = 0.0;
	  tmpTop[2] = 1.0;
	  tmpTop = H0 * tmpTop;
	  tmpTop.setHomogeneousNormalForm();

	  kn::Vector3d tmpBottom;
	  tmpBottom[0] = imageWidth1/2.0;
	  tmpBottom[1] = imageHeight1;
	  tmpBottom[2] = 1.0;
	  tmpBottom = H0 * tmpBottom;
	  tmpBottom.setHomogeneousNormalForm();

	  double verticalScale = (tmpBottom[1]-tmpTop[1]) / (double)imageHeight1; 

	  // horizontal skew and scale correction
	  std::vector< std::pair<kn::Vector3d,kn::Vector3d> > pairList;
	  kn::Vector3d x1,x2;
	  x1[2] = x2[2] = 1.0;

	  x1[0] = 0.0;
	  x1[1] = 0.0;
	  x2[0] = 0.0;
	  x2[1] = 0.0;
	  pairList.push_back(std::pair<kn::Vector3d,kn::Vector3d>(x1,x2));

	  x1[0] = imageWidth1;
	  x1[1] = 0.0;
	  x2[0] = imageWidth1 * verticalScale;
	  x2[1] = 0.0;
	  pairList.push_back(std::pair<kn::Vector3d,kn::Vector3d>(x1,x2));

	  x1[0] = imageWidth1;
	  x1[1] = imageHeight1;
	  x2[0] = imageWidth1 * verticalScale;
	  x2[1] = imageHeight1 * verticalScale;
	  pairList.push_back(std::pair<kn::Vector3d,kn::Vector3d>(x1,x2));

	  x1[0] = 0.0;
	  x1[1] = imageHeight1;
	  x2[0] = 0.0;
	  x2[1] = imageHeight1 * verticalScale;
	  pairList.push_back(std::pair<kn::Vector3d,kn::Vector3d>(x1,x2));

	  // Ha
	  kn::Vector<double> x(3);
	  kn::Matrix<double> A(pairList.size(),3);
	  kn::Vector<double> b(pairList.size());

	  kn::Vector3d xTmp;
	  for(unsigned int i=0; i<pairList.size(); ++i)
	  {
	    // A
	    xTmp = H0*pairList[i].first;
	    xTmp.setHomogeneousNormalForm();
	    A.setRow(i,xTmp);

	    // b
	    xTmp = pairList[i].second;
	    xTmp.setHomogeneousNormalForm();
	    b[i] = xTmp[0];
	  }

	  kn::solveSystemSVD(A,x,b);
	  kn::Matrix3x3d Ha;
	  Ha.setIdentity();
	  Ha.setRow(0,x);

	  // final H1
	  return  Ha * H0;
	}




      /*
	* \brief image rectification of 2 images from 2 homography matrices (already computed), the input/output/1/2 image don't have to have the same resolution, moreover, you can center an output image of (tx,ty) by seting H = T(x,y)*H, where T(x,y) is a 3x3 translation matrix.
	* \param inputImage1 : first input image to be rectifyed
	* \param inputImage2 : second input image to be rectifyed
	* \param outputImage1 : rectifyed image1
	* \param outputImage2 : rectifyed image2
	* \param H1 : the homography to rectify image1
	* \param H2 : the homography to rectify image2
	*/
	void imageRectify(const kn::Image<unsigned char> &inputImage1,
			  const kn::Image<unsigned char> &inputImage2,
			  kn::Image<unsigned char> &outputImage1,
			  kn::Image<unsigned char> &outputImage2,
			  const kn::Matrix3x3d &H1,
			  const kn::Matrix3x3d &H2){
	  
	    // apply the homography
	    kn::applyHomography(inputImage1,outputImage1,H1,false);
	    kn::applyHomography(inputImage2,outputImage2,H2,false); 
	}





	/*
	* End of Namespace
	*/
}


