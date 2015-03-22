// Ann Tupek
// CS381 HW5
// Due 4 Nov 2014
// HW5ATupek.cpp
// different colored lighting of gems
// associated shaders: HW5ATupek_v.glsl HW5ATupek_f.glsl
//
// structure based on
// useshaders.cpp
// VERSION 6
// by Glenn G. Chappell

// OpenGL/GLUT includes - DO THESE FIRST
#include <cstdlib>       // Do this before GL/GLUT includes
using std::exit;
#ifndef __APPLE__
# include <GL/glew.h>
# include <GL/glut.h>    // Includes OpenGL headers as well
#else
# include <GLEW/glew.h>
# include <GLUT/glut.h>  // Apple puts glut.h in a different place
#endif
#ifdef _MSC_VER          // Tell MS-Visual Studio about GLEW lib
# pragma comment(lib, "glew32.lib")
#endif

// Other includes
#include "lib381/bitmapprinter.h"
// For class BitmapPrinter
#include "lib381/glslprog.h"
// For GLSL code-handling functions

#include <string>
using std::string;
#include <iostream>
using std::cerr;
using std::endl;
#include <vector>
using std::vector;

// Global variables
// Keyboard
const int ESCKEY = 27;         // ASCII value of Escape

// Window/viewport
const int startwinsize = 600;  // Start window width & height (pixels)
int winw = 1, winh = 1;        // Window width, height (pixels)
//  (Initialize to avoid spurious errors)
bool showhelp;                 // True if docs displayed

// Objects
double savetime;               // Time of previous movement (sec)
double rotangle;               // Rotation angle for object (deg)
const double rotspeed = 40.;   // Rotation speed (deg/sec)
bool rotateflag;               // True if object rotating

// Shaders
string vshader1fname;          // Filename for vertex shader source
string fshader1fname;          // Filename for fragment shader source
GLhandleARB prog1;             // GLSL Program Object

//bool shaderbool1;              // Boolean to send to shaders
GLfloat shaderfloat1;          // Float to send to shaders
GLfloat differentColors;             //for red lighting

//points for the gem
const double gemPoints[8][3]=
{
    -0.1, 0.1, 0.0, //first four are vertices of top
    -0.1, -0.1, 0.0, //for top & side (vert 5)
    0.1, 0.1, 0.0,
    0.1, -0.1, 0.0, //for top & side (vert 7)
    -0.15, -0.15, -0.15, //for side & bottom (vert 9)
    0.0, -0.15, -0.15,
    0.15, -0.15, -0.15, //for side & bottom (vert 11)
    0.0, 0.0, -0.3
};

//faces for the gem
const int gemFaces[6][3]=
{
    0, 1, 2,
    3, 2, 1,
    5, 1, 4,
    1, 5, 3,
    6, 3, 5,
    4, 7, 6
};

//compute cross product for normals
vector<double> cross_product(vector<double> v1, vector<double> v2)
{
    vector<double> cross;
    cross.resize(3);
    
    cross[0]=v1[1]*v2[2]-v1[2]*v2[1];
    cross[1]=v1[2]*v2[0]-v1[0]*v2[2];
    cross[2]=v1[0]*v2[1]-v1[1]*v2[0];
    return cross;
}

//draw the triangles of the gems with normals
void drawMeATriangle(vector<vector<double> > v, vector<vector<double> > c)
{
    vector<double> norm;
    
    vector<double> v1;
    vector<double> v2;
    v1.resize(3);
    v2.resize(3);
    
    v1[0] = v[0][0] - v[1][0];
    v1[1] = v[0][1] - v[1][1];
    v1[2] = v[0][2] - v[1][2];
    
    v2[0] = v[0][0] - v[2][0];
    v2[1] = v[0][1] - v[2][1];
    v2[2] = v[0][2] - v[2][2];
    
    norm = cross_product(v1, v2);
    
    glBegin(GL_TRIANGLES);
    
    glNormal3d(norm[0], norm[1], norm[2]);
    
    glColor3d(c[0][0], c[0][1], c[0][2]);
    glVertex3d(v[0][0], v[0][1], v[0][2]);
    
    glColor3d(c[1][0], c[1][1], c[1][2]);
    glVertex3d(v[1][0], v[1][1], v[1][2]);
    
    glColor3d(c[2][0], c[2][1], c[2][2]);
    glVertex3d(v[2][0], v[2][1], v[2][2]);
    
    glEnd();
}

