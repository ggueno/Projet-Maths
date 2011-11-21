/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * Homography.hpp created in 12 2008.
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
#ifndef __OPENKN_VISION__HOMOGRAPHY_HPP__
#define __OPENKN_VISION__HOMOGRAPHY_HPP__

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
	    * \brief Compute the normalized homography matrix H
	    * The data normalization provides a better accuracy of matrix values but the computation is slower; The homography is computed from a points2d2d list where every correspondance (a,a') satisfies a' = Ha; Thus, a is the input data and a' is the transformed point (both in homogeneous coordinates).
	    * \param points2d2d a vector of homogeneous vector3d pairs list (list of correspondance homogeneous vectors) (at least 4 correspondances)
	    * \return the homography matrix H
	    * \throw VisionException is number of pairs is incorrect
	    */
	    kn::Matrix3x3d computeHomographyNormalized(const std::vector< std::pair<kn::Vector3d,kn::Vector3d> >& points2d2d);

	  /**
	    * \brief Compute the unnormalized homography matrix H
	    * This approach skip the data normalization that causes a small loss of accuracy of matrix values but the computation is faster; The homography is computed from a points2d2d list where every correspondance (a,a') satisfies a' = Ha; Thus, a is the input data and a' is the transformed point (both in homogeneous coordinates).
	    * \param points2d2d a vector of homogeneous vector3d pairs list (list of correspondance homogeneous vectors)
	    * \return the homography matrix H
	    * \throw VisionException is number of pairs is incorrect
	    */
	    kn::Matrix3x3d computeHomographyUnNormalized(const std::vector< std::pair<kn::Vector3d,kn::Vector3d> >& points2d2d);

	  /**
	    * \brief Compute the homography matrix H
	    * points2d2d is given by (a,a') with a' = Ha; Thus, a is the input data and a' is the transformed point (both in homogeneous coordinates).
	    * \param points2d2d a vector of homogeneous vector3d pairs list (list of correspondance homogeneous vectors)
	    * \param normalized specifies if H is computed with data normalization or not
	    * \return the homography matrix H
	    */
	    kn::Matrix3x3d computeHomography(const std::vector< std::pair<kn::Vector3d,kn::Vector3d> >& points2d2d, 
					     const bool& normalized = true);
  
					     
	  /**
	    * \brief apply a homography H from image1 to image2 (not anti-aliased).
	    * \param image1 : source image
	    * \param image2 : target image to be filled, the resolution can be different from image1, but not the nb channel.
	    * \param H : homography matrix (3x3).
	    * \param scale : if true, the application will scale the resulting image to feet the target image size, if false, just perform the standard homography.
    	    * \throw VisionException incompatible image nb channel
	    */
	    void applyHomography(const kn::Image<unsigned char> &image1,
		                 kn::Image<unsigned char> &image2,
				 const kn::Matrix3x3d &H,
				 const bool scale = false);


	  /*
           * End of Namespace
	   */
}

/*
 * End of Anti-doublon
 */
#endif
