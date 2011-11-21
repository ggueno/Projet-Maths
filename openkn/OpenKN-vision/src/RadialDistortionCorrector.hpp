/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * RadialDistortionCorrector.hpp created in 09 2011.
 * Mail : nozick@univ-mlv.fr
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_RADIAL_DISTORTION_CORRECTOR_HPP__
#define __OPENKN_RADIAL_DISTORTION_CORRECTOR_HPP__


/*
 * Internal Includes
 */
#include <OpenKN/math/Vector.hpp>
#include <OpenKN/image/ImageRGB.hpp>

/*
 * Namespace
 */
namespace kn{


// cf "division model" : Fitzgibbon, "Simultaneous linear estimation of multiple view geometry and lens distortion", CVPR 2001

/**
 * \brief Computes the corrected pixel position of an input distorded pixel position.
 * \param k : the correction factor, set -k for the inverse transformation (cf "division model" : Fitzgibbon, "Simultaneous linear estimation of multiple view geometry and lens distortion", CVPR 2001)
 * \param center : the center of the distortion (usually the center of the image)
 * \param iCorrected : the output pixel poision
 * \param jCorrected : the output pixel poision
 * \param iDistorded : the input pixel poision
 * \param jDistorded : the input pixel poision
 */
void radialDistortionCorrector(const double &k,
                               const kn::Vector<double> &center,
                               double &iCorrected, double &jCorrected, 
                               const double &iDistorded, const double &jDistorded);


/**
 * \brief Computes the corrected pixel position of an input distorded pixel position.
 * \param k : the correction factor, set -k for the inverse transformation (cf "division model" : Fitzgibbon, "Simultaneous linear estimation of multiple view geometry and lens distortion", CVPR 2001)
 * \param center : the center of the distortion (usually the center of the image)
 * \param correctedPoint : the output pixel (dimension is 2 or 3)
 * \param distordedPoint : the input pixel (dimension is 2 or 3)
 */
void radialDistortionCorrector(const double &k,
                               const kn::Vector<double> &center,
                               kn::Vector<double> &correctedPoint, 
                               const kn::Vector<double> &distordedPoint);


/**
 * \brief Apply the radial distortion of in input image, with anti-aliasing.
 * \param k : the correction factor, set -k for the inverse transformation (cf "division model" : Fitzgibbon, "Simultaneous linear estimation of multiple view geometry and lens distortion", CVPR 2001)
 * \param center : the center of the distortion (usually the center of the image)
 * \param distordedImage : the input distorded image
 * \param correctedImage : the ouput corrected image
 */
void radialDistortionCorrector(const double &k,
                               const kn::Vector<double> &center,
                               const kn::ImageRGB8u & distordedImage,
			                   kn::ImageRGB8u & correctedImage);
			                   
			                   
/**
 * \brief Apply the radial distortion of in input image, with anti-aliasing and a scale factor. 
 * \param k : the correction factor, set -k for the inverse transformation (cf "division model" : Fitzgibbon, "Simultaneous linear estimation of multiple view geometry and lens distortion", CVPR 2001)
 * \param center : the center of the distortion (usually the center of the image)
 * \param distordedImage : the input distorded image
 * \param correctedImage : the ouput corrected image
 * \param scale : scale factor, in addition to the correction
 */
void radialDistortionCorrector(const double &k,
                               const kn::Vector<double> &center,
                               const kn::ImageRGB8u & distordedImage,
			                   kn::ImageRGB8u & correctedImage,
			                   const double &scale);

   /*
    * End of Namespace
    */
}

/*
 * End of Anti-doublon
 */
#endif

