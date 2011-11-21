/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * GeometryTools.hpp created in 10 2008.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-geometry.
 *
 * The OpenKraken-geometry is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-geometry is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_GEOMETRY__GEOMETRYTOOLS_HPP__
#define __OPENKN_GEOMETRY__GEOMETRYTOOLS_HPP__


/*
 * External Includes
 */ 
#include <OpenKN/math/Vector3.hpp>
#include <limits>

namespace kn{
    
  /*
   * Brief Max value of float
   */  
  const static float MAX_FLOAT = std::numeric_limits<float>::max();
  
  /*
   * Brief Min value of float
   */
  const static float MIN_FLOAT = std::numeric_limits<float>::min();

  /**
   * \brief convert barycentric coordinates of a triangle in world-space coordinates
   * \param pointA First point of the triangle
   * \param pointB Second point of the triangle
   * \param pointC Third point of the triangle 
   * \param bary Barycentric coordinates
   * \return World-space coordinates
   */
  template<typename T> 
  inline kn::Vector3<T> barycentricToPoint(const kn::Vector3<T> & pointA, const kn::Vector3<T> & pointB, const kn::Vector3<T> & pointC, 
									const kn::Vector2<T> & bary) {
	  return pointA * (1-bary.x()-bary.y()) + pointB*bary.x() + pointC*bary.y();
  }

}

#endif
