/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * OpencvTools.cpp created in 04 2009.
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
 * Internal Includes
 */
#include "OpencvTools.hpp"


/*
 * Namespace
 */
namespace kn {

    template IplImage* convertToCV(Image<unsigned char>& in);
    template IplImage* convertToCV(Image<char>& in);
    template IplImage* convertToCV(Image<unsigned short int>& in);
    template IplImage* convertToCV(Image<short int>& in);
    template IplImage* convertToCV(Image<int>& in);
    template IplImage* convertToCV(Image<float>& in);
    template IplImage* convertToCV(Image<double>& in);

    template void convertFromCV(IplImage* in, Image<unsigned char>& out);
    template void convertFromCV(IplImage* in, Image<char>& out);
    template void convertFromCV(IplImage* in, Image<unsigned short int>& out);
    template void convertFromCV(IplImage* in, Image<short int>& out);
    template void convertFromCV(IplImage* in, Image<int>& out);
    template void convertFromCV(IplImage* in, Image<float>& out);
    template void convertFromCV(IplImage* in, Image<double>& out);

  /*
   * End of Namespace
   */
}

