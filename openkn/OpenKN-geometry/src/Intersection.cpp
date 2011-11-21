/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * Intersection.cpp created in 3 2009.
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
 * External Includes
 */
#include <limits>

/*
 * Internal Includes
 */
#include <Intersection.hpp>

/*
 * Constants
 */
#define TRIANGLE_EPSILON 0.000001
#define OBB_EPSILON 1e-20

/*
 * Namespace
 */
namespace kn{

    /*
	 * Functions definitions
	 */

	std::pair<kn::Vector2d,double> intersectTriangle(const kn::Vector3d & pointA, const kn::Vector3d & pointB, const kn::Vector3d & pointC, 
													 const kn::Vector3d & rayDirection ,const kn::Vector3d & rayOrigin) {
		kn::Vector3d edge1;
		kn::Vector3d edge2;
		kn::Vector3d tvec;
		kn::Vector3d pvec;
		kn::Vector3d qvec;

		double det, inv_det;
		double u, t, v;

		/* find vectors for two edges sharing vert0 */
		edge1 = pointB - pointA;
		edge2 = pointC - pointA;
	
		/* begin calculating determinant - also used to calculate U parameter */
		pvec = rayDirection ^ edge2;
	
		/* if determinant is near zero, ray lies in plane of triangle */	
		det = edge1*pvec;

		if (det > -TRIANGLE_EPSILON && det < TRIANGLE_EPSILON)
			return std::pair<kn::Vector2d, double>(kn::Vector2d(),-1.0);
		inv_det = 1.0 / det;
   
		/* calculate distance from vert0 to ray origin */
		tvec = rayOrigin - pointA;

		/* calculate U parameter and test bounds */
		u = (tvec * pvec) * inv_det;
		if (u < 0.0 || u > 1.0)
			return std::pair<kn::Vector2d, double>(kn::Vector2d(),-1.0);

		/* prepare to test V parameter */
		qvec =  tvec^edge1;

		/* calculate V parameter and test bounds */
		v = (rayDirection*qvec) * inv_det;
		if (v < 0.0 || u + v > 1.0)
			return std::pair<kn::Vector2d, double>(kn::Vector2d(),-1.0);
   
		/* calculate t, ray intersects triangle */
		t = (edge2*qvec) * inv_det;
   
		return std::pair<kn::Vector2d, double>(kn::Vector2d(u,v),t);
	}

	std::pair<kn::Vector3d,double> intersectOBB(const kn::Vector3d & center, const kn::Vector3d  a[3], const kn::Vector3d & h,
												const kn::Vector3d  & rayDirection ,const kn::Vector3d & rayOrigin) {
		double tmin = std::numeric_limits<double>::min();
		double tmax = std::numeric_limits<double>::max();
		kn::Vector3d p = center - rayOrigin;
		
	
		for (int i=0; i < 3; i++) {
			double e = a[i]*p;
			double f = a[i]*rayDirection;

			if (fabs(f) > OBB_EPSILON) {
				double f1 = 1.0/f;
				double t1 = (e+h[i])*f1;
				double t2 = (e-h[i])*f1;			
				if (t1>t2) std::swap(t1,t2);
				if (t1>tmin) tmin = t1;
				if (t2 < tmax) tmax= t2;
				if (tmin > tmax) return std::pair<kn::Vector3d, double>(kn::Vector3d(0.0),-1.0);
				if (tmax < 0) return std::pair<kn::Vector3d, double>(kn::Vector3d(0.0),-1.0);
			}
			else if (-e - h[i]>0.0 || -e+h[i] <0.0) { return std::pair<kn::Vector3d, double>(kn::Vector3d(0.0),-1.0); }				
		}
	
		if (tmin>0)   return std::pair<kn::Vector3d, double>(rayOrigin+tmin*rayDirection,tmin);
		else    return std::pair<kn::Vector3d, double>(rayOrigin+tmax*rayDirection,tmax);
	}

	std::pair<kn::Vector3d, double> intersectSphere(const kn::Vector3d & spherePosition, double sphereRadius, 
													const kn::Vector3d & rayDirection ,const kn::Vector3d  & rayOrigin) {
		kn::Vector3d intersectionPosition;
		double t = -1.0;
		kn::Vector3d l = spherePosition - rayOrigin;
		double s = l*rayDirection;
		double l2 = l*l;
		double r2 = sphereRadius*sphereRadius;
	
		if (s<0 && l2 > r2)
			return std::pair<kn::Vector3d, double>(intersectionPosition,-1.0);
	
		double m2 = l2 - s*s;
		if (m2 > r2)
			return std::pair<kn::Vector3d, double>(intersectionPosition,-1.0);
	
		double q = sqrt(r2-m2);
	
		if (l2>r2) 
			t=s-q;
		else 
			t=s+q;

		return std::pair<kn::Vector3d, double>(rayOrigin+t*rayDirection,t);
	}



/*
 * End of Namespace
 */
}
