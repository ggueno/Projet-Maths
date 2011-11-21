/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * Wiimote_sample.cpp created in 01 2009.
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


#include <OpenKN/controller/WiimoteManager.hpp>
#include <unistd.h>

#include <GL/glut.h>

bool initGL(void);
bool initAnimations(void);
bool initWiimote(void);
bool closeManager(void);
void quit(void);
static void idleFunc(void);
static void drawFunc(void);
static void reshapeFunc(int,int);
static void keyboardGL(unsigned char c, int x, int y);

int position = kn::IR_POSITION_BELOW;
int aspect = kn::ASPECT_4_3;


kn::WiimoteManager *manager = 0;

static float _far = 7.0f;
static float _near = 0.1f;

static unsigned int windowwidth = 640;
static unsigned int windowheight = 480;

bool displaydots = false;
bool displaypointer = false;
bool displayteapot = true;

static void keyboardGL(unsigned char c, int x, int y){

    switch(c)
    { 
    case 27  :  // quit
    case 'q' : 
    case 'Q' :
        quit();
        break;
    }
    glutPostRedisplay();
}


void quit(void){
    closeManager();
    exit(0);
}


bool initWiimote(void){

    try{
        manager = new kn::WiimoteManager();
        std::cout << "Press simultaneously buttons 1 and 2 of the wiimote to activate the device" << std::endl;
        manager->launch();
        manager->getWiimote().setIRParameters(windowwidth,windowheight,aspect,position);
        manager->getWiimote().toggleIR();
    }catch(kn::ControllerException err){
      std::cerr << err << std::endl;
      if(manager) delete manager;
      return false;
    }
    return true;
}

bool closeManager(void){

    if(manager!=0){
        try{
            manager->stop();    
        }catch(kn::ControllerException err){
            std::cerr << err << std::endl;
            delete manager;
            return false;
        }
        if(manager!=0) delete manager;
    }
    return true;
}


static void reshapeFunc(int newwidth, 
                        int newheight)
{
    float ratio = (float)windowwidth/(float)windowheight;
  
    windowwidth = newwidth;
    windowheight = newheight;

    glViewport(0,0,windowwidth,windowheight);
    manager->getWiimote().setIRParameters(windowwidth,windowheight,aspect,position);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,windowwidth,0,windowheight,-0.2,0.2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
       
}


