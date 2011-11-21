/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * RelativeCameraPoseEstimation.cpp created in 01 2009.
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
#include <cassert>

#include <OpenKN/math/Determinant.hpp>
#include <OpenKN/math/InverseMatrix.hpp>
#include <OpenKN/math/MathException.hpp>
#include <OpenKN/math/Vector.hpp>


/*
 * Internal Includes
 */
#include "RelativeCameraPoseEstimation.hpp"
#include "Triangulation.hpp"
#include "VisionException.hpp"


/*
 * Namespace
 */
namespace kn {

  /*
   * Generate the four Projection matrix candidate from an Essential matrix.
   * From "Multiple View Geometry" 2nd Edition, Hartley Zisserman, page 259, Chapter 9 : Epipolar Geometry and the Fundamental Matrix. (9.6.2 : Extraction of cameras from essential matrix. 9.19)
   * \param E : Essential matrix
   * \param P1 : Projection matrix candidate \f$[UWV^T|t]\f$ is computed
   * \param P2 : Projection matrix candidate \f$[UWV^T|-t]\f$ is computed
   * \param P3 : Projection matrix candidate \f$[UW^TV^T|t]\f$ is computed
   * \param P4 : Projection matrix candidate \f$[UW^TV^T|-t]\f$ is computed
   * \throw MathException Pi is not a matrix of size 3x4
   */
  void Pcandidates(const kn::Matrix3x3d &E,
			 	   const kn::Matrix<double> &K2,
			       kn::Matrix<double> &P1,
      			   kn::Matrix<double> &P2,
      			   kn::Matrix<double> &P3,
      			   kn::Matrix<double> &P4){
 
 	// check the matrices size
 	assert(P1.rows()==3 && P1.columns()==4);
 	assert(P2.rows()==3 && P2.columns()==4);
 	assert(P3.rows()==3 && P3.columns()==4);
 	assert(P4.rows()==3 && P4.columns()==4);

    // Singular Value Decomposition (SVD) : E = U.W.V
    kn::Matrix<double> U(E);
    kn::Vector<double> w(3);
    kn::Matrix<double> V(E);
    kn::decompositionSVD(U,w,V);
    kn::sortSingularValuesSVD(U,w,V);

    // both U and V should have a positive determinant
    // if not the last column is multiplied by -1
    if(kn::determinant3x3(U) < 0) U.setColumn(2,-U.getColumn(2));
    if(kn::determinant3x3(V) < 0) V.setColumn(2,-V.getColumn(2));

    // W
    kn::Matrix3x3d W;
    W.fill(0.0);
    W[0][1] = -1.0;
    W[1][0] =  1.0;
    W[2][2] =  1.0;

    // M and t candidates
    kn::Vector3d t = U.getColumn(2);
    kn::Matrix3x3d R1 = U * W * V.getTranspose();
    kn::Matrix3x3d R2 = U * W.getTranspose() * V.getTranspose();

    // Compute the four projection matrix candidates
    // K2[R1|t]
    P1.setSubMatrix(0,0,R1);
    P1.setColumn(3,t);
    P1 = K2 * P1;
    
    // K2[R1|-t]
    P2.setSubMatrix(0,0,R1);
    P2.setColumn(3,-t);
    P2 = K2 * P2;
    
    // K2[R2|t]
    P3.setSubMatrix(0,0,R2);
    P3.setColumn(3,t);
    P3 = K2 * P3;
    
    // K2[R2|-t]
    P4.setSubMatrix(0,0,R2);
    P4.setColumn(3,-t);
    P4 = K2 * P4;
  }


