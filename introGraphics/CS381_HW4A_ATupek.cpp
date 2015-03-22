// CS381_HW4A_ATupek.cpp
// Ann Tupek
// due 21 Oct 2014
//
// draws an interactive solar system model
// with rotating sun, planet, and moon
//
// Structure Based on hier.cpp
// drawSquare & drawCube from heir.cpp
// drawCylinder from useshaders.cpp
// by Glenn G. Chappell


// OpenGL/GLUT includes - DO THESE FIRST
#include <cstdlib>       // Do this before GL/GLUT includes
using std::exit;
#ifndef __APPLE__
# include <GL/glut.h>    // Includes OpenGL headers as well
#else
# include <GLUT/glut.h>  // Apple puts glut.h in a different place
#endif

// Other includes
#include "lib381/bitmapprinter.h"
// For class BitmapPrinter
#include <string>
using std::string;
#include <iostream>
using std::cerr;
using std::endl;
#include <cmath>
using std::cos;
using std::sin;


// Global variables
// Keyboard
const int ESCKEY = 27;         // ASCII value of Escape

// Window/viewport
const int startwinsize = 600;  // Start window width & height (pixels)
int winw = 1, winh = 1;        // Window width, height (pixels)
//  (Initialize to avoid spurious errors)

int subdivs = 50;
const double angstep = 10.0;   // Amt to rotate on single keypress (deg)
GLdouble savedrots[16];        // Saved rotation matrix for object
//  (OpenGL format)
double angSun = 0.0;
double angPlanet = 0.0;
double angMoon = 0.0;

// drawSquare
// Draws a filled square, using current GL states,
//  in the x,y plane, centered at the origin, aligned w/ x,y axes,
//  with side 2.
void drawSquare()
{
    glBegin(GL_POLYGON);
    glVertex2d(-1., -1.);
    glVertex2d( 1., -1.);
    glVertex2d( 1.,  1.);
    glVertex2d(-1.,  1.);
    glEnd();
}


// drawCube()
// Draws a cube, centered at origin, side length 2, axis aligned
void drawCube()
{
    // +x face
    glPushMatrix();
    glTranslated(1., 0., 0.);
    glRotated(90., 0.,1.,0.);
    drawSquare();
    glPopMatrix();
    
    // -x face
    glPushMatrix();
    glTranslated(-1., 0., 0.);
    glRotated(90., 0.,1.,0.);
    drawSquare();
    glPopMatrix();
    
    // +y face
    glPushMatrix();
    glTranslated(0., 1., 0.);
    glRotated(90., 1.,0.,0.);
    drawSquare();
    glPopMatrix();
    
    // -y face
    glPushMatrix();
    glTranslated(0., -1., 0.);
    glRotated(90., 1.,0.,0.);
    drawSquare();
    glPopMatrix();
    
    // +z face
    glPushMatrix();
    glTranslated(0., 0., 1.);
    drawSquare();
    glPopMatrix();
    
    // -z face
    glPushMatrix();
    glTranslated(0., 0., -1.);
    drawSquare();
    glPopMatrix();
}

// drawCylinder
// Draw a cylinder, radius 1, length 2, centered at origin, around
//  x-axis.
// Uses given number of subdivisions. Includes normal.
void drawCylinder()
{
    const double pi = 3.1415926535898;
    const double halflen = 1.;  // Half of cylinder's length
    const double radius = 1.;   // Cylinder's radius
    
    for (int i = 0; i < subdivs; ++i)
    {
        double x1 = -halflen + i*(2.*halflen/subdivs);
        double x2 = -halflen + (i+1)*(2.*halflen/subdivs);
        glBegin(GL_QUAD_STRIP);
        for (int k = 0; k <= subdivs*4; ++k)
        {
            double a = double(k)/(subdivs*4)*2.*pi;
            double ca = cos(a);
            double sa = sin(a);
            double y = radius * ca;
            double z = radius * sa;
            glNormal3d(0., ca, sa);
            glVertex3d(x2, y, z);
            glVertex3d(x1, y, z);
        }
        glEnd();
    }
}

//draw Base
void drawBase()
{
    drawCube();
}

//draw sun support
void drawSupport()
{
    drawCylinder();
 
}

