/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * Matrix.cpp created in 10 2008.
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
#include "MultiCam3D2DCorrespondences.hpp"

/*
 * Namespace
 */
namespace kn {

 	unsigned int MultiCam3D2DCorrespondences::add3DPointsSequence(std::vector<kn::Vector4d >& sequence){
		points3D.push_back(sequence);
		points2D.push_back(std::map < unsigned int, std::vector<kn::Vector3d > >());
		return points3D.size()-1;
	}


	void MultiCam3D2DCorrespondences::addCorresponding2DPointsSequence(unsigned int index3D, unsigned int indexCam, std::vector<kn::Vector3d >& sequence){
		if(index3D >= points3D.size())
			throw VisionException("Matching with unknown 3d points sequence");
		points2D[index3D][indexCam] = sequence;
	}

  /*
   * End of Namespace
   */
}