  /*
   * \brief Select the correct projection Matrix between the four candidate matrices.
   * From "Multiple View Geometry" 2nd Edition, Hartley Zisserman, Chapter 9 : Epipolar Geometry and the Fundamental Matrix.
   * \param E : Essential matrix
   * \param P1 : Projection matrix candidate \f$[UWV^T|t]\f$
   * \param P2 : Projection matrix candidate \f$[UWV^T|-t]\f$
   * \param P3 : Projection matrix candidate \f$[UW^TV^T|t]\f$
   * \param P4 : Projection matrix candidate \f$[UW^TV^T|-t]\f$
   * \param K : Intrinsic matrix
   * \param point1 : Point from the image corresponding to cam1.
   * \param point2 : Point from the image corresponding to cam2 matching point1.
   * \return kn::Matrix<double> P : the only correct projection matrix between P1/P2/P3/P4
   */
  kn::Matrix<double> selectP(const kn::ProjectiveCamera &cam1,
  							 kn::Matrix<double> &P1,
					         kn::Matrix<double> &P2,
      						 kn::Matrix<double> &P3,
      						 kn::Matrix<double> &P4,
      						 const kn::Vector3d &point1,
      						 const kn::Vector3d &point2){

    // Projective camera for cam2, we try all candidates one by one until a candidate satisfies all the conditions.
    // The point qi triangulated from cam1 and cam2 must be in front of both cameas
    // Condition c1 : The point is in front of cam1
    // Condition c2 : The point is in front of cam2
    double c1,c2;

    // try P1
    kn::ProjectiveCamera cam2(P1);
    kn::Vector3d q1 = kn::linearTriangulation(cam1.P(),P1,point1,point2).getUnhomogeneous();
    c1 = q1 * cam1.principalRay();
    c2 = (q1-cam2.C().getUnhomogeneous()) * cam2.principalRay();
    if(c1>0. && c2>0.) return P1;

    // try P2
    cam2.updateP(P2);
    kn::Vector3d q2 = kn::linearTriangulation(cam1.P(),P2,point1,point2).getUnhomogeneous();
	c1 = q2 * cam1.principalRay();
	c2 = (q2-cam2.C().getUnhomogeneous()) * cam2.principalRay();
    if(c1>0. && c2>0.) return P2;

    //Update camP
    cam2.updateP(P3);
    kn::Vector3d q3 = kn::linearTriangulation(cam1.P(),P3,point1,point2).getUnhomogeneous();
	c1 = q3 * cam1.principalRay();
	c2 = (q3-cam2.C().getUnhomogeneous()) * cam2.principalRay();
    if(c1>0. && c2>0.) return P3;

    //Update camP
    cam2.updateP(P4);
    kn::Vector3d q4 = kn::linearTriangulation(cam1.P(),P4,point1,point2).getUnhomogeneous();
	c1 = q4 * cam1.principalRay();
	c2 = (q4-cam2.C().getUnhomogeneous()) * cam2.principalRay();
    if(c1>0. && c2>0.) return P4;

    //If not one of the 4 solution -> there is an error somewhere....
    throw VisionException("Error : Unable to find any valid solution for P2");
  }


  /*
   * \brief Computes a RT decomposition of a 3x3 Essential matrix E where R is a Rotation matrix and T a Translation.
   * From "Multiple View Geometry" 2nd Edition, Hartley Zisserman, Chapter 9 : Epipolar Geometry and the Fundamental Matrix.
   * (9.6.2 : Extraction of cameras from essential matrix.)
   * \param F : Fundamental matrix between cam1 and cam2.
   * \param K1 : Intrinsic parameter matrix (3x3) for cam1.
   * \param K2 : Intrinsic parameter matrix (3x3) for cam2.
   * \param point1 : image point correspondence from cam1.
   * \param point2 : image point correspondence from cam2.
   * \param cam1 : Resulting Projective camera \f$P1=K1[I|0]\f$
   * \param cam2 : Resulting Projective camera \f$P2=K2[R|-RC]=K2[R|t]\f$
   * \throw MathException K1 is not square matrix of size 3
   * \throw MathException K2 is not square matrix of size 3
   */
  void poseEstimationFromFundamental(const kn::Matrix3x3d &F,
  									 const kn::Matrix<double> K1, const kn::Matrix<double> K2,
  									 const kn::Vector3d &point1, const kn::Vector3d &point2,
  									 kn::ProjectiveCamera &cam1, kn::ProjectiveCamera &cam2){

	// check camera internal matrix size
    if(K1.rows()!=3 || K1.columns()!=3) throw MathException("K1 is not square matrix of size 3");
    if(K2.rows()!=3 || K2.columns()!=3) throw MathException("K2 is not square matrix of size 3");

    // compute the essential matrix
    kn::Matrix3x3d E = K2.getTranspose() * F * K1;

    // computes candidates camera matrices
    kn::Matrix<double> P1(3,4), P2(3,4), P3(3,4), P4(3,4);
    Pcandidates(E,K2,P1,P2,P3,P4);

    // Compute P1 for cam1 : P = K1[Id|0]
    kn::Matrix<double> P(3,4);
    P.setIdentity();
    P = K1*P;
    cam1.updateP(P);

    // select the correct P for cam2
    P = selectP(cam1, P1,P2,P3,P4, point1,point2);
    cam2.updateP(P);
  }
 

  /*
   * End of Namespace
   */
}