//draw Sun
void drawSun()
{
    glColor3d(1.0, 1.0, 0.0);
    glutWireSphere(0.5, 20.0, 20.0);
}

//draw torus
void drawTorus()
{
    glColor3d(0.904, 0.598, 0.296);
    glutSolidTorus(0.025, 0.6, 50, 50);
}

//draw ring 2 support
void drawRing2Support()
{
    glColor3d(0.904, 0.598, 0.296);
    drawCylinder();
}

//draw Planet
void drawPlanet()
{
    glColor3d(0.529, 0.808, 0.980);
    glutWireSphere(0.5, 15.0, 15.0);
}

//draw ring 4 support
void drawRing4Support()
{
    glColor3d(0.904, 0.598, 0.296);
    drawCylinder();
}

//draw moon
void drawMoon()
{
    glColor3d(0.9, 0.9, 0.9);
    glutWireSphere(0.5, 10.0, 10.0);
}

//draw moon system
void drawMoonSystem()
{
    glPushMatrix();
    glTranslated(0.0, 0.45, 0.0);
    glRotated(90.0, 0.0, 1.0, 0.0);
    glScaled(0.2, 0.2, 0.2);
    drawMoon();
    glPopMatrix();
    
    glPushMatrix();
    glScaled(0.75, 0.75, 1.0);
    drawTorus();
    glPopMatrix();
}

//draw planet system
void drawPlanetSystem()
{
    glPushMatrix();
    glRotated(90.0, 0.0, 1.0, 0.0);
    glScaled(2.0, 2.0, 1.0);
    drawTorus();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.0, 1.25, 0.0);
    glRotated(90.0, 0.0, 1.0, 0.0);
    glScaled(0.5, 0.5, 0.5);
    drawPlanet();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.0, 1.16, 0.0);
    glRotated(90.0, 1.0, 0.0, 0.0);
    glScaled(0.5, 0.5, 1.0);
    drawTorus();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.358, 1.158, 0.0);
    glRotated(90.0, 1.0, 0.0, 0.0);
    glScaled(0.06, 0.025, 0.025);
    drawRing4Support();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.0, 1.25, 0.0);
    glRotated(angMoon, 0.0, 0.0, 1.0);
    drawMoonSystem();
    glPopMatrix();
}

//draw sun system
void drawSunSystem()
{
    glPushMatrix();
    glRotated(90.0, 0.0, 1.0, 0.0);
    glColor3d(1.0, 1.0, 0.0);
    drawSun();
    glPopMatrix();
    
    glPushMatrix();
    drawTorus();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.0, -0.9, 0.0);
    glRotated(90.0, 0.0, 0.0, 1.0);
    glScaled(0.3, 0.025, 0.025);
    drawRing2Support();
    glPopMatrix();
    
    glPushMatrix();
    glRotated(angPlanet, 1.0, 0.0, 0.0);
    drawPlanetSystem();
    glPopMatrix();
    
}

//draw stand
void drawStand()
{
    glPushMatrix();
    glTranslated(-1.5, 0.0, 0.0);
    glScaled(0.1, 1.0, 1.0);
    glColor3d(0.804, 0.498, 0.196);
    drawBase();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-1.0, 0.0, 0.0);
    glScaled(0.5, 0.05, 0.05);
    glColor3d(0.904, 0.598, 0.296);
    drawSupport();
    glPopMatrix();

}

//draw the whole model
void drawSolarModel()
{
    drawStand();

    glPushMatrix();
    glRotated(angSun, 1.0, 0.0, 0.0);
    drawSunSystem();
    glPopMatrix();
}

// myDisplay
// The GLUT display function
void myDisplay()
{
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Draw objects
    
    // Set up 3-D
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glTranslated(0., 0., -4.);  // Camera transformation
    glRotated(10.0, 1.0, 0.0, 0.0); // Camera transformation
    
    // Draw the model
    glMultMatrixd(savedrots);
    drawSolarModel();
    
    // Draw documentation
    glDisable(GL_DEPTH_TEST);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);  // Set up simple ortho projection
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0., double(winw), 0., double(winh));
    glColor3d(0., 0., 0.);        // Black text
    BitmapPrinter p(20., winh-20., 20.);
    p.print("Arrows   Rotate entire model");
    p.print("Space    Reset object rotation");
    p.print("");
    p.print("Q, W     Rotate Sun System");
    p.print("A, S     Rotate Planet System");
    p.print("Z, X     Rotate Moon System");
    p.print("");
    p.print("Esc      Quit");
    glPopMatrix();                // Restore prev projection
    glMatrixMode(GL_MODELVIEW);
    
    glutSwapBuffers();
}


