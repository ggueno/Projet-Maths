/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * Harris.hpp created in 01 2010.
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
#ifndef __OPENKN_VISION__HARRIS_HPP__
#define __OPENKN_VISION__HARRIS_HPP__

/*
 * External Includes
 */
#include <cmath>
#include <vector>
#include <set>
#include <iterator>

#include <OpenKN/image/Image.hpp>
#include <OpenKN/image/ImageGS.hpp>
#include <OpenKN/image/ImageConvolution.hpp>
#include <OpenKN/image/ConvolutionAverageOperator.hpp>

#include <OpenKN/math/Vector3.hpp>
#include <OpenKN/math/Matrix.hpp>

/*
 * Internal Includes
 */
#include "VisionException.hpp"

namespace kn {


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
  std::vector<kn::Vector3d> harris(const kn::Image<unsigned char> &image,
      unsigned int nbPoint=0, unsigned int nbPartx=0,unsigned int nbParty=0,
      unsigned int gradConvSize=0, unsigned int gaussConvSize=0,
      const double threshold = 1.0e6, const double k= 0.04);

    /*
     * End of Namespace
     */
  }

  /*
   * End of Anti-doublon
   */
#endif
