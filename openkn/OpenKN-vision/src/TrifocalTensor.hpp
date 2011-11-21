/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * TrifocalTensor.hpp created in 08 2009.
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
#ifndef __OPENKN_TRIFOCAL_TENSOR_HPP__
#define __OPENKN_TRIFOCAL_TENSOR_HPP__


/*
 * External Includes
 */
#include <vector>


/*
 * Internal Includes
 */

#include <OpenKN/math/Vector.hpp>
#include <OpenKN/math/Vector3.hpp>
#include <OpenKN/math/Matrix3x3.hpp>



/*
 * Namespace
 */
namespace kn{


  /**
   * \brief computes a tensor from 3 sorted vector lists (image point correspondances under 3 views), at least 6 points; for more information, refer to "Multiple view geometry", Hartley & Zisserman.
   * \param T : a trifocal tensor represented by a Vector<double> with 27 elements : the first 9 elements correspond to the first matrix of the tensor, and so on ...
   * \param list1 : a sorted list of homogeneous vector3d (at least 6 elements)
   * \param list2 : a sorted list of homogeneous vector3d (at least 6 elements)
   * \param list3 : a sorted list of homogeneous vector3d (at least 6 elements)
   */
  void buildTensor(Vector<double> &T, 
		   const std::vector<Vector3d>& list1,
		   const std::vector<Vector3d>& list2,
		   const std::vector<Vector3d>& list3);


  /**
   * \brief computes x3 from x1 and x2 and the trifocal tensor; NOTE : this method is not the best method to perform a transfer since solving a linear system is required.
   * \param T : a trifocal tensor represented by a Vector<double> with 27 elements : the first 9 elements correspond to the first matrix of the tensor, and so on ...
   * \param v1 : image point from the 1st image (homogeneous vector3d)
   * \param v2 : image point from the 2nd image (homogeneous vector3d)
   * \return v3 : corresponding image point on the 3rd image (homogeneous vector3d)
   */
  Vector3d trifocalTensorTransfer12to3(const Vector<double> &T, const Vector3d &v1, const Vector3d &v2);


  /**
   * \brief computes x2 from x1 and x3 and the trifocal tensor; NOTE : this method is not the best method to perform a transfer since solving a linear system is required.
   * \param T : a trifocal tensor represented by a Vector<double> with 27 elements : the first 9 elements correspond to the first matrix of the tensor, and so on ...
   * \param v1 : image point from the 1st image (homogeneous vector3d)
   * \param v3 : image point from the 3rd image (homogeneous vector3d)
   * \return v2 : corresponding image point on the 2nd image (homogeneous vector3d)
   */
  Vector3d trifocalTensorTransfer13to2(const Vector<double> &T, const Vector3d &v1, const Vector3d &v3);


  /**
   * \brief computes x1 from x2 and x3 and the trifocal tensor; NOTE : this method is not the best method to perform a transfer since solving a linear system is required.
   * \param T : a trifocal tensor represented by a Vector<double> with 27 elements : the first 9 elements correspond to the first matrix of the tensor, and so on ...
   * \param v2 : image point from the 2nd image (homogeneous vector3d)
   * \param v3 : image point from the 3rd image (homogeneous vector3d)
   * \return v1 : corresponding image point on the 1st image (homogeneous vector3d)
   */
  Vector3d trifocalTensorTransfer23to1(const Vector<double> &T, const Vector3d &v2, const Vector3d &v3);


  /**
   * \brief computes the fondamental matrix between the view 2 and the view 1 from a trifocal tensor (multiple view geometry, 2nd ed, p. 275)
   * \param T : a trifocal tensor represented by a Vector<double> with 27 elements : the first 9 elements correspond to the first matrix of the tensor, and so on ...
   * \return F21 : fondamental matrix between the view 2 and the view 1
   */
  Matrix3x3d trifocalTensorF21(const Vector<double> &T);


  /**
   * \brief computes x3 from x1 and x2, the trifocal tensor and its corresponding fondamental matrix F21.
   * \param T : a trifocal tensor represented by a Vector<double> with 27 elements : the first 9 elements correspond to the first matrix of the tensor, and so on ...
   * \param F21 : 3x3 fondamental matrix between the view 2 and the view 1.
   * \param v1 : image point from the 1st image (homogeneous vector3d)
   * \param v2 : image point from the 2nd image (homogeneous vector3d)
   * \return v3 : corresponding image point on the 3rd image (homogeneous vector3d)
   */
  Vector3d trifocalTensorTransfer12to3(const Vector<double> &T, const Matrix3x3d &F21, const Vector3d &v1, const Vector3d &v2);












  /*
   * End of Namespace
   */
}

/*
 * End of Anti-doublon
 */
#endif
