/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * TrifocalTensor.cpp created in 08 2009.
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
#include "TrifocalTensor.hpp"
#include <OpenKN/math/Matrix.hpp>
#include <OpenKN/math/Solver.hpp>


namespace kn{



  /*
   * \brief make the system to be solved to compute the tensor
   * \param A : the matrix to build, used to make a linear system which solution is the tensor
   * \param list1 : a sorted list of homogeneous vector3d (at least 6 elements)
   * \param list2 : a sorted list of homogeneous vector3d (at least 6 elements)
   * \param list3 : a sorted list of homogeneous vector3d (at least 6 elements)
   */
  /// \cond
  void makeSystem(Matrix<double> &A,
		   const std::vector<Vector3d>& list1,
		   const std::vector<Vector3d>& list2,
		   const std::vector<Vector3d>& list3){
  // init
  A.fill(0.0);
  unsigned int numLine = 0;

  // build the matrix
  for(unsigned int j=0; j<list1.size(); j++)
    for(unsigned int i=0; i<2; i++)
	for(unsigned int l=0; l<2; l++)
	  {
 	    for(unsigned int k=0; k<3; k++)
	    {
	   	    // T33k
		    A[numLine][k*9 + 8] = list1[j][k] * list2[j][i] * list3[j][l];

		    // Ti3k
		    A[numLine][k*9 + i*3 + 2] = - list1[j][k] * list3[j][l];

		    // T3lk
		    A[numLine][k*9 + 6 + l] = - list1[j][k] * list2[j][i];

		    // Tilk
		    A[numLine][k*9 + i*3 + l] = list1[j][k];
	    }

	    numLine++;
	  }
  }
 /// \endcond

  /*
   * \brief computes a tensor from 3 sorted vector lists (image point correspondances under 3 views), at least 6 points; for more information, refer to "Multiple view geometry", Hartley & Zisserman.
   * \param T : a trifocal tensor represented by a Vector<double> with 27 elements : the first 9 elements correspond to the first matrix of the tensor, and so on ...
   * \param list1 : a sorted list of homogeneous vector3d (at least 6 elements)
   * \param list2 : a sorted list of homogeneous vector3d (at least 6 elements)
   * \param list3 : a sorted list of homogeneous vector3d (at least 6 elements)
   */
  void buildTensor(Vector<double> &T,
		   const std::vector<Vector3d>& list1,
		   const std::vector<Vector3d>& list2,
		   const std::vector<Vector3d>& list3){
  // data size
  int nbPoints = list1.size();

  // computational data
  Matrix<double> A(4*nbPoints, 27); // (cf. multiple view geom. 1er edt pp381)

  // prepare the system to be solved
  makeSystem(A,list1,list2,list3);

  // solve the system
  solveNullSystemSVD(A,T);
  }


  /*
   * \brief return the 1d element index of a 3d element referencement
   */
  unsigned int tensorAccessor(const unsigned int i,
			      const unsigned int j,
			      const unsigned int k){
    return 9*i + 3*j + k;
  }


	/*
		* \brief computes x3 from x1 and x2 and the trifocal tensor; NOTE : this method is not the best method to perform a transfer since solving a linear system is required.
		* \param T : a trifocal tensor represented by a Vector<double> with 27 elements : the first 9 elements correspond to the first matrix of the tensor, and so on ...
		* \param v1 : image point from the 1st image (homogeneous vector3d)
		* \param v2 : image point from the 2nd image (homogeneous vector3d)
		* \return v3 : corresponding image point on the 3rd image (homogeneous vector3d)
		*/
	Vector3d trifocalTensorTransfer12to3(const Vector<double> &T, const Vector3d &v1, const Vector3d &v2){

		// solution vector
		Vector3d v3;

		// matrix to build
		Matrix<double> A(4,3);
		A.fill(0.0);

		// make the system
		unsigned int numLine = 0;

		for(unsigned int i=0; i<2; i++)
			for(unsigned int l=0; l<2; l++)
				{
					for(unsigned int k=0; k<3; k++)
						{
							// l = 0,1
							A[numLine][l] += - v1[k] * v2[i] * T[tensorAccessor(k,2,2)]   +   v1[k] * v2[2] * T[tensorAccessor(k,i,2)];

							// l = 3
							A[numLine][2] += - v1[k] * v2[2] * T[tensorAccessor(k,i,l)]   +   v1[k] * v2[i] * T[tensorAccessor(k,2,l)];
						}
					++numLine;
				}

		// solve the system
		kn::Vector<double> v3X(v3);
		solveNullSystemSVD(A,v3X);
		v3 = v3X;

		// return the solution
		v3.setHomogeneousNormalForm();
		return v3;
	}


	/**
		* \brief computes x2 from x1 and x3 and the trifocal tensor; NOTE : this method is not the best method to perform a transfer since solving a linear system is required.
		* \param T : a trifocal tensor represented by a Vector<double> with 27 elements : the first 9 elements correspond to the first matrix of the tensor, and so on ...
		* \param v1 : image point from the 1st image (homogeneous vector3d)
		* \param v3 : image point from the 3rd image (homogeneous vector3d)
		* \return v2 : corresponding image point on the 2nd image (homogeneous vector3d)
		*/
	Vector3d trifocalTensorTransfer13to2(const Vector<double> &T, const Vector3d &v1, const Vector3d &v3){
		// solution vector
		Vector3d v2;

		// matrix to build
		Matrix<double> A(4,3);
		A.fill(0.0);

		// make the system
		unsigned int numLine = 0;

		for(unsigned int i=0; i<2; i++)
			for(unsigned int l=0; l<2; l++)
				{
					for(unsigned int k=0; k<3; k++)
						{
							// i = 0,1
							A[numLine][i] += - v1[k] * v3[l] * T[tensorAccessor(k,2,2)]   +   v1[k] * v3[2] * T[tensorAccessor(k,2,l)];

							// i = 3
							A[numLine][2] += - v1[k] * v3[2] * T[tensorAccessor(k,i,l)]   +   v1[k] * v3[l] * T[tensorAccessor(k,i,2)];
						}
					++numLine;
				}

		// solve the system
		Vector<double> v2X(v2);
		solveNullSystemSVD(A,v2X);
		v2 = v2X;//solveNullSystemSVD(A,v2X);

		// return the solution
		v2.setHomogeneousNormalForm();
		return v2;
	}


