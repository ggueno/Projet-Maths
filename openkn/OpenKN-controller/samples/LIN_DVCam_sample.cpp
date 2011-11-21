/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * LIN_DVCam_sample.hpp created in 03 2009.
 * Mail : biri@univ-mlv.fr					  
 *													   
 * This file is part of the OpenKraken-controller.
 *
 * The OpenKraken-controller is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-controller is distributed in the hope that it will be useful,
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
#include <iostream>
#include <string>
#include <cstdlib>

#include <GL/gl.h>
#include <GL/glut.h>

/*
 * Internal Includes
 */
#include <OpenKN/controller/LIN_DVCam.hpp>

kn::DVCam *dvcam;

unsigned int imagetexwidth, imagetexheight;

float texcoords, texcoordt;

unsigned int windowwidth=720, windowheight=576;

unsigned int textureid = 0;

int timebase = 0;

void quit(void){

	dvcam->stop();
	dvcam->closeDevice();
	delete dvcam;
	exit(0);
	
}


static void displayGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	// Background texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,textureid);
	glBegin(GL_QUADS);
	glColor3f(1.0f,1.0f,1.0f);
	glTexCoord2f(0.0f,texcoordt);
	glVertex2i(0,0);
	glTexCoord2f(0.0f,0.0f);
	glVertex2i(0,windowheight);
	glTexCoord2f(texcoords,0.0f);
	glVertex2i(windowwidth,windowheight);
	glTexCoord2f(texcoords,texcoordt);
	glVertex2i(windowwidth,0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glutSwapBuffers();

}


static void reshapeGL(int newwidth, 
					  int newheight)
{

	windowwidth = dvcam->width();
	windowheight = dvcam->height();

	float ratio = (float)windowwidth/(float)windowheight;
	glViewport(0, 0, (GLint)windowwidth, (GLint)windowheight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 2D projection for background image
	glOrtho(0,windowwidth,0,windowheight,-0.2,0.2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
 
}


static void idleGL(void)
{
	glBindTexture(GL_TEXTURE_2D,textureid);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, windowwidth, windowheight, GL_RGB, GL_UNSIGNED_BYTE,dvcam->getImage());
	glBindTexture(GL_TEXTURE_2D,0);
    int dt = glutGet(GLUT_ELAPSED_TIME) - timebase;
    if(dt >= 30){
        timebase += dt - 30;
        glutPostRedisplay();
    }

}

static void keyboardGL(unsigned char c, 
					   int x, 
					   int y){ 
	switch(c){ 
	case 27: case 'q':
		quit();
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int nearestPowerOf2(int v)
{
	int l,p;

	for (l=v,p=0;l>0;l>>=1,++p){}
	if ((1 << (p-1)) == v)
		return (v);
	return (1 << (p));
}

bool initDV(void){

	try{
		dvcam = new kn::DVCam();
		kn::DVCamParams defaultparams(0);
		dvcam->openDevice(defaultparams);
		dvcam->start();

		windowwidth = dvcam->width();
		windowheight = dvcam->height();

		imagetexwidth  = nearestPowerOf2(int(windowwidth));
		imagetexheight = nearestPowerOf2(int(windowheight));
		
		texcoords = float(windowwidth)/float(imagetexwidth);
		texcoordt = float(windowheight)/float(imagetexheight);
	}catch(kn::ControllerException e){
		std::cerr << e << std::endl;
		return false;
	}
	return true;
}



int main(int argc, char** argv){

	if(!initDV())
		return 0;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(windowwidth, windowheight);
	
	if(glutCreateWindow("DV Capture") == 0)
		return 1;
	
	glGenTextures(0, &textureid);
	glBindTexture(GL_TEXTURE_2D,textureid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagetexwidth, imagetexheight, 0, GL_RGB, GL_UNSIGNED_BYTE, dvcam->getImage());
	usleep(50);
	
	glDisable(GL_LIGHT0);

	glutReshapeFunc(reshapeGL);
	glutDisplayFunc(displayGL);
	glutIdleFunc(idleGL);
	glutKeyboardFunc(keyboardGL);
	
    timebase = glutGet(GLUT_ELAPSED_TIME);

	glutMainLoop();
	
	return 0;

}
