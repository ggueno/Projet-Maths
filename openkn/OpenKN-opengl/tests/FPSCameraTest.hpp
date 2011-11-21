/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * OpenglExceptionTest.hpp created in 09 2008.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_OPENGL__FPSCAMERATEST_HPP__
#define __OPENKN_OPENGL__FPSCAMERATEST_HPP__

#define TEST_FPS_CAMERA_EPSILON			0.00001
/*
 * External Includes
 */
#include <iostream>
#include <string>
#include <cxxtest/TestSuite.h>

/*
 * Internal Includes
 */
#include <OpenKN/opengl/FPSCamera.hpp>

/*
 * Class definition
 */
using namespace kn;

class FPSCameraTest : public CxxTest::TestSuite {
public:

	static float mat_config1[16];
	static float mat_config2[16];
	static float mat_config3[16];
	

	void toolFloatCompWithDelta(int nb_float,float* op1,float* op2,float delta) {
		for(unsigned int i=0;i<nb_float;i++) {
			TS_ASSERT_DELTA(op1[i],op2[i],delta);
		}
	}
	
	void testConstructor( void ) {
		FPSCamera cam;
		float nul[3] = {0.0,0.0,0.0};
		float vue[3] = {0.0,0.0,-1.0};
		float top[3] = {0.0,1.0,0.0};
		toolFloatCompWithDelta(3,(float*)cam.position_cam.begin(),nul,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.orientat_cam.begin(),nul,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.view_dir_cam.begin(),vue,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.dir_init_cam.begin(),vue,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.top__dir_cam.begin(),top,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.top_init_cam.begin(),top,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(16,(float*)cam.getModelviewMatrix().begin(),mat_config1,TEST_FPS_CAMERA_EPSILON);
	}
	
	void testConstructorWithInitialisation( void ) {
		float pos[3] = {3.0,3.0,3.0};
		float orientation[3] = {0.0,0.0,0.0};
		float vue[3] = {-0.57735 , -0.57735 , -0.57735};
		float top[3] = {0.0,1.0,0.0};
		float top_mod[3] =  {-0.408248 , 0.816497 , -0.408248};
		FPSCamera cam(Vector3f(3.0,3.0,3.0),Vector3f(-1.0,-1.0,-1.0),
									Vector3f(0.0,1.0,0.0),Vector3f(0.0,0.0,0.0));
		toolFloatCompWithDelta(3,(float*)cam.position_cam.begin(),pos,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.orientat_cam.begin(),orientation,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.dir_init_cam.begin(),vue,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.view_dir_cam.begin(),vue,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.top__dir_cam.begin(),top_mod,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.top_init_cam.begin(),top,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(16,(float*)cam.getModelviewMatrix().begin(),mat_config2,TEST_FPS_CAMERA_EPSILON);
	}

	//testSetProjectionGL();		// A PRIORI NE SERA PAS IMPLEMENTE

	//testSetTransfoGL();		// DEPRECATED

	void testReinitPosCam() {
		float pos[3] = {3.0,3.0,3.0};
		float orientation[3] = {-M_PI/4.,M_PI/4.,0.0};
		float vue[3] = {0.0 , 0.0 , -1.0};
		float top[3] = {0.0,1.0,0.0};
		float vue_mod[3] = {-0.5 , -0.707107 , -0.5};
		float top_mod[3] =  {-0.5 , 0.707107 , -0.5};
		FPSCamera cam;
		toolFloatCompWithDelta(16,(float*)cam.getModelviewMatrix().begin(),mat_config1,TEST_FPS_CAMERA_EPSILON);
		cam.reinitPosCam(Vector3f(3.0,3.0,3.0),Vector3f(0.0,0.0,-1.0),
										 Vector3f(0.0,1.0,0.0),Vector3f(-M_PI/4.,M_PI/4.,0.0));
		toolFloatCompWithDelta(3,(float*)cam.position_cam.begin(),pos,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.orientat_cam.begin(),orientation,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.dir_init_cam.begin(),vue,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.view_dir_cam.begin(),vue_mod,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.top_init_cam.begin(),top,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.top__dir_cam.begin(),top_mod,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(16,(float*)cam.getModelviewMatrix().begin(),mat_config3,TEST_FPS_CAMERA_EPSILON);
	}

	

	void testStepFront() {
		FPSCamera cam;
		float the_step = 1.25;
		cam.stepFront(the_step);
		TS_ASSERT_EQUALS(cam.position_cam[2],-1.25);
	}
	
	void testStepBack() {
		FPSCamera cam;
		float the_step = 1.25;
		cam.stepBack(the_step);
		TS_ASSERT_EQUALS(cam.position_cam[2],1.25);
	}
	
	void testStepLeft() {
		FPSCamera cam;
		float the_step = 1.25;
		cam.stepLeft(the_step);
		TS_ASSERT_EQUALS(cam.position_cam[0],-1.25);
	}
	
	void testStepRight() {
		FPSCamera cam;
		float the_step = 1.25;
		cam.stepRight(the_step);
		TS_ASSERT_EQUALS(cam.position_cam[0],1.25);
	}
	
	void testStepUp() {
		FPSCamera cam;
		float the_step = 1.25;
		cam.stepUp(the_step);
		TS_ASSERT_EQUALS(cam.position_cam[1],1.25);
	}
	
	void testStepDown() {
		FPSCamera cam;
		float the_step = 1.25;
		cam.stepDown(the_step);
		TS_ASSERT_EQUALS(cam.position_cam[1],-1.25);
	}
	
	void testLookRight() {
		FPSCamera cam;
		float vue[3] = {0.5 , 0 , -0.866025};
		float angle_step = 30.0;
		cam.lookRight(angle_step);
		TS_ASSERT_DELTA(-0.523599,cam.orientat_cam[1],TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.view_dir_cam.begin(),vue,TEST_FPS_CAMERA_EPSILON);
	}
	
	void testLookLeft() {
		FPSCamera cam;
		float vue[3] = {-0.5 , 0 , -0.866025};
		float angle_step = 30.0;
		cam.lookLeft(angle_step);
		TS_ASSERT_DELTA(0.523599,cam.orientat_cam[1],TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.view_dir_cam.begin(),vue,TEST_FPS_CAMERA_EPSILON);
	}
	
	void testLookUp() {
		FPSCamera cam;
		float vue[3] = {0 , 0.5 , -0.866025};
		float top[3] = {0 , 0.866025 , 0.5};
		float angle_step = 30.0;
		cam.lookUp(angle_step);
		TS_ASSERT_DELTA(0.523599,cam.orientat_cam[0],TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.view_dir_cam.begin(),vue,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.top__dir_cam.begin(),top,TEST_FPS_CAMERA_EPSILON);
	}
	
	void testLookDown() {
		FPSCamera cam;
		float vue[3] = {0 , -0.5 , -0.866025};
		float top[3] = {0 , 0.866025 , -0.5};
		float angle_step = 30.0;
		cam.lookDown(angle_step);
		TS_ASSERT_DELTA(-0.523599,cam.orientat_cam[0],TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.view_dir_cam.begin(),vue,TEST_FPS_CAMERA_EPSILON);
		toolFloatCompWithDelta(3,(float*)cam.top__dir_cam.begin(),top,TEST_FPS_CAMERA_EPSILON);
	}

	void testGetModelviewMatrix() {
		float pos[3] = {3.0,3.0,3.0};
		float orientation[3] = {0.0,0.0,0.0};
		float vue[3] = {-0.57735 , -0.57735 , -0.57735};
		float top[3] = {0.0,1.0,0.0};
		float top_mod[3] =  {-0.408248 , 0.816497 , -0.408248};
		FPSCamera cam(Vector3f(3.0,3.0,3.0),Vector3f(-1.0,-1.0,-1.0),
									Vector3f(0.0,1.0,0.0),Vector3f(0.0,0.0,0.0));
		toolFloatCompWithDelta(16,(float*)cam.getModelviewMatrix().begin(),mat_config2,TEST_FPS_CAMERA_EPSILON);
	}

};

float FPSCameraTest::mat_config1[16] = {1.0,		0.0,	0.0,	0,
																				0.0,		1.0,	0.0,	0,
																				0.0,		0.0,	1.0,	0,
																				0.0,		0.0,	0.0,	1};
float FPSCameraTest::mat_config2[16] = {0.707107,		0.0,			-0.707107,	0.0,
																				-0.408248,	0.816497,	-0.408248,	0.0,
																				0.57735,		0.57735,	0.57735,		-5.19615,
																				0.0,				0.0,			0.0,				1.0};

float FPSCameraTest::mat_config3[16] = {0.707107,		0.0,			-0.707107,	0.0,
																				-0.5,				0.707107,	-0.5,				0.87868,
																				0.5,				0.707107,	0.5,				-5.12132,
																				0.0,				0.0,			0.0,				1.0};

/*
 * End of Anti-doublon
 */
#endif
