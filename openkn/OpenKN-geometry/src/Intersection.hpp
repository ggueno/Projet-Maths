/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * Intersection.hpp created in 3 2009.
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
#ifndef __OPENKN_GEOMETRY__INTERSECTION_HPP__
#define __OPENKN_GEOMETRY__INTERSECTION_HPP__

/*
 * External Includes
 */
#include <utility>
#include <OpenKN/math/Vector3.hpp>

/*
 * Internal Includes
 */

/*
 * Namespace
 */
namespace kn{

  /**
   * \brief Intersect a triangle
   * If the returned distance is negative, no intersection was found.
   * \param pointA First point of the triangle
   * \param pointB Second point of the triangle
   * \param pointC Third point of the triangle 
   * \param rayDirection Direction of the intersection ray
   * \param rayOrigin Origin of the ray
   * \return Barycentric coordinates of the intersection and distance to the intersection
   */
	std::pair<kn::Vector2d,double> intersectTriangle(const kn::Vector3d & pointA, const kn::Vector3d & pointB, const kn::Vector3d & pointC, 
													 const kn::Vector3d & rayDirection ,const kn::Vector3d & rayOrigin);
  /**
   * \brief Intersect an Oriented Bounding Box
   * If the returned distance is negative, no intersection was found.
   * \param center Center of the bounding box
   * \param a Normalized side directions (x,y,z)
   * \param h Positive half-lengths
   * \param rayDirection Direction of the intersection ray
   * \param rayOrigin Origin of the ray
   * \return Poistion of the intersection and distance to the intersection
   */    
	std::pair<kn::Vector3d,double> intersectOBB(const kn::Vector3d & center, const kn::Vector3d  a[3], const kn::Vector3d & h,
												const kn::Vector3d  & rayDirection ,const kn::Vector3d & rayOrigin);


  /**
   * \brief Intersect a sphere
   * If the returned distance is negative, no intersection was found.
   * \param spherePosition position of the center of the sphere
   * \param radius radius of the sphere
   * \param rayDirection Direction of the intersection ray
   * \param rayOrigin Origin of the ray
   * \return Poistion of the intersection and distance to the intersection
   */    
	std::pair<kn::Vector3d, double> intersectSphere(const kn::Vector3d & spherePosition, double sphereRadius, 
													const kn::Vector3d & rayDirection ,const kn::Vector3d  & rayOrigin);

}

/*
 * End of Anti-doublon
 */
#endif
