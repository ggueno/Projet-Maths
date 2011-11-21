/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * LIN_V4L2Webcam_sample2.cpp created in 03 2009.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
#include <OpenKN/controller/LIN_V4L2Webcam.hpp>

kn::V4L2Webcam webcam;/* *webcam = 0;*/

unsigned int imagetexwidth, imagetexheight;

float texcoords, texcoordt;

unsigned int windowwidth=1024, windowheight=768;

unsigned int textureid = 0;

void quit(void){

    webcam.stop();
    webcam.closeDevice();
    /*delete webcam;*/
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

  float ratio = (float)newwidth/(float)newheight;
  glViewport(0, 0, (GLint)newwidth, (GLint)newheight);
  
  windowwidth = newwidth;
  windowheight = newheight;

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
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, windowwidth, windowheight, GL_RGB, GL_UNSIGNED_BYTE,webcam.getImage());
    glBindTexture(GL_TEXTURE_2D,0);
    usleep(1000);
    glutPostRedisplay();
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

bool initWebcam(void){

    try{
        //webcam = new kn::V4L2Webcam();
        kn::V4L2WebcamParams defaultparams("/dev/video0",windowwidth,windowheight,kn::FMT_MJPEG,kn::MMAP_METHOD,35);
        webcam.openDevice(defaultparams);
        webcam.start();
        windowwidth = webcam.width();
        windowheight = webcam.height();

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

    if(!initWebcam())
        return 0;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(windowwidth, windowheight);
    
    if(glutCreateWindow("V4L2 Webcam Capture") == 0)
        return 1;
    
    glGenTextures(0, &textureid);
    glBindTexture(GL_TEXTURE_2D,textureid);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagetexwidth, imagetexheight, 0, GL_RGB, GL_UNSIGNED_BYTE, webcam.getImage());
    usleep(50);
    
    glDisable(GL_LIGHT0);

    glutReshapeFunc(reshapeGL);
    glutDisplayFunc(displayGL);
    glutIdleFunc(idleGL);
    glutKeyboardFunc(keyboardGL);
    
    glutMainLoop();
    
    return 0;

}
