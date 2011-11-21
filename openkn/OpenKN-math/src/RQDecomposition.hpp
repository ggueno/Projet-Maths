/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * RQDecomposition.hpp created in 01 2009.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-math.
 *
 * The OpenKraken-math is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-math is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_MATH__RQ_DECOMPOSITION_HPP__
#define __OPENKN_MATH__RQ_DECOMPOSITION_HPP__


/*
 * External Includes
 */
#include <cmath>

/*
 * Internal Includes
 */
#include "MathException.hpp"
#include "Matrix.hpp"
#include "Matrix3x3.hpp"


/*
 * Namespace
 */
namespace kn {


	/**
		* \brief Computes a QR decomposition of a nxn matrix A where R is a upper triangular nxn matrix and Q is a nxn orthogonal matrix. From "Multiple View Geometry" 2nd Edition, Hartley Zisserman, Appendix 4 : Matrix Properties and Decompositions, A4.1.2 : Householder matrices and QR decomposition. Note : this decomposition is not unique. For this fuction, the matrice template type should be float, double or long double.
		* \param A : nxn input matrix
		* \param R : nxn upper triangular matrix to be computed
		* \param Q : nxn orthogonal matrix to be computed
		* \throw MathException the input matrices are not square matrix
		* \throw MathException the input matrices does not have the same size
		*/
	template <class T>
		void qrDecomposition(const Matrix<T> &A, Matrix<T> &R, Matrix<T> &Q) {
			if(A.rows() != A.columns()) throw MathException("the input matrix is not a square matrix");
			if(R.rows() != R.columns()) throw MathException("the 'R' matrix is not a square matrix");
			if(Q.rows() != Q.columns()) throw MathException("the 'Q' matrix is not a square matrix");
			if(A.rows() != R.rows() || A.rows() != Q.rows()) throw MathException("input matrix does not have the same size");

			R=A;
			Q.setIdentity();
			Matrix<T> Qtmp(Q.rows());

			//During all this loop we consider Q to be transpose(Q)
			for(unsigned int i=0;i<A.columns()-1;i++){
				//v=first column of sub problem
				Vector<T,DynamicStorePolicy<double> > v = R.getColumn(i).getSubVector(i,R.rows()-i);
				//v = v +- (||v||,0,0,.....)
				//the sign is the same as Vo
				if(v.at(0)<0.0) {v.at(0) -= v.getNorm();}
				else		{v.at(0) += v.getNorm();}
				//v = v/||v||
				if(v.getNorm()<10e-30){
					throw MathException("Division by zero");
				}
				v.normalize();

				//we resolve the QR decomposition for the sub problem
				Matrix<T> Qn(v.size(),v.size());
				Qn.setIdentity();
				//Qn = Id - 2*tranpose(v)*v;
				for(unsigned int j=0;j<v.size();j++){
					for(unsigned int k=j;k<v.size();k++){
						Qn.at(j,k) -= 2*v.at(j)*v.at(k);
						Qn.at(k,j) = Qn.at(j,k);//symetric matrix
					}
				}
				Qn=-Qn;

				//Qtmp = Id or resolution of the sub problem in the bottom right corner of the matrix
				Qtmp.setIdentity();
				Qtmp.setSubMatrix(i,i,Qn);
				//transpose(Q) = Qn Qn-1 .... Q1
				Q = Qtmp*Q;

				//R = transpose(Q)*A
				R = Q*A;
				R.roundZero(10e-10);

			}
			Q.transpose();
		}