//draw one side of the gem with triangles
void drawGem0()
{
    glPushMatrix();
    
    vector<vector<double> > v;
    vector<vector<double> > c;
    
    c.resize(3);
    v.resize(3);
    for(int ii = 0; ii < 3; ii++) {
        c[ii].resize(3);
        c[ii][0] = 1.0;
        c[ii][1] = 1.0;
        c[ii][2] = 1.0;
        
        v[ii].resize(3);
    }
    
    for(int ii = 0; ii < 6; ii++) {
        for(int jj = 0; jj < 3; jj++) {
            v[jj][0] = gemPoints[gemFaces[ii][jj]][0];
            v[jj][1] = gemPoints[gemFaces[ii][jj]][1];
            v[jj][2] = gemPoints[gemFaces[ii][jj]][2];
        }
        drawMeATriangle(v, c);
    }
    
    glPopMatrix();
}

//draw the whole gem
void drawGem()
{
    glPushMatrix();
    drawGem0();
    glPopMatrix();
    glPushMatrix();
    glRotated(90.0, 0.0, 0.0, 1.0);
    drawGem0();
    glPopMatrix();
    glPushMatrix();
    glRotated(180.0, 0.0, 0.0, 1.0);
    drawGem0();
    glPopMatrix();
    glPushMatrix();
    glRotated(-90.0, 0.0, 0.0, 1.0);
    drawGem0();
    glPopMatrix();
}

// myDisplay
// The GLUT display function
void myDisplay()
{
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    GLhandleARB theprog;  // CURRENTLY-used program object or 0 if none
    
    theprog = prog1;
    
    // Set up 3-D
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glTranslated(0., 0., -4.);  // Camera transformation
    
    GLfloat origin4[] = { 0.f, 0.f, 0.f, 1.f };
    
    // Position light source 1
    glPushMatrix();
    glTranslated(1., 0., 3.);
    glLightfv(GL_LIGHT1, GL_POSITION, origin4);
    glPopMatrix();
    
    // Make program object (if any) active
    glUseProgramObjectARB(theprog);
    
    // Send values to shaders
    if (theprog)
    {
        GLint loc;  // Location for shader vars

        loc = glGetUniformLocationARB(theprog, "myf1");
        if (loc != -1)
            glUniform1f(loc, shaderfloat1);
        
        loc = glGetUniformLocationARB(theprog, "myb2");
        if (loc != -1)
            glUniform1f(loc, differentColors);
    }
    
    // Draw the gems
    glPushMatrix();
    glTranslated(0.0, 0.0, 1.0);
    glRotated(-80.0, 1.0, 0.0, 0.0);
    glRotated(rotangle, 0.0, 0.0, 1.0);
    glScaled(2.0, 2.0, 2.0);
    drawGem();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(1.0, 0.0, 0.0);
    glRotated(-80.0, 1.0, 0.0, 0.0);
    glRotated(rotangle, 0.0, 0.0, 1.0);
    glScaled(2.0, 1.0, 1.0);
    drawGem();
    glPopMatrix();
            
    glPushMatrix();
    glTranslated(-1.0, 0.0, 0.0);
    glRotated(-80.0, 1.0, 0.0, 0.0);
    glRotated(rotangle, 0.0, 0.0, 1.0);
    glScaled(2.0, 1.0, 1.0);
    drawGem();
    glPopMatrix();
    
    // Reset polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // Draw documentation
    glUseProgramObjectARB(0);     // No shaders
    glDisable(GL_DEPTH_TEST);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);  // Set up simple ortho projection
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0., double(winw), 0., double(winh));
    glColor3d(0., 0., 0.);
    BitmapPrinter p(20., winh-20., 20.);
    p.print("123456   Choose object to draw");
    p.print("R        Change light color to red");
    p.print("Y        Change light color to yellow");
    p.print("B        Change light color to blue");
    p.print("W        Change light color to white");
    p.print("O        Rotate gems");
    p.print("Esc      Quit");
    glPopMatrix();                // Restore prev projection
    glMatrixMode(GL_MODELVIEW);

    
    glutSwapBuffers();
}


