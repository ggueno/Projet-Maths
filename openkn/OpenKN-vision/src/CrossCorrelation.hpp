/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * CrossCorrelation.hpp created in 01 2010.
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
#ifndef __OPENKN_VISION__CROSS_CORRELATION_HPP__
#define __OPENKN_VISION__CROSS_CORRELATION_HPP__

/*
 * External Includes
 */
#include <cmath>
#include <vector>

#include <OpenKN/image/Image.hpp>
#include <OpenKN/image/ImageGS.hpp>
#include <OpenKN/image/ImageConvolution.hpp>
#include <OpenKN/image/ConvolutionAverageOperator.hpp>

#include <OpenKN/math/Vector2.hpp>
#include <OpenKN/math/Vector3.hpp>
#include <OpenKN/math/Matrix.hpp>

/*
 * Internal Includes
 */
#include "VisionException.hpp"

namespace kn {

  /**
   * \brief Return a matching score for 2 image
   *
   * The score is normalized (-1 <= score <= 1)\n
   * Meaning of the score S :\n
   *   S =  1	  : Same image\n
   *   S near  1  : High correlation\n
   *   S near  0  : Image are not correlated\n
   *   S near -1  : High correlation with image negative\n
   *   S = -1	  : Image negative
   * \param image1	: Image
   * \param pt1		: Interest point for image1
   * \param image2	: Image
   * \param pt2		: Interest point for image2
   * \param windowSize	: Size of the correlation window
   * \param channel	: Channel of the images to consider
   * \return double score
   */
  double crossCorrelation(const Image<unsigned char> &image1,
      const Vector3d &pt1,
      const Image<unsigned char> &image2,
      const Vector3d &pt2,
      const Vector2i &windowSize,
      unsigned int channel=0);

  /**
   * \brief Return a matching score between 2 grayscale image
   *
   * The score is normalized (-1 <= score <= 1)\n
   * Meaning of the score S :\n
   *   S =  1	  : Same image\n
   *   S near  1  : High correlation\n
   *   S near  0  : Image are not correlated\n
   *   S near -1  : High correlation with image negative\n
   *   S = -1	  : Image negative
   * \param image1	: Image
   * \param pt1		: Interest point for image1
   * \param image2	: Image
   * \param pt2		: Interest point for image2
   * \param windowSize	: Size of the correlation window
   * \return double score
   */
  double crossCorrelationGS(const Image<unsigned char> &image1,
      const Vector3d &pt1,
      const Image<unsigned char> &image2,
      const Vector3d &pt2,
      const Vector2i &windowSize);

  /**
   * \brief Return a matching score between 2 RGB image
   *
   * The score is normalized (-1 <= score <= 1)\n
   * Meaning of the score S :\n
   *   S =  1	  : Same image\n
   *   S near  1  : High correlation\n
   *   S near  0  : Image are not correlated\n
   *   S near -1  : High correlation with image negative\n
   *   S = -1	  : Image negative
   * \param image1	: Image
   * \param pt1		: Interest point for image1
   * \param image2	: Image
   * \param pt2		: Interest point for image2
   * \param windowSize	: Size of the correlation window
   * \return double score
   */
  double crossCorrelationRGB(const Image<unsigned char> &image1,
      const Vector3d &pt1,
      const Image<unsigned char> &image2,
      const Vector3d &pt2,
      const Vector2i &windowSize);

  /**
   * \brief Return a matching score for 2 image (on the whole image)
   *
   * If images width or height are pair, we don't consider the last row/column\n
   * The score is normalized (-1 <= score <= 1)\n
   * Meaning of the score S :\n
   *   S =  1	  : Same image\n
   *   S near  1  : High correlation\n
   *   S near  0  : Image are not correlated\n
   *   S near -1  : High correlation with image negative\n
   *   S = -1	  : Image negative
   * \param image1	: Image
   * \param image2	: Image
   * \param channel     : Channel of the images to consider
   * \return double score
   * \throw VisionException Error : invalid channel value
   * \throw VisionException Error : Images must have the same size
   */
  double crossCorrelation(const Image<unsigned char> &image1,
      const Image<unsigned char> &image2,
      unsigned int channel=0);


  /**
   * \brief Correlate 2d points from two images and their list of interest points
   * \param image1	    : Image gray scale
   * \param list1	    : Interest points for image1
   * \param image2	    : Image gray scale
   * \param list2	    : Interest points for image2
   * \param windowSize	    : Size of the correlation window
   * \param minThreshold    : Minimal value used as a threshold for correlation score
   * \param nbChannel	    : 1 for GS correlation and 3 for RGB correlation
   * \return std::vector< std::pair<kn::Vector3d, kn::Vector3d> > a vector of correlated interest point pair
   * \throw VisionException Error : nbChannel must be 1 (GS) or 3 (RGB)
   * \throw VisionException Error : Image is not grayscale (1 channel)
   * \throw VisionException Error : Image are not RGB (3 channel)
   */
  std::vector< std::pair<kn::Vector3d, kn::Vector3d> > crossCorrelation(const kn::Image<unsigned char> &image1,
      std::vector<kn::Vector3d> &list1,
      const kn::Image<unsigned char> &image2,
      std::vector<kn::Vector3d> &list2,
      const kn::Vector2i &windowSize,
      double minThreshold=0.75,
      unsigned int nbChannel=1);

  /*
   * End of Namespace
   */
}

/*
 * End of Anti-doublon
 */
#endif

