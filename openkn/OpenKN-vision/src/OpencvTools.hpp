/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * OpencvTools.hpp created in 04 2009.
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/



/*
 * Anti-doublon
 */
#ifndef __OPENKN_VISION__OPENCV_TOOLS_HPP__
#define __OPENKN_VISION__OPENCV_TOOLS_HPP__

/*
 * External Includes
 */
#include<opencv/cv.h>
#include<algorithm>

/*
 * Internal Includes
 */
#include <OpenKN/image/Image.hpp>
#include "VisionException.hpp"
/*
 * Namespace
 */
namespace kn {
	/**
	* \brief return the detph (nb of channels) of a type for openCV image
	* \return image depth (int) according to a template type
	* \author Ben
	*/
	template <typename T> int getCVDepth(){return -1;}
	template < > int getCVDepth<unsigned char>(){ return IPL_DEPTH_8U;}
	template < > int getCVDepth<char>(){ return IPL_DEPTH_8S;}
	template < > int getCVDepth<unsigned short int>(){ return IPL_DEPTH_16U;}
	template < > int getCVDepth<short int>(){ return IPL_DEPTH_16S;}
	template < > int getCVDepth<int>(){ return IPL_DEPTH_32S;}
	template < > int getCVDepth<float>(){ return IPL_DEPTH_32F;}
	template < > int getCVDepth<double>(){ return IPL_DEPTH_64F;}


     /**
      * \brief Convert an OpenKN Image in OpenCV IplImage format
      * \param in the OpenKN Image to convert
      * \return the converted OpenCV IplImage
      * \throw VisionException incompatible template
      * \author Ben
      */
      template <typename T>
      IplImage* convertToCV(Image<T>& in){
				int width = in.width();
				int height = in.height();
				int nChannels = in.nbChannel();
				int depth = getCVDepth<T>();
				if(depth == -1){
						throw VisionException("incompatible template","convertToCV");
				}
				IplImage* out = cvCreateImage(cvSize(width, height), depth, nChannels);
				T* datas;
				cvGetRawData(out, (uchar**)&datas, NULL, NULL);
				std::copy(in.begin(), in.end(), datas);
				return out;
      }

	/**
      * \brief Convert an OpenCV IplImage in OpenKN Image
      * \param in the OpenCV IplImage to convert
      * \param out the converted OpenKN Image (NEED TO BE 0 SIZED)
      * \author Ben
      */
      template <typename T>
      void convertFromCV(IplImage* in, Image<T>& out){
				int width = in->width;
				int height = in->height;
				int nbChannel = in->nChannels;
				T* datas;
				cvGetRawData(in, (uchar**)&datas, NULL, NULL);
				out = kn::Image<T>(width,height,nbChannel,datas);
      }



  /*
   * End of Namespace
   */
}


/*
 * End of Anti-doublon
 */
#endif