// myIdle
// The GLUT idle function
void myIdle()
{
    // Compute elapsed time since last movement
    double currtime = glutGet(GLUT_ELAPSED_TIME) / 1000.;
    double elapsedtime = currtime - savetime;
    savetime = currtime;
    if (elapsedtime > 0.1)
        elapsedtime = 0.1;
    
    // Move objects
    
    // Rotate main object
    if (rotateflag)
    {
        rotangle += rotspeed * elapsedtime;
        glutPostRedisplay();
    }

    // Print OpenGL errors, if there are any (for debugging)
    static int error_count = 0;
    if (GLenum err = glGetError())
    {
        ++error_count;
        cerr << "OpenGL ERROR " << error_count << ": "
        << gluErrorString(err) << endl;
    }
}


// myKeyboard
// The GLUT keyboard function
void myKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case ESCKEY:  // Esc: quit
            exit(0);
            break;
        case 'o':     // O: toggle object rotation
        case 'O':
            rotateflag = !rotateflag;
            break;
        case 'r':     // R: for red lighting
        case 'R':
            differentColors=1.0;
            glutPostRedisplay();
            break;
        case 'y':     // Y: for yellow lighting
        case 'Y':
            differentColors=2.0;
            glutPostRedisplay();
            break;
        case 'b':     // B: for blue lighting
        case 'B':
            differentColors=3.0;
            glutPostRedisplay();
            break;
        case 'w':     // B: for white lighting
        case 'W':
            differentColors=0.0;
            glutPostRedisplay();
            break;
    }
}

// myReshape
// The GLUT reshape function
void myReshape(int w, int h)
{
    // Set viewport & save window dimensions in globals
    glViewport(0, 0, w, h);
    winw = w;
    winh = h;
    
    // Set up projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60., double(w)/h, 0.5, 50.);
    
    glMatrixMode(GL_MODELVIEW);  // Always go back to model/view mode
}


// init
// Initialize GL states & global data
// Called by main after window creation
void init()
{
    // Objects
    savetime = glutGet(GLUT_ELAPSED_TIME) / 1000.;
    rotangle = 0.;
    rotateflag = false;

    shaderfloat1 = 1.0f;
    differentColors = 0.0;
    
    showhelp = true;
    
    // OpenGL Stuff
    
    // Shaders
    prog1 = makeProgramObjectFromFiles(vshader1fname, fshader1fname);
}


int main(int argc, char ** argv)
{
    // Initialize OpenGL/GLUT
    glutInit(&argc, argv);
    getShaderFilenames(vshader1fname, fshader1fname, argc, argv);
    // Set shader source filenames. Done here, as opposed to in
    //  function init, so that we can use command-line arguments.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    // Make a window
    glutInitWindowSize(startwinsize, startwinsize);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("CS 381 - Ann Tupek HW5");
    
    // Init GLEW & check status
    if (glewInit() != GLEW_OK)
    {
        cerr << "glewInit failed" << endl;
        exit(1);
    }
    
    // Initialize GL states & register GLUT callbacks
    init();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myIdle);
    glutKeyboardFunc(myKeyboard);
    glutReshapeFunc(myReshape);
    
    // Do something
    glutMainLoop();
    
    return 0;
}