static void drawFunc(void){

    glPushMatrix();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(displaydots){
        unsigned int dn = manager->getWiimote().getDotsNumber();
        for(int i = 0; i < dn; ++i){
            kn::WiimoteIRDot d;
            try{
                d = manager->getWiimote().getDot(i);
                glBegin(GL_TRIANGLES);
                glColor3f(1.0,0.0,0.0);
                glVertex2i(d.x-4,d.y-4);
                glVertex2i(d.x+4,d.y-4);
                glVertex2i(d.x,d.y+4);
                glEnd();
                glBegin(GL_TRIANGLES);
                glColor3f(0.0,1.0,0.0);
                glVertex2i(d.rx-4,d.ry-4);
                glVertex2i(d.rx+4,d.ry-4);
                glVertex2i(d.rx,d.ry+4);
                glEnd();
            }catch(kn::ControllerException err){
                std::cerr << "Dot " << i << " : " <<err << std::endl;
            }
        }
  
    }

    if(displaypointer){
        kn::WiimoteIRPointer p;
        try{
            p = manager->getWiimote().getPointer();
            glBegin(GL_TRIANGLES);
            glColor3f(0.0,0.0,1.0);
            glVertex2i(p.x-4,windowheight-p.y-4);
            glVertex2i(p.x+4,windowheight-p.y-4);
            glVertex2i(p.x,windowheight-p.y+4);
            glEnd();
            std::cout << p.x << " " << p.y << std::endl;
            
        }catch(kn::ControllerException err){
            std::cerr << "Pointer : " <<err << std::endl;
        }
        
    }

    if(displayteapot){
        glMatrixMode(GL_PROJECTION);
         glPushMatrix();
         glLoadIdentity();
         gluPerspective(60.0,(float)windowwidth/(float)windowheight,0.001,10.0);
         glMatrixMode(GL_MODELVIEW);

         glEnable(GL_LIGHTING);
         glEnable(GL_LIGHT0);
         float LightPos[] = {0.0,0.0,-2.0,1.0};
         glLightfv(GL_LIGHT0,GL_POSITION,LightPos);
         float white[] = {1.f,1.f,1.f,1.f};
         float black[] = {0.f,0.f,0.f,1.f};
         glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
         glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,black);
         glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,white); 

         glPushMatrix();
         glTranslatef(-2.0,0.0,-4.0);
         glRotatef(-manager->getWiimote().getRoll(),0.0,0.0,1.0);
         glutSolidTeapot(0.5);
         glPopMatrix();

         glPushMatrix();
         glTranslatef(0.0,0.0,-4.0);
         glRotatef(-manager->getWiimote().getPitch(),1.0,0.0,0.0);
         glutSolidTeapot(0.5);
         glPopMatrix();

         if(manager->getWiimote().isIRSet()){
             glPushMatrix();
             glTranslatef(2.0,0.0,-4.0);
             glRotatef(manager->getWiimote().getYaw(),0.0,1.0,0.0);
             glutSolidTeapot(0.5);
             glPopMatrix();
          }

         glDisable(GL_LIGHT0);
         glDisable(GL_LIGHTING);

         glMatrixMode(GL_PROJECTION);
         glPopMatrix();         
         glMatrixMode(GL_MODELVIEW);
    }

    glPopMatrix();

    glutSwapBuffers();

}



static void idleFunc(void){

    glutPostRedisplay();
}


bool initGL(void){

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glDisable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

}

void MenuIRConf(int selection)
{
    if(selection==1){
        manager->getWiimote().setIRParameters(windowwidth,windowheight,kn::ASPECT_4_3,position);
        aspect = kn::ASPECT_4_3;
    }
    if(selection==2){
        manager->getWiimote().setIRParameters(windowwidth,windowheight,kn::ASPECT_16_9,position);
        aspect = kn::ASPECT_16_9;
    }
    if(selection==2){
        manager->getWiimote().setIRParameters(windowwidth,windowheight,aspect,kn::IR_POSITION_ABOVE);
        position = kn::IR_POSITION_ABOVE;
    }
    if(selection==3){
        manager->getWiimote().setIRParameters(windowwidth,windowheight,aspect,kn::IR_POSITION_BELOW);
        position = kn::IR_POSITION_BELOW;
    }
}

void MenuIR(int selection)
{
    if(selection==1){
        manager->getWiimote().toggleIR();
        std::cout << "IR : " << manager->getWiimote().isIRSet() << std::endl;
    }
    if(selection==2){
        manager->getWiimote().setIRSensitivity(manager->getWiimote().getIRSensitivity()+1);
    }
    if(selection==3){
        manager->getWiimote().setIRSensitivity(manager->getWiimote().getIRSensitivity()-1);
    }
    if(selection==4){
        displaydots= !displaydots;
    }    
    if(selection==5){
        displaypointer = !displaypointer;
    }

}

void MenuLED(int selection)
{
    manager->getWiimote().toggleLED(selection);
}

void MenuMain(int selection)
{

    if(selection==1)
      manager->getWiimote().toggleRumble();  
    if(selection==2)
        quit();
    if(selection==3)
       displayteapot = !displayteapot;
    if(selection==4)
        manager->getWiimote().showStatus();

}

