/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * Triangulation.cpp created in 12 2008.
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
#include "Triangulation.hpp"
#include "VisionException.hpp"
#include <OpenKN/math/Solver.hpp>
#include <OpenKN/math/Vector.hpp>
#include <OpenKN/math/Matrix.hpp>

/*
 * Namespace
 */
namespace kn{
	/*
	 * \brief Compute the triangulation from the pixel x1 in camera P1 and the pixel x2 from camera P2, cf : Multiple view geometry (2nd ed): cahpter 12.2 page 312
	 * \param P1 : a 3x4 projection matrix
	 * \param P2 : a 3x4 projection matrix
	 * \param x1 : a 3-vector in homogeneous coordinates (non-ideal points)
	 * \param x2 : a 3-vector in homogeneous coordinates (non-ideal points)
	 * \return the triangulated point (4-vector in homogeneous coordinates)
	 * \throw VisionException invalite matrix size
	 */
	kn::Vector4d linearTriangulation(const kn::Matrix<double>  & P1,
																						const kn::Matrix<double>  & P2,
																						const kn::Vector3d & x1,
																						const kn::Vector3d & x2){
		if(P1.rows() != 3 && P1.columns() != 4)
			throw VisionException("P1 is not a 3x4 Matrix<double>");

		if(P2.rows() != 3 && P2.columns() != 4)
			throw VisionException("P2 is not a 3x4 Matrix<double>");

		kn::Vector2d unhomogeneousX1(x1.getUnhomogeneous());
		kn::Vector2d unhomogeneousX2(x2.getUnhomogeneous());

		int nbPoints = 2;
		kn::Matrix<double> A(2*nbPoints,4);

		// build A matrix
		// point x1
		// x.P3-P1
		A[0][0] = unhomogeneousX1[0]*P1[2][0] - P1[0][0];
		A[0][1] = unhomogeneousX1[0]*P1[2][1] - P1[0][1];
		A[0][2] = unhomogeneousX1[0]*P1[2][2] - P1[0][2];
		A[0][3] = unhomogeneousX1[0]*P1[2][3] - P1[0][3];
		// y.P3-P2
		A[1][0] = unhomogeneousX1[1]*P1[2][0] - P1[1][0];
		A[1][1] = unhomogeneousX1[1]*P1[2][1] - P1[1][1];
		A[1][2] = unhomogeneousX1[1]*P1[2][2] - P1[1][2];
		A[1][3] = unhomogeneousX1[1]*P1[2][3] - P1[1][3];

		// point x2
		// x.P3-P1
		A[2][0] = unhomogeneousX2[0]*P2[2][0] - P2[0][0];
		A[2][1] = unhomogeneousX2[0]*P2[2][1] - P2[0][1];
		A[2][2] = unhomogeneousX2[0]*P2[2][2] - P2[0][2];
		A[2][3] = unhomogeneousX2[0]*P2[2][3] - P2[0][3];
		// y.P3-P2
		A[3][0] = unhomogeneousX2[1]*P2[2][0] - P2[1][0];
		A[3][1] = unhomogeneousX2[1]*P2[2][1] - P2[1][1];
		A[3][2] = unhomogeneousX2[1]*P2[2][2] - P2[1][2];
		A[3][3] = unhomogeneousX2[1]*P2[2][3] - P2[1][3];

		kn::Vector<double> X;
		kn::solveNullSystemSVD(A,X);
		X.setHomogeneousNormalForm();

		kn::Vector4d Xfinal;
		Xfinal[0] = X[0]; Xfinal[1] = X[1]; Xfinal[2] = X[2]; Xfinal[3] = X[3];

		return Xfinal;
	}


	/*
	 * \brief Compute the triangulation from n Cameras (n>1), cf : Multiple view geometry (2nd ed): cahpter 12.2 page 312
	 * \param P : a list of 3x4 projection matrices
	 * \param x : a list of pixel (3-vector in homogeneous coordinates)
	 * \return the triangulated point (4-vector in homogeneous coordinates).
	 * \throw VisionException invalite matrix size
	 */
	kn::Vector4d linearTriangulation(const std::vector<kn::Matrix<double> >   & P,
																						const std::vector<kn::Vector3d >  & x) {
		if(P.size() != x.size())
			throw VisionException("P list and x list don't have the same number of elements");

		for(unsigned int i=0; i<P.size(); ++i)
			if(P[i].rows() != 3 && P[i].columns() != 4)
				throw VisionException("one of the P matrix is not a 3x4 Matrix<double>");

		int nbPoints = P.size();
		kn::Matrix<double> A(2*nbPoints,4);

		// build A matrix
		for(unsigned int i=0; i<P.size(); ++i){  // for every correspondance
			double unhomogeneousX = x[i].getUnhomogeneous()[0];
			double unhomogeneousY = x[i].getUnhomogeneous()[1];

			// x.P3-P1
			A[2*i][0]   = unhomogeneousX*P[i][2][0] - P[i][0][0];
			A[2*i][1]   = unhomogeneousX*P[i][2][1] - P[i][0][1];
			A[2*i][2]   = unhomogeneousX*P[i][2][2] - P[i][0][2];
			A[2*i][3]   = unhomogeneousX*P[i][2][3] - P[i][0][3];
			// y.P3-P2
			A[2*i+1][0] = unhomogeneousY*P[i][2][0] - P[i][1][0];
			A[2*i+1][1] = unhomogeneousY*P[i][2][1] - P[i][1][1];
			A[2*i+1][2] = unhomogeneousY*P[i][2][2] - P[i][1][2];
			A[2*i+1][3] = unhomogeneousY*P[i][2][3] - P[i][1][3];
		}

		kn::Vector<double> X;
		kn::solveNullSystemSVD(A,X);
		X.setHomogeneousNormalForm();

		kn::Vector4d Xfinal;
		Xfinal[0] = X[0]; Xfinal[1] = X[1]; Xfinal[2] = X[2]; Xfinal[3] = X[3];

		return Xfinal;
	}


	/*
	 * End of Namespace
	 */
}
