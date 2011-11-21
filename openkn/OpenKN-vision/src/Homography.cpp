/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * Homography.cpp created in 12 2008.
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
#include "Homography.hpp"
#include "VisionException.hpp"

#include <OpenKN/math/Solver.hpp>
#include <OpenKN/math/Vector.hpp>
#include <OpenKN/math/InverseMatrix.hpp>

/*
 * Namespace
 */
namespace kn{

	// normalized DLT (Direct Linera Transformation)
	// cf multiple view geometry 1st edition p92
	static void normalize(std::vector< std::pair<kn::Vector3d,kn::Vector3d> >& points2d2d,
			      kn::Matrix3x3d& T1,
			      kn::Matrix3x3d& T2,
			      kn::Matrix3x3d& T2Inverse)
	{

		// Compute the average for each set of points
		kn::Vector2d averagePosList1;
		kn::Vector2d averagePosList2;
		averagePosList1.fill(0.0);
		averagePosList2.fill(0.0);
		std::vector< std::pair<kn::Vector3d,kn::Vector3d> >::iterator it = points2d2d.begin();
		while(it != points2d2d.end()) {
			averagePosList1 += Vector2d(Vectord(it->first).getUnhomogeneous());
			averagePosList2 += Vector2d(Vectord(it->second).getUnhomogeneous());
			++it;
		}

		averagePosList1 /= double(points2d2d.size());
		averagePosList2 /= double(points2d2d.size());

		// Compute the mean for each set of points
		double meanList1 = 0.0;
		double meanList2 = 0.0;
		kn::Vector2d tmp;
		it = points2d2d.begin();
		while(it != points2d2d.end()){
			tmp = Vector2d(Vectord(it->first).getUnhomogeneous()) - averagePosList1;
			meanList1 += tmp.getNorm();
			tmp = Vector2d(Vectord(it->second).getUnhomogeneous()) - averagePosList2;
			meanList2 += tmp.getNorm();
			++it;
		}
		meanList1 /= double(points2d2d.size());
		meanList2 /= double(points2d2d.size());

		double scaleList1 = meanList1 / 1.4142135623730950488;
		double scaleList2 = meanList2 / 1.4142135623730950488;

		// T matrix
		T1.setIdentity();
		T1[0][0] = 1.0/scaleList1;
		T1[1][1] = 1.0/scaleList1;
		T1[0][2] = -averagePosList1.x()/scaleList1;
		T1[1][2] = -averagePosList1.y()/scaleList1;

		// T' matrix
		T2.setIdentity();
		T2[0][0] = 1.0/scaleList2;
		T2[1][1] = 1.0/scaleList2;
		T2[0][2] = -averagePosList2.x()/scaleList2;
		T2[1][2] = -averagePosList2.y()/scaleList2;

		// T'^-1
		T2Inverse.setIdentity();
		T2Inverse[0][0] = scaleList2;
		T2Inverse[1][1] = scaleList2;
		T2Inverse[0][2] = averagePosList2.x();
		T2Inverse[1][2] = averagePosList2.y();

		// normalize the input data
		it = points2d2d.begin();
		while(it != points2d2d.end()){
			it->first = T1 * it->first;
			it->second = T2 * it->second;
			++it;
		}
	}


	// cf multiple view geometry 1st edition pp72
	static kn::Matrixd createSystem(const std::vector< std::pair<kn::Vector3d,kn::Vector3d> >& points2d2d)
	{
		kn::Matrixd m(points2d2d.size()*2, 9);
		std::vector< std::pair<kn::Vector3d,kn::Vector3d> >::const_iterator it = points2d2d.begin();
		unsigned int i = 0;
		while(it != points2d2d.end()){
			// first line
			m[2*i][0] = 0.0;
			m[2*i][1] = 0.0;
			m[2*i][2] = 0.0;

			m[2*i][3] = -it->second.z()*it->first.x();
			m[2*i][4] = -it->second.z()*it->first.y();
			m[2*i][5] = -it->second.z()*it->first.z();

			m[2*i][6] = it->second.y()*it->first.x();
			m[2*i][7] = it->second.y()*it->first.y();
			m[2*i][8] = it->second.y()*it->first.z();

			// second line
			m[2*i+1][0] = it->second.z()*it->first.x();
			m[2*i+1][1] = it->second.z()*it->first.y();
			m[2*i+1][2] = it->second.z()*it->first.z();

			m[2*i+1][3] = 0.0;
			m[2*i+1][4] = 0.0;
			m[2*i+1][5] = 0.0;

			m[2*i+1][6] = -it->second.x()*it->first.x();
			m[2*i+1][7] = -it->second.x()*it->first.y();
			m[2*i+1][8] = -it->second.x()*it->first.z();

			++it;
			++i;
		}
		return m;
	}


