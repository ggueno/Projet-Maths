/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * CameraCalibrationIAC.cpp created in 04 2010.
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
#include <CameraCalibrationIAC.hpp>
#include <VisionException.hpp>
#include <OpenKN/math/Solver.hpp>
#include <OpenKN/math/InverseMatrix.hpp>
#include <OpenKN/math/CholeskyDecomposition.hpp>


/*
 * Namespace
 */
namespace kn{

       /*
	* \brief compute internal parameter matrix K from a set of orthogonal vanishing points using the Image of the Absolute Conic (IAC)
	* \param myList3d2d : a list of pair of vanishing points associated to perpendicular lines, at least 3 correspondances.
	* \return the internal parameter matrix K (3x3)
	* \throw VisionException : too few vanishing point correspondances. 
	*/
	kn::Matrix3x3d cameraCalibrationIAC(const std::vector< std::pair<kn::Vector3d,kn::Vector3d > > & myList){

          if(myList.size() < 3)
	  	throw VisionException("too few vanishing point correspondances","cameraCalibrationIAC");

	  // compute w
	  kn::Matrix<double> W = computeAbsoluteConic(myList);

	  // Cholesky decoposition
	  kn::Matrix3x3d K = choleskyDecomposition(W).getTranspose();

	  // inverse w
	  K = kn::inverseMatrixSVD(K);
	  K = K / K[2][2];
	  K.roundZero(1.0e-10);
	  std::cout << "K\n" << K << std::endl;

	  return K;
	}


       /*
	* \brief compute the absolute conic from a set of orthogonal vanishing points, and assuming that : the pixels are square and the image skew is 0.
	* \param myList :  a list of pair of vanishing points associated to perpendicular lines, at least 3 correspondances.
	*/
	kn::Matrix<double> computeAbsoluteConic(const std::vector< std::pair<kn::Vector3d,kn::Vector3d > > &vanishingPoints){

	  // build A
	  kn::Matrix<double> A(vanishingPoints.size(),4);

	  // perpendicular vanishing points 
	  for(unsigned int i=0; i<vanishingPoints.size(); ++i)
	  	A.setRow(i,getSystemLine(vanishingPoints[i].first,vanishingPoints[i].second));

	  // compute the absolute conic
	  kn::Vector<double> w(4);
	  kn::solveNullSystemSVD(A,w);

	  // absolute conic matrix
	  kn::Matrix<double> W = w2W(w);

	  return W;
	}


	/*
	* \brief convert a vector to a matrix
	*/
	kn::Matrix<double> w2W(const kn::Vector<double> &w){

	  kn::Matrix<double> W(3,3);
	  W[0][0] = w[0];
	  W[1][0] = W[0][1] = 0.0;
	  W[1][1] = w[0];
	  W[2][0] = W[0][2] = w[1];
	  W[1][2] = W[2][1] = w[2];
	  W[2][2] = w[3];

	  return W;
	}


	/*
	* \brief creat a linear constraint (that already includes that the pixels are square and zero skew)
	*/
	kn::Vector<double> getSystemLine(const kn::Vector3d &v1, const kn::Vector3d &v2){
	  kn::Vector<double> a(4);

	  a[0] = v1[0]*v2[0] + v1[1]*v2[1];
	  a[1] = v1[0]*v2[2] + v1[2]*v2[0];
	  a[2] = v1[1]*v2[2] + v1[2]*v2[1];
	  a[3] = v1[2]*v2[2];

	  return a;
	}




	/*
	* End of Namespace
	*/
}
