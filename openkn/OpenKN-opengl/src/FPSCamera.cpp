/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * FPSCamera.cpp created in 2 2009.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKN-opengl.
 *
 * The OpenKN-opengl is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKN-opengl is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU LessOpenKNer General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Internal Includes
 */
#include "FPSCamera.hpp"

/*
 * External Includes
 */
#include <GL/gl.h>
#include <GL/glu.h>
#include <OpenKN/math/Quaternion.hpp>

/***************************************************************************
 *										CONSTRUCTEURS ET CONSTRUCTIONS
 ***************************************************************************/
using namespace kn;

FPSCamera::FPSCamera() {
	type_cam = CAM_TYPE_PERSPEC;
	position_cam = Vector3f(0.0,0.0,0.0);
	view_dir_cam = dir_init_cam = Vector3f(0.0,0.0,-1.0);
	top__dir_cam = top_init_cam = Vector3f(0.0,1.0,0.0);
	orientat_cam = Vector3f(0.0,0.0,0.0);
	computeModelview();
}

FPSCamera::FPSCamera(Vector3f pos_init,Vector3f dir_init,Vector3f top_init,Vector3f orient_init) {
	type_cam = CAM_TYPE_PERSPEC;
	reinitPosCam(pos_init,dir_init,top_init,orient_init);
}

FPSCamera::~FPSCamera() {
}

/***************************************************************************
 *										OPERATION GL PROJ / TRANSFO
 ***************************************************************************/

void FPSCamera::setProjectionGL() {
}

void FPSCamera::setTransfoGL() {
	gluLookAt(position_cam(0),position_cam(1),position_cam(2),
						position_cam(0)+view_dir_cam(0),position_cam(1)+view_dir_cam(1),position_cam(2)+view_dir_cam(2),
						top__dir_cam(0),top__dir_cam(1),top__dir_cam(2));
}

Matrix4x4f FPSCamera::getModelviewMatrix() {
	Matrix4x4f final_mv = modelview;
	Matrix4x4f trans_mv;
	Vector4f npos(-position_cam[0],-position_cam[1],-position_cam[2],1.0);
	trans_mv.setColumn(3,npos);
	return final_mv*trans_mv;
}

void FPSCamera::reinitPosCam(Vector3f pos_init,Vector3f dir_init,
															Vector3f top_init,
															Vector3f orient_init) {
	position_cam = pos_init;
	view_dir_cam = dir_init_cam = dir_init.normalize();
	top__dir_cam = top_init_cam = top_init.normalize();
	if ((dir_init_cam^top_init_cam).getNorm()<0.001) {
		throw OpenglException("Direction and up vectors are colinear !","FPSCamera::reinitPosCam");
	}
	// Reactualisation de top_init au cas où il ne soit pas orthogonal a view_init_dir
	//Vector3f right_vec = dir_init_cam^top_init_cam;
	//top__dir_cam = top_init_cam = right_vec^dir_init_cam;
	orientat_cam = orient_init;
	computeModelview();
}

/***************************************************************************
 *										OPERATION DE DEPLACEMENT
 ***************************************************************************/

void FPSCamera::stepFront(float step) {
	position_cam += view_dir_cam*step;
	reactuPosModelview();
}

void FPSCamera::stepBack(float step) {
	position_cam -= view_dir_cam*step;
	reactuPosModelview();
}

void FPSCamera::stepLeft(float step) {
	Vector3f left_vec = top__dir_cam^view_dir_cam;
	position_cam += left_vec*step;
	reactuPosModelview();
}

void FPSCamera::stepRight(float step) {
	Vector3f left_vec = top__dir_cam^view_dir_cam;
	position_cam -= left_vec*step;
	reactuPosModelview();
}

void FPSCamera::stepUp(float step) {
	position_cam += top__dir_cam*step;
	reactuPosModelview();
}

void FPSCamera::stepDown(float step) {
	position_cam -= top__dir_cam*step;
	reactuPosModelview();
}

void FPSCamera::lookRight(float angle) {
	orientat_cam(1) -= angle*M_PI/180.0;
	reactuOrientation();
}

void FPSCamera::lookLeft(float angle) {
	orientat_cam(1) += angle*M_PI/180.0;
	reactuOrientation();
}

void FPSCamera::lookUp(float angle) {
	orientat_cam(0) += angle*M_PI/180.0;
	reactuOrientation();
}

void FPSCamera::lookDown(float angle) {
	orientat_cam(0) -= angle*M_PI/180.0;
	reactuOrientation();
}

void FPSCamera::reactuPosModelview() {
/*	Vector4f npos(-position_cam[0],-position_cam[1],-position_cam[2],1.0);
	modelview.setRow(3,npos);*/
}

void FPSCamera::computeModelview() {
	reactuPosModelview();
	reactuOrientation();
}

void FPSCamera::reactuOrientation() {
	Matrix4x4f matt = Quaternionf(top_init_cam,orientat_cam(1)).getMatrix4();
	Vector3f right_vec = (dir_init_cam^top_init_cam).normalize();
	Vector4f right_vec_rot = matt*(right_vec.getHomogeneous(0.));
	modelview.setRow(0,right_vec_rot);
	Matrix4x4f matu = Quaternionf(Vector3f(right_vec_rot(0),right_vec_rot(1),right_vec_rot(2)),
																orientat_cam(0)).getMatrix4();
	Vector3f dir_init_rot = (matt*(dir_init_cam.getHomogeneous(0.))).getUnhomogeneous();
	Vector3f up_rot = (right_vec_rot.getUnhomogeneous())^dir_init_rot;
	top__dir_cam = (matu*up_rot.getHomogeneous(0.)).getUnhomogeneous();
	top__dir_cam.normalize();
	modelview.setRow(1,top__dir_cam.getHomogeneous(0.));
	view_dir_cam = (matu*matt*dir_init_cam.getHomogeneous(0.)).getUnhomogeneous();
	view_dir_cam.normalize();
	modelview.setRow(2,-view_dir_cam.getHomogeneous(0.));
}

extern std::ostream& kn::operator<<(std::ostream& os,const kn::FPSCamera & src) {
	os <<"**************************************"<<std::endl;
	os <<"          INFORMATIONS CAMERA         "<<std::endl;
	os <<" Position  : "<<src.position_cam<<std::endl;
	os <<" View dir  : "<<src.view_dir_cam<<std::endl;
	os <<" Top dir   : "<<src.top__dir_cam<<std::endl;
	os <<" Rot % x   : "<<src.orientat_cam(0)<<std::endl;
	os <<" Rot % y   : "<<src.orientat_cam(1)<<std::endl;
	os <<" Modelview : "<<std::endl<<src.modelview<<std::endl;
	os <<"**************************************"<<std::endl;
	return os;
}