	/**
		* \brief Computes a RQ decomposition of a 3x3 matrix A where R is a upper triangular 3x3 matrix and Q is a 3x3 orthogonal matrix. From "Multiple View Geometry", Hartley Zisserman, Appendix 3 : Numerical algorithms, A3.1.1. Note : this decomposition is not unique and for computer vision applications, especially the internal parameters and rotation matrix extraction, the focal parameter (2 first elements on the R matrix diagonal) computed with this method can be negative. To ensure positive focal parameters, the user should check the decomposition with the rq3x3MakePositiveDiagonal function. For this fuction, the matrice template type should be float, double or long double.
		* \param A : 3x3 input matrix
		* \param R : 3x3 upper triangular 3x3 matrix to be computed
		* \param Q : 3x3 orthogonal matrix to be computed
		* \throw MathException the input matrices are not 3x3 matrices
		*/
	template <class T>
		void rqDecomposition3x3(const Matrix<T> &A, Matrix<T> &R, Matrix<T> &Q){
			if(A.rows() != 3 || A.columns() != 3) throw MathException("the input matrix is not a 3x3 matrix");
			if(R.rows() != 3 || R.columns() != 3) throw MathException("the 'R' matrix is not a 3x3 matrix");
			if(Q.rows() != 3 || Q.columns() != 3) throw MathException("the 'Q' matrix is not a 3x3 matrix");

			Matrix3x3<T> Qx;
			Matrix3x3<T> Qy;
			Matrix3x3<T> Qz;

			Qx.setIdentity();
			Qy.setIdentity();
			Qz.setIdentity();


			/////// R = A.Qx.Qy.Qz
			R = A;

			/////// Qx
			Qx[2][2] = -R[2][2]/sqrt(pow(R[2][1],2)+pow(R[2][2],2));
			Qx[1][1] = Qx[2][2];
			Qx[2][1] = R[2][1]/sqrt(pow(R[2][1],2)+pow(R[2][2],2));
			Qx[1][2] = -Qx[2][1];

			R = R*Qx;

			// Note : there are 2 equivalent solutions for "sqrt(pow(R[][],2)+pow(R[][],2));" correpsonding to the angle
			// "+ alpha" and "- 360° + alpha". The selected solution is "+sqrt(pow(R[][],2)+pow(R[][],2));".

			/////// Qy
			Qy[2][2] = R[2][2]/sqrt(pow(R[2][0],2)+pow(R[2][2],2));
			Qy[0][0] = Qy[2][2];
			Qy[0][2] = R[2][0]/sqrt(pow(R[2][0],2)+pow(R[2][2],2));
			Qy[2][0] = -Qy[0][2];

			R = R*Qy;

			/////// Qz
			Qz[0][0] = R[1][1]/sqrt(pow(R[1][1],2)+pow(R[1][0],2));
			Qz[1][1] = Qz[0][0];
			Qz[1][0] = -R[1][0]/sqrt(pow(R[1][1],2)+pow(R[1][0],2));
			Qz[0][1] = -Qz[1][0];

			R = R*Qz;

			/////// Q = QzT.QyT.QxT
			Qx.transpose();
			Qy.transpose();
			Qz.transpose();
			Q = Qz * Qy * Qx;
		}


	/**
		* \brief Update the 3x3 RQ decomposition such the diagonal elements of R are positive. The correction is performed by a modification on the Q matrix, which remains a 3x3 orthogonal matrix.
		* \param R : 3x3 upper triangular 3x3 matrix
		* \param Q : 3x3 orthogonal matrix
		* \throw MathException the input matrices are not 3x3 matrices
		*/
	template <class T>
		void rq3x3MakePositiveDiagonal(Matrix<T> &R, Matrix<T> &Q){
			if(R.rows() != 3 || R.columns() != 3) throw MathException("the 'R' matrix is not a 3x3 matrix");
			if(Q.rows() != 3 || Q.columns() != 3) throw MathException("the 'Q' matrix is not a 3x3 matrix");

			// variations pour garantir R[1][1] >= 0
			if(R[1][1] < 0)
			{
				for(int i=0; i<3; i++) R[i][1] *= -1.0;
				for(int i=0; i<3; i++) Q[1][i] *= -1.0;
			}

			// variations pour garantir R[0][0] >= 0
			if(R[0][0] < 0)
			{
				for(int i=0; i<3; i++) R[i][0] *= -1.0;
				for(int i=0; i<3; i++) Q[0][i] *= -1.0;
			}
		}

  /*
   * End of Namespace
   */
}

/*
 * End of Anti-doublon
 */
#endif