	kn::Matrix3x3d computeHomographyNormalized(const std::vector< std::pair<kn::Vector3d,kn::Vector3d> >& points2d2d)
	{
		if(points2d2d.size() < 4){
		  throw VisionException("at least 4 pixel correspondance required","computeHomographyNormalized");
		}

		// data normalization
		std::vector< std::pair<kn::Vector3d,kn::Vector3d> > ptmp(points2d2d);
		kn::Matrix3x3d T1(0.0);
		kn::Matrix3x3d T2(0.0);
		kn::Matrix3x3d T2Inverse(0.0);
		normalize(ptmp,T1,T2,T2Inverse);

		// H computation
		kn::Matrixd M = createSystem(ptmp);
		kn::Vectord h(9);
		kn::solveNullSystemSVD(M,h);
		kn::Matrix3x3d H(h);

		// data denormalization
		H = T2Inverse * H * T1;

		return H;
	    }


	kn::Matrix3x3d computeHomographyUnNormalized(const std::vector< std::pair<kn::Vector3d,kn::Vector3d> >& points2d2d)
	{
		if(points2d2d.size() < 4){
		    throw VisionException("at least 4 pixel correspondance required","computeHomographyUnNormalized");
		}

		// H computation
		kn::Matrixd A = createSystem(points2d2d);
		kn::Vectord h(9);
		kn::solveNullSystemSVD(A,h);

		return kn::Matrix3x3d(h);
	    }



	kn::Matrix3x3d computeHomography(const std::vector< std::pair<kn::Vector3d,kn::Vector3d> >& points2d2d, const bool& normalized)
	{
		if(normalized)
		    return computeHomographyNormalized(points2d2d);
		else
		    return computeHomographyUnNormalized(points2d2d);
	}




	void findBounds(int &xmin, int &xmax, int &ymin, int &ymax, const int w, const int h, const kn::Matrix3x3d &H)
	{
	  kn::Vector3d px1, px2;
	  px1[2] = 1.0;

	  // 1st corner
	  px1[0] = px1[1] = 0.0;
	  px2 = H * px1;
	  px2.setHomogeneousNormalForm();

	  xmin = xmax = px2[0];
	  ymin = ymax = px2[1];

	  // 2nd corner
	  px1[0] = -1.0 + (double)w;
	  px1[1] = 0.0;
	  px2 = H * px1;
	  px2.setHomogeneousNormalForm();
	  if(px2[0] < xmin) xmin = px2[0];
	  if(px2[0] > xmax) xmax = px2[0];
	  if(px2[1] < ymin) ymin = px2[1];
	  if(px2[1] > ymax) ymax = px2[1];

	  // 3rd corner
	  px1[0] = -1.0 + (double)w;
	  px1[1] = -1.0 + (double)h;
	  px2 = H * px1;
	  px2.setHomogeneousNormalForm();
	  if(px2[0] < xmin) xmin = px2[0];
	  if(px2[0] > xmax) xmax = px2[0];
	  if(px2[1] < ymin) ymin = px2[1];
	  if(px2[1] > ymax) ymax = px2[1];

	  // 4th corner
	  px1[0] = 0.0;
	  px1[1] = -1.0 + (double)h;
	  px2 = H * px1;
	  px2.setHomogeneousNormalForm();
	  if(px2[0] < xmin) xmin = px2[0];
	  if(px2[0] > xmax) xmax = px2[0];
	  if(px2[1] < ymin) ymin = px2[1];
	  if(px2[1] > ymax) ymax = px2[1];
	}