// myIdle
// The GLUT idle function
void myIdle()
{
    // Print OpenGL errors, if there are any (for debugging)
    static int error_count = 0;
    if (GLenum err = glGetError())
    {
        ++error_count;
        cerr << "OpenGL ERROR " << error_count << ": "
        << gluErrorString(err) << endl;
    }
}


// resetObjRotation
// Set global savedrots to an identity matrix.
void resetObjRotation()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(90., 0.,0.,1.);
    angSun = 0.0;
    angPlanet = 0.0;
    angMoon = 0.0;
    glGetDoublev(GL_MODELVIEW_MATRIX, savedrots);
}

// myKeyboard
// The GLUT keyboard function
void myKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case ' ':     // Space: reset object rotation
            resetObjRotation();
            glutPostRedisplay();
            break;
        case 'q':   //ccw rotation of sun
            angSun += angstep;
            glutPostRedisplay();
            break;
        case 'Q':
            angSun += angstep;
            glutPostRedisplay();
            break;
        case 'w':   //cw rotation of sun
            angSun -= angstep;
            glutPostRedisplay();
            break;
        case 'W':
            angSun -= angstep;
            glutPostRedisplay();
            break;
        case 'a':   //ccw rotation of planet
            angPlanet += angstep;
            glutPostRedisplay();
            break;
        case 'A':
            angPlanet += angstep;
            glutPostRedisplay();
            break;
        case 's':   //cw rotation of planet
            angPlanet -= angstep;
            glutPostRedisplay();
            break;
        case 'S':
            angPlanet -= angstep;
            glutPostRedisplay();
            break;
        case 'z':   //ccw rotation of moon
            angMoon += angstep;
            glutPostRedisplay();
            break;
        case 'Z':
            angMoon += angstep;
            glutPostRedisplay();
            break;
        case 'x':   //cw rotation of moon
            angMoon -= angstep;
            glutPostRedisplay();
            break;
        case 'X':
            angMoon -= angstep;
            glutPostRedisplay();
            break;
        case ESCKEY:  // Esc: quit
            exit(0);
            break;
    }
}


// mySpecial
// The GLUT special function
void mySpecial(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_RIGHT:  // right: rotation
            glLoadIdentity();
            glRotated(angstep, 0.,1.,0.);
            glMultMatrixd(savedrots);
            glGetDoublev(GL_MODELVIEW_MATRIX, savedrots);
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:   // left: rotation
            glLoadIdentity();
            glRotated(-angstep, 0.,1.,0.);
            glMultMatrixd(savedrots);
            glGetDoublev(GL_MODELVIEW_MATRIX, savedrots);
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:     // up: rotation
            glLoadIdentity();
            glRotated(-angstep, 1.,0.,0.);
            glMultMatrixd(savedrots);
            glGetDoublev(GL_MODELVIEW_MATRIX, savedrots);
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:   // down: rotation
            glLoadIdentity();
            glRotated(angstep, 1.,0.,0.);
            glMultMatrixd(savedrots);
            glGetDoublev(GL_MODELVIEW_MATRIX, savedrots);
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
    // Standard perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60., double(w)/h, 0.1, 10.0);
    
    glMatrixMode(GL_MODELVIEW);  // Always go back to model/view mode
}


// init
// Initialize GL states & global data
// Called by main after window creation
void init()
{
    // Objects
    resetObjRotation();
    
    // OpenGL Stuff
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char ** argv)
{
    // Initialize OpenGL/GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    // Make a window
    glutInitWindowSize(startwinsize, startwinsize);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("CS 381 - Ann Tupek - Homework 4A");
    
    // Initialize GL states & register GLUT callbacks
    init();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myIdle);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecial);
    glutReshapeFunc(myReshape);
    
    // Do something
    glutMainLoop();
    
    return 0;
}