	/**
		* \brief computes x1 from x2 and x3 and the trifocal tensor; NOTE : this method is not the best method to perform a transfer since solving a linear system is required.
		* \param T : a trifocal tensor represented by a Vector<double> with 27 elements : the first 9 elements correspond to the first matrix of the tensor, and so on ...
		* \param v2 : image point from the 2nd image (homogeneous vector3d)
		* \param v3 : image point from the 3rd image (homogeneous vector3d)
		* \return v1 : corresponding image point on the 1st image (homogeneous vector3d)
		*/
	Vector3d trifocalTensorTransfer23to1(const Vector<double> &T, const Vector3d &v2, const Vector3d &v3){

		// solution vector
		Vector3d v1;

		// matrix to build
		Matrix<double> A(4,3);
		A.fill(0.0);

		// make the system
		unsigned int numLine = 0;

		for(unsigned int i=0; i<2; i++)
			for(unsigned int l=0; l<2; l++)
				{
					for(unsigned int k=0; k<3; k++)
						{
							// k = 0,1,2
							A[numLine][k] +=   v2[i]*v3[2]*T[tensorAccessor(k,2,l)]
															- v2[2]*v3[2]*T[tensorAccessor(k,i,l)]
															- v2[i]*v3[l]*T[tensorAccessor(k,2,2)]
															+ v2[2]*v3[l]*T[tensorAccessor(k,i,2)];
						}
					++numLine;
				}

		// solve the system
		Vector<double> v1X(v1);
		solveNullSystemSVD(A,v1X);
		v1 = v1X;

		// return the solution
		v1.setHomogeneousNormalForm();
		return v1;
	}


	/*
		* \brief computes the fondamental matrix between the view 2 and the view 1 from a trifocal tensor (multiple view geometry, 2nd ed, p. 275)
		* \param T : a trifocal tensor represented by a Vector<double> with 27 elements : the first 9 elements correspond to the first matrix of the tensor, and so on ...
		* \return F21 : fondamental matrix between the view 2 and the view 1
		*/
	Matrix3x3d trifocalTensorF21(const Vector<double> &vectorT){

		// T1, T2 and T3
		std::vector<Matrix3x3d> T;
		T.push_back(Matrix3x3d(vectorT.begin()));
		T.push_back(Matrix3x3d(vectorT.begin())+9);
		T.push_back(Matrix3x3d(vectorT.begin())+18);

		// u1, u2 and u3
		Matrix3x3d U;
		for(unsigned int i=0; i<3; ++i){
			Vector<double> tmp(3);
			kn::solveNullSystemSVD(T[i].getTranspose(),tmp);
			U.setRow(i,tmp);
		}

		// v1, v2 and v3
		Matrix3x3d V;
		for(unsigned int i=0; i<3; ++i){
			Vector<double> tmp(3);
			solveNullSystemSVD(T[i],tmp);
			V.setColumn(i,tmp);
		}

		// find the epipole e'
		Vector<double> e2(3);
		solveNullSystemSVD(U,e2);

		// find the epipole e''
		Vector<double> e3(3);
		solveNullSystemSVD(V,e3);

		// retrieve fondamental matrix F21
		Matrix3x3d F21;
		Matrix3x3d e2Cross;
		e2Cross.cross3x3(Vector3d(e2));
		for(unsigned int i=0; i<3; ++i){
			F21.setColumn(i,(e2Cross * T[i] * e3));
		}

		return F21;
	}


  /*
   * \brief computes x3 from x1 and x2, the trifocal tensor and its corresponding fondamental matrix F21.
   * \param T : a trifocal tensor represented by a Vector<double> with 27 elements : the first 9 elements correspond to the first matrix of the tensor, and so on ...
   * \param F21 : 3x3 fondamental matrix between the view 2 and the view 1.
   * \param v1 : image point from the 1st image (homogeneous vector3d)
   * \param v2 : image point from the 2nd image (homogeneous vector3d)
   * \return v3 : corresponding image point on the 3rd image (homogeneous vector3d)
   */
  Vector3d trifocalTensorTransfer12to3(const Vector<double> &T, const Matrix3x3d &F21, const Vector3d &v1, const Vector3d &v2){
		// l'e = F21.x1
		Vector3d l2e( F21 * v1 );

		// homogenous form x2
		Vector3d x2(v2);
		x2.setHomogeneousNormalForm();

		// l2 : passing throug x2 and perpendicular to l2e
		Vector3d l2;
		l2[0] =  l2e[1];
		l2[1] = -l2e[0];
		l2[2] = v2[1]*l2e[0] - v2[0]*l2e[1];

		// x3 : transfered point
		Vector3d v3(0.0);
		for(unsigned int k=0; k<3; k++)
			for(unsigned int i=0; i<3; i++)
				for(unsigned int j=0; j<3; j++)
					v3[k] += v1[i] * l2[j] * T[tensorAccessor(i,j,k)];

		// return the solution
		v3.setHomogeneousNormalForm();
		return v3;
  }



  /*
   * End of Namespace
   */
}