	kn::Matrix3x3d computeScaleHomography(const int xmin, const int xmax, const int ymin, const int ymax, int w2, int h2)
	{
	  // homogeneous scale (same on x and y axis)
	  double ratio1 = (xmax-xmin)/(double)(ymax-ymin);
	  double ratio2 = (double)w2/(double)h2;
	  double xmin2 = 0.0;
	  double ymin2 = 0.0;

	  // center the rectification
	  if(ratio1 > ratio2)
	  {
	    double adjust = h2 - (w2 / ratio1);
	    h2 -= adjust*0.5;
	    ymin2 = adjust*0.5;
	  }
	  else
	  {
	    double adjust = w2 - (h2 * ratio1);
	    w2 -= adjust*0.5;
	    xmin2 = adjust*0.5;
	  }

	  // compute the homography to scale the result of H in image2
	  std::vector< std::pair<kn::Vector3d,kn::Vector3d> > myList;
	  kn::Vector3d px1;
	  kn::Vector3d px2;
	  px1[2] = px2[2] = 1.0;

	  px1[0] = xmin;
	  px1[1] = ymin;
	  px2[0] = xmin2;
	  px2[1] = ymin2;
	  myList.push_back(std::pair<kn::Vector3d,kn::Vector3d>(px1,px2));

	  px1[0] = xmax;
	  px1[1] = ymin;
	  px2[0] = -1.0 + (double)w2;
	  px2[1] = ymin2;
	  myList.push_back(std::pair<kn::Vector3d,kn::Vector3d>(px1,px2));

	  px1[0] = xmax;
	  px1[1] = ymax;
	  px2[0] = -1.0 + (double)w2;
	  px2[1] = -1.0 + (double)h2;
	  myList.push_back(std::pair<kn::Vector3d,kn::Vector3d>(px1,px2));

	  px1[0] = xmin;
	  px1[1] = ymax;
	  px2[0] = xmin2;
	  px2[1] = -1.0 + (double)h2;
	  myList.push_back(std::pair<kn::Vector3d,kn::Vector3d>(px1,px2));

	  return  computeHomographyNormalized(myList);
	}


	void applyHomography(const kn::Image<unsigned char> &image1,
	                     kn::Image<unsigned char> &image2,
			     const kn::Matrix3x3d &H,
			     const bool scale)
	{
	  // check the image channel
	  if(image1.nbChannel() != image2.nbChannel())
	    throw VisionException("incompatible nb channel between the 2 images","applyHomography");

	  // inverse homography
	  kn::Matrix3x3d Hfinal(H);

	  // scale
	  if(scale)
	  {
	    // find the bounds
	    int xmin=0,xmax=0,ymin=0,ymax=0;
	    findBounds(xmin, xmax, ymin, ymax, image1.width(), image1.height(), H);

	    // compute the scaling homography
	    kn::Matrix3x3d Hscale = computeScaleHomography(xmin, xmax, ymin, ymax, image2.width(), image2.height());

	    // final homography
	    Hfinal = Hscale * H;
	  }

	  // inverse homography
	  Hfinal = kn::inverseMatrixSVD(Hfinal);

	  // apply the homography
	  kn::Vector3d px1;
	  kn::Vector3d px2;
	  px2[2] = 1.0;

	  for(unsigned int i=0; i<image2.width(); ++i)
	    for(unsigned int j=0; j<image2.height(); ++j)
		{
		  px2[0] = (double) i;
		  px2[1] = (double) j;
		  px1 = Hfinal * px2;
		  px1.setHomogeneousNormalForm();

#if 0
		  if(image1.contains((int)px1[0],(int)px1[1]))
		      for(unsigned int c=0; c<image1.nbChannel(); ++c)
			  image2(i,j)[c] = image1((unsigned int)px1[0],(unsigned int)px1[1])[c];
#else
		  image1.atBilinear(px1[0],px1[1],image2(i,j));
#endif
		}
	}


	/*
	 * End of Namespace
	 */
}
