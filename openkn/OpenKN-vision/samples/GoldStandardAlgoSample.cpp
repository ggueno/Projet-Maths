/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * GoldStandardAlgoSample.cpp created in 04 2009.
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
#include <GL/gl.h>
#include <GL/glut.h>

/*
 * Internal Includes
 */
#include <OpenKN/vision/ProjectiveCamera.hpp>
#include <OpenKN/vision/CameraCalibrationDLT.hpp>
#include <OpenKN/image/ImageRGB.hpp>
#include <OpenKN/image/ioJPG.hpp>
#include <OpenKN/math/Vector.hpp>

// Origine de la fenetre
static const unsigned int windowx = 0;
static const unsigned int windowy = 0;

// Dimensions de la fenetre
static unsigned int windowwidth  = 800;
static unsigned int windowheight = 600;

unsigned int imagetexwidth, imagetexheight;

float texcoords, texcoordt;

kn::Vector3d tmp;

unsigned int textureid = 0;

// GL projection matrix
float projectionmatrix[16];

// GL modelview matrix
float modelviewmatrix[16];


static void displayGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();

  // 2D so don't care of depth
  glDisable(GL_DEPTH_TEST);

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

  // Point projected accordind to the projective camera projection matrix
  glPointSize(5.0);
  glColor3f(1.0,0.0,0.0);
  glBegin(GL_POINTS);
  glVertex2i(tmp[0],windowheight-tmp[1]);
  glEnd();
  glEnable(GL_DEPTH_TEST);

  glClear(GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  // Applying the computed projection matrix
  glLoadMatrixf(projectionmatrix);

  glMatrixMode(GL_MODELVIEW);
  // Applying the computed modelview matrix
  glLoadMatrixf(modelviewmatrix);

  glEnable(GL_LIGHTING);
  float lightpos[4] = {20.0f,20.0f,20.0f,1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  glPushMatrix();
  glTranslatef(0.1f,0.7f,0.0025f);
  glutSolidCube(0.05);
  glPopMatrix();
  glDisable(GL_LIGHTING);

  // Draw frame of reference
  glBegin(GL_LINES);
  glColor3f(1.0,0.0,0.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(1.0,0.0,0.0);
  glColor3f(0.0,1.0,0.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0,1.0,0.0);
  glColor3f(0.0,0.0,1.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0,0.0,0.6);
  glEnd();

  glPointSize(5.0);
  glColor3f(1.0,1.0,0.0);
  glBegin(GL_POINTS);
  glVertex3f(0.0,0.0,0.6);
  glEnd();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
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
    glutPostRedisplay();
}

static void keyboardGL(unsigned char c,
		       int x,
		       int y){
  switch(c){
  case 27: case 'q':
      exit(0);
    break;
  case 'w':
    GLint wtype[2];
    glGetIntegerv(GL_POLYGON_MODE,wtype);
    if(wtype[0]==GL_FILL)
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    else
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
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

int main( int argc, char ** argv){

    std::vector< std::pair<kn::Vector4d,kn::Vector3d> > correspondanceList;

    kn::Vector3d v2d;
    kn::Vector4d v3d;
    v2d[2] = v3d[3] = 1.0;

    // Definition of the correspondances
    // Each 3D point have been measured manually
    // vertical accuracy is not good because most of the points are in xy plane

    v3d[0] = 0.0;
    v3d[1] = 0.0;
    v3d[2] = 0.0;
    v2d[0] = 523.0;
    v2d[1] = 312.0;
    correspondanceList.push_back(std::pair< kn::Vector4d,kn::Vector3d>(v3d,v2d));

    v3d[0] = 0.030;
    v3d[1] = 0.095;
    v3d[2] = 0.033;
    v2d[0] = 492.0;
    v2d[1] = 298.0;
    correspondanceList.push_back(std::pair< kn::Vector4d,kn::Vector3d>(v3d,v2d));

    v3d[0] = 0.230;
    v3d[1] = 0.245;
    v3d[2] = 0.033;
    v2d[0] = 368.0;
    v2d[1] = 296.0;
    correspondanceList.push_back(std::pair< kn::Vector4d,kn::Vector3d>(v3d,v2d));

    v3d[0] = 0.176;
    v3d[1] = 0.463;
    v3d[2] = 0.0;
    v2d[0] = 316.0;
    v2d[1] = 326.0;
    correspondanceList.push_back(std::pair< kn::Vector4d,kn::Vector3d>(v3d,v2d));

    v3d[0] = 0.366;
    v3d[1] = 0.463;
    v3d[2] = 0.242;
    v2d[0] = 240.0;
    v2d[1] = 184.0;
    correspondanceList.push_back(std::pair< kn::Vector4d,kn::Vector3d>(v3d,v2d));

    v3d[0] = 0.108;
    v3d[1] = 0.608;
    v3d[2] = 0.03;
    v2d[0] = 292.0;
    v2d[1] = 326.0;
    correspondanceList.push_back(std::pair< kn::Vector4d,kn::Vector3d>(v3d,v2d));

    v3d[0] = 0.124;
    v3d[1] = 0.666;
    v3d[2] = 0.135;
    v2d[0] = 250.0;
    v2d[1] = 254.0;
    correspondanceList.push_back(std::pair< kn::Vector4d,kn::Vector3d>(v3d,v2d));

    v3d[0] = 0.0;
    v3d[1] = 0.625;
    v3d[2] = 0.0;
    v2d[0] = 346.0;
    v2d[1] = 364.0;
    correspondanceList.push_back(std::pair< kn::Vector4d,kn::Vector3d>(v3d,v2d));

    kn::ProjectiveCamera P(cameraCalibrationDLT(correspondanceList));

    // Get the GL projection matrix
    P.getGLProjectionMatrix(640,480,0.1f,100.0f,projectionmatrix);

    // Get the modelview projection matrix
    P.getGLModelviewMatrix(modelviewmatrix);


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowPosition(windowx, windowy);
    glutInitWindowSize(windowwidth, windowheight);

    if(glutCreateWindow("Gold Standard Algorithm") == 0)
        return 1;

    // Load backgroung image
    kn::ImageRGB8u image;
    kn::loadJPG(image,"./inputData/GSAimage.jpg");

    imagetexwidth  = nearestPowerOf2(int(image.width()));
    imagetexheight = nearestPowerOf2(int(image.height()));

    texcoords = float(image.width())/float(imagetexwidth);
    texcoordt = float(image.height())/float(imagetexheight);

    glGenTextures(0, &textureid);
    glBindTexture(GL_TEXTURE_2D,textureid);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagetexwidth, imagetexheight, 0, GL_RGB, GL_UNSIGNED_BYTE,0);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image.width(), image.height(), GL_RGB, GL_UNSIGNED_BYTE,image.begin());


    glEnable(GL_LIGHT0);
    float white[4] = {1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE,white);

    glutReshapeFunc(reshapeGL);
    glutDisplayFunc(displayGL);
    glutIdleFunc(idleGL);
    glutKeyboardFunc(keyboardGL);


    // Computes the projection of the basis point according tot the current GL matrices
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT,viewport);
    GLdouble x,y,z;
    GLdouble mv[16];
    GLdouble proj[16];
    for(int i = 0; i < 16; ++i){
        mv[i] = (GLdouble)modelviewmatrix[i];
        proj[i] = (GLdouble)projectionmatrix[i];
    }
    gluProject(0.0,0.0,0.6f,mv,proj,viewport,&x,&y,&z);

    // Computes projection of the basis point
    kn::Vector<double> tmp4d(4);
    tmp4d.fill(0.0);
    tmp4d[2] = 0.6;
    tmp4d[3] = 1.0;
		std::cerr<<"====> ON A "<<tmp4d[0]<<":"<<tmp4d[1]<<":"<<tmp4d[2]<<":"<<tmp4d[3]<<std::endl;
    tmp = P.project(tmp4d);
		std::cerr<<"====> ON A "<<tmp[0]<<":"<<tmp[1]<<":"<<tmp[2]<<std::endl;


    // Take account of window's size
    tmp[0] = tmp[0] * float(windowwidth) / 640.0f;
    tmp[1] = tmp[1] * float(windowheight) / 480.0f;
    tmp = tmp/tmp[2];

    std::cout << "Projection vision : " <<  tmp[0] << " " << windowheight - tmp[1] << " " << tmp[2] << std::endl;
    std::cout << "Projection Opengl : " << x << " " << y << " " << z << std::endl;
    std::cout << "-----------------------------------------------------------------" << std::endl;

    glutMainLoop();

    return 0;
}
