/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * CameraCalibrationDLT.cpp created in 04 2010.
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
 * External Includes
 */



/*
 * Internal Includes
 */
#include "CameraCalibrationDLT.hpp"
#include "VisionException.hpp"
#include <OpenKN/math/Solver.hpp>


/*
 * Namespace
 */
namespace kn{


	/*
	* \brief compute the projection matrix P from a set of 3d-2d correspondances.
	* \param myList : a list of 3d-2d correspondances, in homogenous coordinates.
	*/
	kn::Matrix<double> cameraCalibrationDLT(const std::vector< std::pair<kn::Vector4d,kn::Vector3d> > & myList3d2d){
		// number of correspondances
		int nbElements = myList3d2d.size();
		if(nbElements < 6)
			throw VisionException("camera calibration : at least 6 correspondances 3d-2d are required","computeP");

		kn::Matrix<double> A(2*nbElements,12);
		kn::Vector<double> p(12);

		// data normalization
		kn::Matrix3x3<double> T;
		kn::Matrix3x3<double> Tinverse;
		kn::Matrix4x4<double> U;
		std::vector< std::pair<kn::Vector4d,kn::Vector3d > > normalizedList(myList3d2d);
		normalizationDLT(normalizedList,T,Tinverse,U);

		// build the linear system to solve
		makeSystemDLT(A,normalizedList);

		// solve the system
		kn::solveNullSystemSVD(A, p);

		// build P matrix from p vecrtor
		kn::Matrix<double> matP = kn::Matrix<double>(3,4,p,true);

		// data denormalization
		matP = Tinverse * matP * U;

		// finish
		return matP;
	}


	/*
	* \brief data normalization when computing the P matrix from a set of 3d-2d correspondances.
	* cf. Multiple View Geometry, Hartley Zisserman, Computation of the camera matrix P
	* \param myList : a list of 3d-2d correspondances, in homogenous coordinates, to be normalized.
	* \param T : transformation matrix (will be set by the function)
	* \param Tinverse : inverse of T, to be set by the function
	* \param U : transformation matrix (will be set by the function)s
	*/
	void normalizationDLT(std::vector< std::pair<kn::Vector4d,kn::Vector3d > > &myList,
			      kn::Matrix3x3<double> &T,
			      kn::Matrix3x3<double> &Tinverse,
			      kn::Matrix4x4<double> &U){

		double nbPoints = (double)(myList.size());

		// list : set normal form
		std::vector< std::pair<kn::Vector4d,kn::Vector3d > >::iterator it = myList.begin();
		while(it != myList.end()){
			it->first.setHomogeneousNormalForm();
			it->second.setHomogeneousNormalForm();
			++it;
		}

		// Compute average for each set of points
		kn::Vector3d averagePosList4d;
		kn::Vector2d averagePosList3d;
		averagePosList4d.fill(0.0);
		averagePosList3d.fill(0.0);
		it = myList.begin();
		while(it != myList.end()){
			averagePosList4d += Vector3d(Vectord(it->first).getUnhomogeneous());
			averagePosList3d += Vector2d(Vectord(it->second).getUnhomogeneous());
			++it;
		}

		averagePosList4d /= nbPoints;
		averagePosList3d /= nbPoints;

		// compute mean
		double meanList4d = 0.0;
		double meanList3d = 0.0;
		kn::Vector3d tmp;
		it = myList.begin();
		while(it != myList.end()){
			meanList4d += (Vector3d(Vectord(it->first).getUnhomogeneous()) - averagePosList4d).getNorm();
			meanList3d += (Vector2d(Vectord(it->second).getUnhomogeneous()) - averagePosList3d).getNorm();
			++it;
		}

		meanList4d /= nbPoints;
		meanList3d /= nbPoints;

		// scale to perform
		double scaleList4d = meanList4d / 1.73205081;		 // sqrt(3)
		double scaleList3d = meanList3d / 1.4142135623730950488; // sqrt(2)

		// T matrix
		T.setIdentity();
		T[0][0] = 1.0/scaleList3d;
		T[1][1] = 1.0/scaleList3d;
		T[0][2] = -averagePosList3d[0]/scaleList3d;
		T[1][2] = -averagePosList3d[1]/scaleList3d;

		// T inverse matrix
		Tinverse.setIdentity();
		Tinverse[0][0] = scaleList3d;
		Tinverse[1][1] = scaleList3d;
		Tinverse[0][2] = averagePosList3d[0];
		Tinverse[1][2] = averagePosList3d[1];

		// U matrix
		U.setIdentity();
		U[0][0] = 1.0/scaleList4d;
		U[1][1] = 1.0/scaleList4d;
		U[2][2] = 1.0/scaleList4d;
		U[0][3] = -averagePosList4d[0]/scaleList4d;
		U[1][3] = -averagePosList4d[1]/scaleList4d;
		U[2][3] = -averagePosList4d[2]/scaleList4d;

		// list normalization
		it = myList.begin();
		while(it != myList.end()){
			it->first = U * it->first;
			it->first.setHomogeneousNormalForm();
			it->second = T * it->second;
			it->second.setHomogeneousNormalForm();
			++it;
		}
	}


	/*
	* \brief Build the linear system to solve for the projection matrix computation. DLT : Direct Linear Transform.
	* \param A : the main matrix of the linear system. This matrix is filled in this method.
	* \param myList : a list of 3d-2d correspondances, in homogenous coordinates.
	*/
	void makeSystemDLT(kn::Matrix<double> &A,
			   const std::vector< std::pair<kn::Vector4d,kn::Vector3d > > &myList){
		int i = 0;
		std::vector< std::pair<kn::Vector4d,kn::Vector3d > >::const_iterator iter = myList.begin();

		while(iter != myList.end()){
			// 1st line
			A[2*i][0]=0.0;	A[2*i][1]=0.0;
			A[2*i][2]=0.0;	A[2*i][3]=0.0;

			A[2*i][4] = -iter->second[2] * iter->first[0];
			A[2*i][5] = -iter->second[2] * iter->first[1];	  // -pixel.wi * point.XiT
			A[2*i][6] = -iter->second[2] * iter->first[2];
			A[2*i][7] = -iter->second[2] * iter->first[3];

			A[2*i][8] =  iter->second[1] * iter->first[0];
			A[2*i][9] =  iter->second[1] * iter->first[1];	  // pixel.yi * point.XiT
			A[2*i][10]=  iter->second[1] * iter->first[2];
			A[2*i][11]=  iter->second[1] * iter->first[3];

			// 2nd line
			A[2*i+1][0] = iter->second[2] * iter->first[0];
			A[2*i+1][1] = iter->second[2] * iter->first[1];	  // pixel.wi * point.XiT
			A[2*i+1][2] = iter->second[2] * iter->first[2];
			A[2*i+1][3] = iter->second[2] * iter->first[3];

			A[2*i+1][4]=0.0;  A[2*i+1][5]=0.0;
			A[2*i+1][6]=0.0;  A[2*i+1][7]=0.0;

			A[2*i+1][8] = -iter->second[0] * iter->first[0];
			A[2*i+1][9] = -iter->second[0] * iter->first[1]; // pixel.xi*point.XiT
			A[2*i+1][10]= -iter->second[0] * iter->first[2];
			A[2*i+1][11]= -iter->second[0] * iter->first[3];

			// next
			++iter;
			++i;
		}
	}

	/*
	* End of Namespace
	*/
}
