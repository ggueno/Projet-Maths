/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * CVtoGLSampleample.cpp created in 04 2009.
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

#include <OpenKN/util/StringEnumerator.hpp>
#include <OpenKN/vision/OpencvCalibrationTools.hpp>
#include <OpenKN/vision/ProjectiveCamera.hpp>
#include <OpenKN/vision/CameraCalibrationZhang.hpp>
#include <OpenKN/vision/Homography.hpp>
#include <OpenKN/math/Matrix3x3.hpp>
#include <OpenKN/math/Vector.hpp>
#include <OpenKN/image/ImageRGB.hpp>
#include <OpenKN/image/ioJPG.hpp>
#include <OpenKN/image/ioPPM.hpp>

#include <GL/gl.h>
#include <GL/glut.h>

int timebase = 0;

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

// homography list
std::vector<kn::Matrix3x3d> Hlist;

// Projective camera
kn::ProjectiveCamera *P  = 0;

// current displayed object (0 cube - 1 teapot)
unsigned int currentobject = 1;


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
  glTranslatef(9.0f,9.0f,3.0f);
  if(currentobject == 1){
      glRotatef(90.0f,1.0,0.0,0.0);
      glutSolidTeapot(5.0);
  }else{
      glutSolidCube(6.0);
  }
  glPopMatrix();
  glDisable(GL_LIGHTING);

  // Draw frame of reference
  glBegin(GL_LINES);
  glColor3f(1.0,0.0,0.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(3.0,0.0,0.0);
  glColor3f(0.0,1.0,0.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0,3.0,0.0);
  glColor3f(0.0,0.0,1.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0,0.0,3.0);
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
    static int i = 0;
    int dt = glutGet(GLUT_ELAPSED_TIME) - timebase;

    // Use a new image for extrinsic parameters each five seconds
    if(dt >= 5000){

        i = (i+1) % 13;

        timebase += dt;

        std::cout << "P\n" <<P->P() << std::endl;
        std::cout << "R\n" << P->R() << std::endl;

        // Get new projection matrix according to a given homography (image)
				computeExternalParametersZhang(Hlist[i], *P);
        //P->computeExternalParameters(Hlist[i]);

        // Computes the new GL projection matrix
        P->getGLProjectionMatrix(640,480,0.1f,100.0f,projectionmatrix);

        // Computes the new GL modelview matrix
        P->getGLModelviewMatrix(modelviewmatrix);

        // Load the related image
        kn::ImageRGB8u image;
        kn::loadJPG(image,kn::stringEnumerator("inputData/capture",i,4,".jpg"));

        // Updates he texture
        glBindTexture(GL_TEXTURE_2D,textureid);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image.width(), image.height(), GL_RGB, GL_UNSIGNED_BYTE,image.begin());

        // Computes the projection of the basis point according tot the current projection matrix
        kn::Vector<double> tmp4d(4);
        tmp4d.fill(0.0);
        tmp4d[3] = 1.0;
        //tmp = (P->P() * tmp4d).convertToVector3D();
        tmp = P->project(tmp4d);


        // Take account of window's size
        tmp[0] = tmp[0] * windowwidth / 640.0f;
        tmp[1] = tmp[1] * windowheight / 480.0f;
        tmp = tmp/tmp[2];

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
        gluProject(0.0,0.0,0.0f,mv,proj,viewport,&x,&y,&z);

        std::cout << "Projection vision : " <<  tmp[0] << " " << windowheight - tmp[1] << " " << tmp[2] << std::endl;
        std::cout << "Projection Opengl : " << x << " " << y << " " << z << std::endl;
        std::cout << "-----------------------------------------------------------------" << std::endl;

    }
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
  case 'c':
      currentobject++;
      currentobject%=2;
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
	// load images
	std::vector<kn::ImageRGB8u> imageList;
	for(unsigned int i=0; i< 13; i++){
	      kn::ImageRGB8u image;
	      kn::loadJPG(image,kn::stringEnumerator("inputData/capture",i,4,".jpg"));
	      imageList.push_back(image);
	}

	// detect the corners
	for(unsigned int i=0; i< 13; i++){
		// 2d-2d correpondance list
		std::vector< std::pair<kn::Vector3d,kn::Vector3d> > correspondanceList;

		// detect the corners
		kn::opencvChessboardDetection(imageList[i],
					      correspondanceList,
					      8, 6,
					      3.0, // cm
					      true);
		if(correspondanceList.size() > 3){
		  Hlist.push_back(kn::computeHomographyNormalized(correspondanceList));
		  kn::savePPM(imageList[i],kn::stringEnumerator("outputData/chessboard",i,4,".ppm"));
		}
	}
    // Compute the Projective camera parameters
    //P  = new kn::ProjectiveCamera(Hlist);
    P  = new kn::ProjectiveCamera(cameraCalibrationZhang(Hlist));

    // Specifies specific external parameters
    //P->computeExternalParameters(Hlist[0]);
    computeExternalParametersZhang(Hlist[0], *P);

    // Get the GL projection matrix
    P->getGLProjectionMatrix(640,480,0.1f,100.0f,projectionmatrix);

    // Get the modelview projection matrix
    P->getGLModelviewMatrix(modelviewmatrix);

    // Computes projection of the basis point
    kn::Vector<double> tmp4d(4);
    tmp4d.fill(0.0);
    tmp4d[3] = 1.0;
    tmp = P->project(tmp4d);

    // Take account of window's size
    tmp[0] = tmp[0] * windowwidth / 640.0f;
    tmp[1] = tmp[1] * windowheight / 480.0f;
    tmp = tmp/tmp[2];

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowPosition(windowx, windowy);
    glutInitWindowSize(windowwidth, windowheight);

    if(glutCreateWindow("Zhang") == 0)
        return 1;

    // Load backgroung image
    kn::ImageRGB8u image;
    kn::loadJPG(image,kn::stringEnumerator("inputData/capture",0,4,".jpg"));

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

    timebase = glutGet(GLUT_ELAPSED_TIME);

    glutMainLoop();

    return 0;
}
