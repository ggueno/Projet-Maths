/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * Homography3d.cpp created in 02 2010.
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

#include <iterator>
#include <cassert>

/*
 * Internal Includes
 */
#include "Homography3d.hpp"
#include "VisionException.hpp"
#include <OpenKN/math/InverseMatrix.hpp>

/*
 * Namespace
 */
namespace kn{

  /**
   * \cond
   * \brief Compute system for Homography computation
   *
   * The homography is computed from a points3d3d list where every correspondance (a,a') satisfies \f$ a' = Ha\f$\n
   * Thus, a is the input data and a' is the transformed point (both in homogeneous coordinates), Note that we set the input vectors as rows and not column because of pseudo inverse purpose.
   * \param A1 matrix which will contains all the original points ( 1 on each rows )
   * \param A2 matrix which will contains all transformed points ( 1 on each rows )
   * \param points3d3d a vector of homogeneous vector4d pairs (at least 4 correspondances needed)
   * \throw VisionException at least 4 match required in point3d3d
   */
  void makeSystem(kn::Matrix<double> &A1, kn::Matrix<double> &A2,const std::vector< std::pair<kn::Vector4d,kn::Vector4d> >& points3d3d){
    //Assert correct size of systems's matrix
    assert(A1.rows() == points3d3d.size());
    assert(A2.rows() == points3d3d.size());

    // Compute A1 and A2
    std::vector< std::pair<kn::Vector4d,kn::Vector4d> >::const_iterator iter = points3d3d.begin();
    int i=0;
    while(iter != points3d3d.end()){
      A1.setRow(i,iter->first);
			A2.setRow(i,iter->second);
      ++i;
      ++iter;
    }
  }
  /// \endcond

  /**
   * \brief Compute the 3d homography matrix H
   *
   * The homography is computed from a points3d3d list where every correspondance (a,a') satisfies \f$ a' = Ha\f$\n
   * Thus, a is the input data and a' is the transformed point (both in homogeneous coordinates).\n
   * Consider we have respectively A and A' two matrices (4,n) with corresponding points \f$a_{i}\f$, and \f$a'_{i}\f$ on each column \n
   * \f$ HA=A' \Longleftrightarrow H=A'A^{-1}\f$\n
   * \param points3d3d a vector of homogeneous vector4d pairs (at least 4 correspondances needed)
   * \return the homography matrix4x4d H
   * \throw VisionException at least 4 match required in point3d3d
   */
  kn::Matrix4x4d computeHomography3d(const std::vector< std::pair<kn::Vector4d,kn::Vector4d> >& points3d3d){
    if(points3d3d.size()<4)
      throw VisionException("at least 4 match required in point3d3d");
    // System to resolve
    kn::Matrix<double> A1(points3d3d.size(),4);
    kn::Matrix<double> A2(points3d3d.size(),4);

    // System creation
    makeSystem(A1,A2,points3d3d);

    // A1 pseudo-inverse
    kn::Matrix<double> A1inv = kn::pseudoInverseMatrixSVD(A1);

    // compute H
    kn::Matrix4x4d H(A1inv*A2);
    H.transpose(); // we have to transpose H because we used tranposed matrices for A1 and A2. This is important for the pseudo inverse computation.

    return H;
  }

  /*
   * End of Namespace
   */
}
