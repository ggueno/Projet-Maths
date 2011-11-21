#include <cstdlib>

#include <OpenKN/opengl/GLSLShader.hpp>

#include <GL/glut.h>

bool initGL(void);
bool initGLSL(void);
void quit(void);
static void idleFunc(void);
static void drawFunc(void);
static void reshapeFunc(int,int);
static void keyboardGL(unsigned char c, int x, int y);

static unsigned int windowwidth = 640;
static unsigned int windowheight = 480;


GLhandleARB po = 0; // shader program object

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

    if(po!=0)
        // program object is now useless
        glDeleteObjectARB(po);
    exit(0);
}


bool initGLSL(void){

    GLhandleARB vs = 0; // Vertex shader object
    GLhandleARB fs = 0; // Fragment shader object

    if(!kn::glslCheckAvailability())
        return false;

    try{
        vs = kn::glslLoadVertexShader("glsl_sample.vert");
        fs = kn::glslLoadFragmentShader("glsl_sample.frag");
    }catch(kn::OpenglException err){
        std::cerr << err << std::endl;
        return false;
    }

    try{
        kn::glslCompile(vs);
        kn::glslCompile(fs);
    }catch(kn::OpenglException err){
        std::cerr << err << std::endl;
        return false;
    }

    std::list<GLhandleARB> solist;
    solist.push_front(vs);
    solist.push_front(fs);
    po = 0;
    try{
        po = kn::glslLink(solist);
    }catch(kn::OpenglException err){
        std::cerr << err << std::endl;
        return false;
    }
    solist.clear();
    // shader objects are now useless
    glDeleteObjectARB(vs);
    glDeleteObjectARB(fs);

    return true;
}

static void reshapeFunc(int newwidth, 
                        int newheight)
{
    float ratio = (float)windowwidth/(float)windowheight;
  
    windowwidth = newwidth;
    windowheight = newheight;

    glViewport(0,0,windowwidth,windowheight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,ratio,0.01,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
       
}


static void drawFunc(void){

    glPushMatrix();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(po!=0){
        glUseProgramObjectARB(po);
    }
    
    glColor3f(1.0f,1.0f,1.0f);
    glTranslatef(0.0,0.0,-2.5);
    glutSolidTeapot(1.0);
    
    glUseProgramObjectARB(0);

    glPopMatrix();

    GLenum glerror;
    glerror = glGetError();
    if( glerror != GL_NO_ERROR){
      printf("OpenGL error has occured : %s \n",
      gluErrorString(glerror));
      quit();
    }

    glutSwapBuffers();

}



static void idleFunc(void){

    glutPostRedisplay();
}


bool initGL(void){

    glClearColor(0.2f,0.2f,0.2f,1.0f);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    return true;

}

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutInitWindowPosition(0,0);
    glutInitWindowSize(windowwidth, windowheight);

    if(glutCreateWindow("glsl sample") == 0)
        return 1;

    glewInit();

    if(!initGL())
        quit();

    if(!initGLSL())
        quit();

    GLenum glerror;
    glerror = glGetError();
    if( glerror != GL_NO_ERROR){
      printf("OpenGL error has occured : %s \n",
      gluErrorString(glerror));
      quit();
    }

    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(drawFunc);
    glutIdleFunc(idleFunc);
    glutKeyboardFunc(keyboardGL);

    glutMainLoop();

    return 0;
}
