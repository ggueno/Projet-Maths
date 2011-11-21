/*************************************************************************** \
* Copyright (C) by University Paris-Est - MISS team
* ImageRectification.hpp created in 04 2010.
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
* Anti-doublon
*/
#ifndef __OPENKN_VISION__IMAGE_RECTIFICATION_HPP__
#define __OPENKN_VISION__IMAGE_RECTIFICATION_HPP__

/*
* External Includes
*/
#include <vector>


/*
* Internal Includes
*/
#include <OpenKN/math/Matrix3x3.hpp>
#include <OpenKN/math/Vector.hpp>
#include <OpenKN/image/Image.hpp>


/*
* Namespace
*/
namespace kn{

      /**
	* \brief computes 2 homographies H1 and H2 designed for an image rectification of a pair of image, i.e. the epipolar lines are horizontal and aligned, this method uses a set of corresponding points between the 2 images to minimize the rectified images distorsion, note that the input images don't have to have the same resolution, this method is detailed in "Multiple view geometry", 2nd ed, page 307.
	* \param pairList : a set of corresponding points between image1 and image2, at least 8 points to compute the epipolar relation between the 2 images.
	* \param imageWidth2 : resolution of the image2
	* \param imageHeight2 : resolution of the image2
	* \param H1 : the homography to compute (to rectify image1)
	* \param H2 : the homography to compute (to rectify image2)
	* \return F : the fundamental matrix between image1 and image2
	* \throw VisionException too few corresponding points
	*/
        kn::Matrix3x3d imageRectification(const std::vector< std::pair<kn::Vector3d,kn::Vector3d> > &pairList,
					  const unsigned int imageWidth2,
					  const unsigned int imageHeight2,
					  kn::Matrix3x3d &H1,
					  kn::Matrix3x3d &H2);

	/**
	* \brief computes 2 homographies H1 and H2 designed for an image rectification of a pair of image, i.e. the epipolar lines are horizontal and aligned, this method uses a set of corresponding points between the 2 images to minimize the rectified images distorsion, note that the input images don't have to have the same resolution, this method is detailed in "Multiple view geometry", 2nd ed, page 307.
	* \param F : fundamental matrix between image1 and image2
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
					    kn::Matrix3x3d &H2);

	/**
	* \cond
	* \brief computes the homography fo the second image
	* \param e2 : epipol in image2
	* \param F : fundamental matrix between image1 and image2
	* \param H2 : an homography that maps e1 to infinity
	* \return H0 : an homography that (epipolarly) matches H2
	*/
	kn::Matrix3x3d matchingHomographyH1(kn::Vector3d e2, const kn::Matrix3x3d &F, const kn::Matrix3x3d H2);
	/// \endcond



	/**
	* \cond
	* \brief computes the homography fo the second image
	* \param e2 : epipol in image2
	* \param imageWidth2 : resolution of the image2
	* \param imageHeight2 : resolution of the image2
	* \return H2 : the homography to rectify image2
	*/
	kn::Matrix3x3d computeH2(kn::Vector3d e2, const unsigned int imageWidth2, const unsigned int imageHeight2);
	/// \endcond


      /**
	* \cond
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
				 const std::vector< std::pair<kn::Vector3d,kn::Vector3d> > &pairList);
	/// \endcond



      /**
      * \cond
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
					  const unsigned int imageHeight1);
      /// \endcond


      /**
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
			  const kn::Matrix3x3d &H2);




	 /*
	  * End of Namespace
	  */
}

/*
* End of Anti-doublon
*/
#endif