int main(int argc, char** argv){

    if(!initWiimote()){
        return 1;
    }
  
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutInitWindowPosition(0,0);
    glutInitWindowSize(windowwidth, windowheight);

    if(glutCreateWindow("Wiimote example") == 0)
        return 1;

    initGL();

    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(drawFunc);
    glutIdleFunc(idleFunc);
    glutKeyboardFunc(keyboardGL);
   
    int menuirconf = glutCreateMenu(MenuIRConf);
    glutAddMenuEntry("Set Aspect 4/3",1);
    glutAddMenuEntry("Set Aspect 16/9",2);
    glutAddMenuEntry("Position above",3);
    glutAddMenuEntry("Position below",4);
    int menuir = glutCreateMenu(MenuIR);
    glutAddMenuEntry("Toggle IR Tracking",1);
    glutAddMenuEntry("Increase sensitivity",2);
    glutAddMenuEntry("Decrease sensitivity",3);
    glutAddMenuEntry("Display dots",4);
    glutAddMenuEntry("Display pointer",5);
    glutAddSubMenu("Configuration",menuirconf);
    int menuled = glutCreateMenu(MenuLED);
    glutAddMenuEntry("Toggle LED 1",1);
    glutAddMenuEntry("Toggle LED 2",2);
    glutAddMenuEntry("Toggle LED 3",3);
    glutAddMenuEntry("Toggle LED 4",4);
    int mainmenu = glutCreateMenu(MenuMain);
    glutAddSubMenu("LEDs",menuled);
    glutAddSubMenu("IR",menuir);
    glutAddMenuEntry("Toggle rumble",1);
    glutAddMenuEntry("Display teapot",3);
    glutAddMenuEntry("Show status",4);
    glutAddMenuEntry("Quitter",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);


    glutMainLoop();

    return 0;


        /*for(int i = 0; i < 100; ++i){
            std::cout << manager->getWiimote().getRoll() << std::endl;
            std::cout << manager->getWiimote().getPitch() << std::endl;
            std::cout << manager->getWiimote().getXForce() << std::endl;
            std::cout << manager->getWiimote().getYForce() << std::endl;
            std::cout << manager->getWiimote().getZForce() << std::endl;
            std::cout << "------------------------------------------" << std::endl;
            usleep(100000);
        }*/

        /*kn::WiimoteIRPointer p;
        manager->getWiimote().toggleIR();
        manager->getWiimote().setIRParameters(1280,1024,kn::ASPECT_4_3);
        for(int i = 0; i < 5000; ++i){
            p = manager->getWiimote().getPointer();
            std::cout << p.x << " " << p.y << std::endl;
            usleep(1000);
            }
            manager->getWiimote().toggleIR();*/

        /*sleep(1);
        if(manager->getWiimote().popEvent() == kn::EVENT_BUTTON_A_DOWN)
        std::cout << "Boutton A pressé" << std::endl;*/
       
        /*kn::WiimoteIRDot p;
        manager->getWiimote().toggleIR();
        for(int i = 0; i < 5000; ++i){
            if(manager->getWiimote().getDotsNumber() > 0){
               p =  manager->getWiimote().getDot(0);
               std :: cout << p.x << " " << p.y << " " << p.size << std::endl;
            }
            usleep(1000);
            }*/

        /*  for(int i = 0; i < 2000; ++i){
            if(manager->getWiimote().getNunchuk().isConnected()){
                std::cout << "angle : " << manager->getWiimote().getNunchuk().getJoystickAngle() << std::endl;
                std::cout << "magnitude : " << manager->getWiimote().getNunchuk().getJoystickMagnitude() << std::endl;
                std::cout << "roll : " << manager->getWiimote().getNunchuk().getRoll() << std::endl;
                std::cout << "pitch : " << manager->getWiimote().getNunchuk().getPitch() << std::endl;
                std::cout << "xforce : " << manager->getWiimote().getNunchuk().getXForce() << std::endl;
            }
            usleep(5000);
        
            }*/
    /*  int i = 0;
        while(i<50000000){
            if(manager->getWiimote().popEvent() == kn::EVENT_BUTTON_A_DOWN)
                std::cout << "Boutton A pressé" << std::endl;
            ++i;
        }

        sleep(1);
       
  
        return 0;*/

}
