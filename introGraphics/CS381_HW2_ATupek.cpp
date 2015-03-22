// CS381_Assignment2.cpp
// Ann Tupek
// 25 Sep 2014
//
// Graphical application that lets the user feed a bunny
//
// Basic structure based on clickdrag2.cpp & slider.cpp
// By Glenn G. Chappell

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
#include <iostream>
using std::cerr;
using std::endl;

#include <time.h> //for clock()
#include <algorithm>
using std::min;



// Global variables
// Keyboard
const int ESCKEY = 27;         // ASCII value of Escape

// Window/viewport
const int startwinsize = 600;  // Start window width & height (pixels)
int winw = 1, winh = 1;        // Window width, height (pixels)
                               //  (Initialize to avoid spurious errors)
double cam_xmin, cam_xmax, cam_ymin, cam_ymax;
                               // Viewport bdaries in world (cam coords)

// Mouse
double cam_mousex, cam_mousey;  // Mouse pos in cam coords
int draggedobj;                 // 0: not currently dragging
                                // 1: dragging carrot 1
                                // 2: dragging carrot 2
                                // 3: dragging carrot 3
// Objects

// Carrots
const double chalfside = 0.1; // carrot half side len (cam coords)
double  c1posx, c1posy,
        c2posx, c2posy,
        c3posx, c3posy; // x,y of 'center' of carrots (cam coords)
double  c1dragposx, c1dragposy,
        c2dragposx, c2dragposy,
        c3dragposx, c3dragposy; // Where carrots are dragged (cam coords)
                                // Valid when draggedobj == 1, 2, or 3
                                // May lie outside window; in this case
                                //  (c1posx, c1posy)
                                // or (c2posx, c2posy)
                                // or (c3posx, c3posy) is nearest point
                                //  with entire carrot in window.
bool bunnyNOM = false;  //show bunny2
bool c1exists = true;   //existential status of carrots
bool c2exists = true;
bool c3exists = true;
bool chewing = false;   //bunny chew animation
clock_t nomTime;
clock_t pickUpTime = clock();


// drawCarrot
// Draws a carrot in the x,y plane, centered at the origin
void drawCarrot()//the carrot
{
    GLdouble carrot[2*7] = {
        0.0, 0.25,
        -0.5, 0.5,
        -1.0, 0.5,
        -2.5, 0.0,
        -1.0, -0.5,
        -0.5, -0.5,
        0.0, -0.25};
    
    glVertexPointer(
                    2,
                    GL_DOUBLE,
                    2*sizeof(GLdouble),
                    carrot);
    
    glDisableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3d(1.0, 0.5, 0.0);
    glDrawArrays(GL_POLYGON, 0, 7);
    
    GLdouble carrotTop[2*14] = {
        0.0, 0.0,
        1.5, 0.0,
        0.0, 0.0,
        1.4, 0.2,
        0.0, 0.0,
        1.4, -0.2,
        0.0, 0.01,
        1.3, 0.3,
        0.0, -0.01,
        1.3, -0.3,
        0.0, 0.02,
        1.3, 0.4,
        0.0, -0.02,
        1.3, -0.4};
    
    glVertexPointer(
                    2,
                    GL_DOUBLE,
                    2*sizeof(GLdouble),
                    carrotTop);
    
    glDisableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3d(0.0, 1.0, 0.0);
    glDrawArrays(GL_LINES, 0, 14);
}

// drawBunny1
// Draws a bunny in the x,y plane, centered at the origin
void drawBunny1()
{
    GLdouble bunny1[2*50] = {
        -0.08, -0.291,
        0.149, -0.291,
        0.16, -0.273,
        0.14, -0.244,
        0.014, -0.238,
        0.114, -0.211,
        0.171, -0.147,
        0.186, -0.229,
        0.211, -0.287,
        0.266, -0.287,
        0.294, -0.276,
        0.266, -0.256,
        0.234, -0.133,
        0.246, 0.009,
        0.3, 0.089,
        0.403, 0.142,
        0.417, 0.156,
        0.366, 0.218,
        0.24, 0.3,
        0.209, 0.311,
        0.223, 0.46,
        0.209, 0.647,
        0.169, 0.684,
        0.146, 0.644,
        0.149, 0.424,
        0.103, 0.604,
        0.066, 0.673,
        0.029, 0.584,
        0.069, 0.373,
        0.103, 0.3,
        0.029, 0.227,
        0.009, 0.151,
        0.023, 0.1,
        -0.106, 0.06,
        -0.246, -0.009,
        -0.34, -0.118,
        -0.363, -0.18,
        -0.409, -0.118,
        -0.409, -0.176,
        -0.474, -0.144,
        -0.423, -0.189,
        -0.474, -0.213,
        -0.417, -0.213,
        -0.443, -0.264,
        -0.369, -0.236,
        -0.377, -0.282,
        -0.351, -0.238,
        -0.314, -0.282,
        -0.123, -0.291,
        -0.08, -0.291};
    
    glVertexPointer(
                    2,
                    GL_DOUBLE,
                    2*sizeof(GLdouble),
                    bunny1);
    
    glDisableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3d(1.0, 1.0, 1.0);
    glDrawArrays(GL_LINE_STRIP, 0, 50);
    
    //bunny's eye
    glColor3d(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    glVertex2d(0.25, 0.2);
    glEnd();
}

//drawBunny2
// Draws a bunny in the x,y plane, centered at the origin
void drawBunny2()
{
    GLdouble bunny2[2*68] = {
        -0.08, -0.296,
        0.14, -0.287,
        0.16, -0.262,
        0.131, -0.238,
        0, -0.236,
        0.111, -0.207,
        0.174, -0.138,
        0.209, -0.276,
        0.266, -0.264,
        0.306, -0.284,
        0.309, -0.244,
        0.254, -0.229,
        0.234, -0.142,
        0.24, -0.024,
        0.317, -0.067,
        0.417, -0.067,
        0.426, 0.007,
        0.369, -0.022,
        0.366, 0.029,
        0.329, -0.009,
        0.329, 0.04,
        0.271, 0.022,
        0.266, 0.082,
        0.249, 0.156,
        0.291, 0.431,
        0.326, 0.487,
        0.34, 0.44,
        0.369, 0.489,
        0.391, 0.433,
        0.414, 0.487,
        0.446, 0.387,
        0.431, 0.298,
        0.486, 0.373,
        0.483, 0.478,
        0.451, 0.542,
        0.431, 0.616,
        0.366, 0.66,
        0.26, 0.687,
        0.16, 0.649,
        0.063, 0.571,
        -0.097, 0.511,
        -0.277, 0.409,
        -0.057, 0.418,
        0.126, 0.511,
        -0.069, 0.364,
        -0.103, 0.309,
        0.029, 0.356,
        0.129, 0.411,
        0.129, 0.309,
        0.017, 0.244,
        0.02, 0.111,
        -0.117, 0.058,
        -0.274, -0.042,
        -0.357, -0.153,
        -0.397, -0.08,
        -0.403, -0.151,
        -0.523, -0.049,
        -0.443, -0.153,
        -0.56, -0.124,
        -0.417, -0.18,
        -0.563, -0.216,
        -0.403, -0.207,
        -0.503, -0.28,
        -0.369, -0.231,
        -0.4, -0.28,
        -0.346, -0.247,
        -0.294, -0.291,
        -0.08, -0.296};
    
    glVertexPointer(
                    2,
                    GL_DOUBLE,
                    2*sizeof(GLdouble),
                    bunny2);
    
    glDisableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3d(1.0, 1.0, 1.0);
    glDrawArrays(GL_LINE_STRIP, 0, 68);
    
    //bunny's eye
    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2d(0.2, 0.5);
    glEnd();
}

//timer for animation when idle
void timer(int extra)
{
    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

// myDisplay
// The GLUT display function
void myDisplay()
{
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw objects
    clock_t numTicks = clock()-nomTime;
    clock_t chewingPeriod = CLOCKS_PER_SEC/3;
    if(bunnyNOM)
        {
            if(numTicks % chewingPeriod >(chewingPeriod/2))
                {
                    chewing = true;
                }
            else
                {
                    chewing = false;
                }
            if(numTicks > 3*CLOCKS_PER_SEC)
                {
                    bunnyNOM = false;
                }
        }
    if (bunnyNOM && !chewing)
        {
            glPushMatrix();
            glTranslated(-0.75, -0.5, 0.0);
            glScaled(0.5, 0.5, 0.5);
            drawBunny2();
            glPopMatrix();
        }
    else
        {
            glPushMatrix();
            glTranslated(-0.75, -0.5, 0.0);
            glScaled(0.5, 0.5, 0.5);
            drawBunny1();
            glPopMatrix();
        }
    
    //for carrot rotation animation
    clock_t rotateTime = CLOCKS_PER_SEC/4;
    clock_t elapsedTime = clock() - pickUpTime;
    clock_t minTime = min(rotateTime, elapsedTime);
    double carrotRotation = 90.0-(90.0*(double)minTime/(double)rotateTime);

    //drawCarrot 1
    if(c1exists)
        {
            glLoadIdentity();
            glTranslated(c1posx, c1posy, 0.0);
            if(draggedobj !=1)
                {
                    glRotated(90.0, 0.0, 0.0, 1.0);
                }
            else
                {
                    glRotated(carrotRotation, 0.0, 0.0, 1.0);
                }
        
            glScaled(chalfside, chalfside, chalfside);
            drawCarrot();
        }
    
    //drawCarrot2
    if(c2exists)
        {
            glLoadIdentity();
            glTranslated(c2posx, c2posy, 0.0);
            if(draggedobj != 2)
                {
                    glRotated(90.0, 0.0, 0.0, 1.0);
                }
            else
                {
                    glRotated(carrotRotation, 0.0, 0.0, 1.0);
                }
            glScaled(chalfside, chalfside, chalfside);
            drawCarrot();
        }
    
    //drawCarrot3
    if(c3exists)
        {
            glLoadIdentity();
            glTranslated(c3posx, c3posy, 0.0);
            if(draggedobj != 3)
                {
                    glRotated(90.0, 0.0, 0.0, 1.0);
                }
            else
                {
                    glRotated(carrotRotation, 0.0, 0.0, 1.0);
                }
            glScaled(chalfside, chalfside, chalfside);
            drawCarrot();
        }

    //ground
    glLoadIdentity();
    glColor3d(0.0, 0.5, 0.2);
    glBegin(GL_QUADS);
    glVertex2d(cam_xmin, cam_ymin);
    glVertex2d(cam_xmin,  -0.65);
    glVertex2d(cam_xmax,  -0.65);
    glVertex2d(cam_xmax, cam_ymin);
    glEnd();
    
    // Draw documentation
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);  // Set up simple ortho projection
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0., double(winw), 0., double(winh));
    glColor3d(0., 0., 0.);        // Black text
    BitmapPrinter p(20., winh-20., 20.);
    p.print("Feed The Bunny!");
    p.print("Esc      Quit");
    if(!c1exists && !c2exists && !c3exists)
    {
        glColor3d(0., 0., 0.);
        BitmapPrinter p(20., winh-60., 20.);
        p.print("NO MORE CARROTS!");
    }
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


// myKeyboard
// The GLUT keyboard function
void myKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ESCKEY:  // Esc: quit
        exit(0);
        break;
    }
}


// fixCarrot
// If carrots [center (c1posx, c1posy), half width = chalfside]
//  are not entirely in windows [boundaries cam_xmin, cam_xmax],
//  then place carrots into this region, at
//  nearest possible location.
void fixCarrot1()
{
    if (c1posx < cam_xmin+chalfside)
        c1posx = cam_xmin+chalfside;
    if (c1posx > cam_xmax-chalfside)
        c1posx = cam_xmax-chalfside;
    if (c1posy < -0.6)
        c1posy = -0.6; //don't let carrot go underground
    if (c1posy > cam_ymax-chalfside)
        c1posy = cam_ymax-chalfside;
}
void fixCarrot2()
{
    if (c2posx < cam_xmin+chalfside)
        c2posx = cam_xmin+chalfside;
    if (c2posx > cam_xmax-chalfside)
        c2posx = cam_xmax-chalfside;
    if (c2posy < -0.6)
        c2posy = -0.6; //don't let the carrot go underground
    if (c2posy > cam_ymax-chalfside)
        c2posy = cam_ymax-chalfside;
}
void fixCarrot3()
{
    if (c3posx < cam_xmin+chalfside)
        c3posx = cam_xmin+chalfside;
    if (c3posx > cam_xmax-chalfside)
        c3posx = cam_xmax-chalfside;
    if (c3posy < -0.6)
        c3posy = -0.6; //don't let the carrot go underground
    if (c3posy > cam_ymax-chalfside)
        c3posy = cam_ymax-chalfside;
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
    // Save max/min x/y coords in globals
    // Projection is orthographic. Aspect ratio is correct,
    // and region -1..1 in x, y always just fits in viewport.
    if (w > h)
    {
        cam_xmin = -double(w)/h;
        cam_xmax = double(w)/h;
        cam_ymin = -1.;
        cam_ymax = 1.;
    }
    else
    {
        cam_xmin = -1.;
        cam_xmax = 1.;
        cam_ymin = -double(h)/w;
        cam_ymax = double(h)/w;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(cam_xmin, cam_xmax, cam_ymin, cam_ymax);

    glMatrixMode(GL_MODELVIEW);  // Always go back to model/view mode

    // Move carrots into the window, if they are outside
    fixCarrot1();
    fixCarrot2();
    fixCarrot3();
}


// saveMouse
// Given mouse pos in GLUT format; computes mouse pos in cam coords,
//  saves it in globals cam_mousex, cam_mousey.
// Uses globals winw, winh, cam_xmin, cam_xmax, cam_ymin, cam_ymax.
void saveMouse(int x, int y)
{
    double t;  // Intermediate value of lirping

    t = double(x) / winw;
    cam_mousex = cam_xmin + t * (cam_xmax - cam_xmin);

    t = double(y) / winh;
    cam_mousey = cam_ymax + t * (cam_ymin - cam_ymax);
}


// myMouse
// The GLUT mouse function
void myMouse(int button, int state, int x, int y)
{
    // Save old mouse pos, for relative mouse-movement computation
    double old_cam_mousex = cam_mousex;
    double old_cam_mousey = cam_mousey;
    
    // Find mouse pos in cam coords (saved in cam_mousex, cam_mousey)
    saveMouse(x, y);
    
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)  // Left mouse down
        {
            // Extent test for carrot 1
            if (cam_mousex >= c1posx-chalfside
                && cam_mousex <= c1posx+chalfside
                && cam_mousey >= c1posy-chalfside
                && cam_mousey <= c1posy+chalfside)
            {
                // We have a mouse-down on carrot 1
                draggedobj = 1;
                pickUpTime = clock();
                c1dragposx = c1posx;
                c1dragposy = c1posy;
                glutPostRedisplay();
            }
            // Extent test for carrot 2
            if (cam_mousex >= c2posx-chalfside
                && cam_mousex <= c2posx+chalfside
                && cam_mousey >= c2posy-chalfside
                && cam_mousey <= c2posy+chalfside)
            {
                // We have a mouse-down on carrot 2
                draggedobj = 2;
                pickUpTime = clock();
                c2dragposx = c2posx;
                c2dragposy = c2posy;
                glutPostRedisplay();
            }
            // Extent test for carrot 3
            if (cam_mousex >= c3posx-chalfside
                && cam_mousex <= c3posx+chalfside
                && cam_mousey >= c3posy-chalfside
                && cam_mousey <= c3posy+chalfside)
            {
                // We have a mouse-down on carrot 3
                draggedobj = 3;
                pickUpTime = clock();
                c3dragposx = c3posx;
                c3dragposy = c3posy;
                glutPostRedisplay();
            }
        }
        else // Left mouse up
        {
            if (draggedobj == 1)  // We were dragging carrot 1
            {
                // Move square 1 by relative mouse movement
                c1dragposx += (cam_mousex - old_cam_mousex);
                c1dragposy += (cam_mousey - old_cam_mousey);
                c1posx = c1dragposx;
                c1posy = c1dragposy;
                fixCarrot1();
                glutPostRedisplay();
            }
            if (draggedobj == 2)  // We were dragging carrot 2
            {
                // Move square 1 by relative mouse movement
                c2dragposx += (cam_mousex - old_cam_mousex);
                c2dragposy += (cam_mousey - old_cam_mousey);
                c2posx = c2dragposx;
                c2posy = c2dragposy;
                fixCarrot2();
                glutPostRedisplay();
            }
            if (draggedobj == 3)  // We were dragging carrot 3
            {
                // Move square 1 by relative mouse movement
                c3dragposx += (cam_mousex - old_cam_mousex);
                c3dragposy += (cam_mousey - old_cam_mousey);
                c3posx = c3dragposx;
                c3posy = c3dragposy;
                fixCarrot3();
                glutPostRedisplay();
            }
            draggedobj = 0;
        }
    }
}


// myMotion
// The GLUT motion function
void myMotion(int x, int y)
{
    // Save old mouse pos, for relative mouse-movement computation
    double old_cam_mousex = cam_mousex;
    double old_cam_mousey = cam_mousey;
    
    // Find mouse pos in cam coords (saved in cam_mousex, cam_mousey)
    saveMouse(x, y);
    double bunnyMouthxRight = -0.35; //for feeding bunny
    double bunnyMouthyTop = -0.35; //for feeding bunny
    
    if (draggedobj == 1)  // We are dragging carrot 1
    {
        // Move carrot 1 by relative mouse movement
        c1dragposx += (cam_mousex - old_cam_mousex);
        c1dragposy += (cam_mousey - old_cam_mousey);
        c1posx = c1dragposx;
        c1posy = c1dragposy;
       if(c1posx<=bunnyMouthxRight && c1posy <= bunnyMouthyTop)
        {
            nomTime = clock();
            bunnyNOM = true;
            c1exists = false;
        }
        fixCarrot1();
        glutPostRedisplay();
    }
    if (draggedobj == 2)  // We are dragging carrot 2
    {
        // Move carrot 2 by relative mouse movement
        c2dragposx += (cam_mousex - old_cam_mousex);
        c2dragposy += (cam_mousey - old_cam_mousey);
        c2posx = c2dragposx;
        c2posy = c2dragposy;
        if(c2posx<=bunnyMouthxRight && c2posy <= bunnyMouthyTop)
        {
            nomTime = clock();
            bunnyNOM = true;
            c2exists = false;
        }
        fixCarrot2();
        glutPostRedisplay();
    }
    if (draggedobj == 3)  // We are dragging carrot 3
    {
        // Move carrot 3 by relative mouse movement
        c3dragposx += (cam_mousex - old_cam_mousex);
        c3dragposy += (cam_mousey - old_cam_mousey);
        c3posx = c3dragposx;
        c3posy = c3dragposy;
        if(c3posx<=bunnyMouthxRight && c3posy <= bunnyMouthyTop)
        {
            nomTime = clock();
            bunnyNOM = true;
            c3exists = false;
        }
        fixCarrot3();
        glutPostRedisplay();
    }
}


// init
// Initialize GL states & global data
// Called by main after window creation
void init()
{
    // Mouse
    draggedobj = 0;
    cam_mousex = 0.0;
    cam_mousey = 0.0;

    // Objects
    c1posx = 0.6;
    c1posy = -0.6;
    c2posx = 0.4;
    c2posy = -0.6;
    c3posx = 0.2;
    c3posy = -0.6;

    // OpenGL Stuff
    // (Nothing here)
    glLineWidth(3);
    glPointSize(5.0f);
}


int main(int argc, char ** argv)
{
    // Initialize OpenGL/GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Make a window
    glutInitWindowSize(startwinsize, startwinsize);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("CS 381 - Ann Tupek - Assignment 2");

    // Initialize GL states & register GLUT callbacks
    init();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myIdle);
    glutKeyboardFunc(myKeyboard);
    glutReshapeFunc(myReshape);
    glutMouseFunc(myMouse);
    glutMotionFunc(myMotion);
    glutTimerFunc(0, timer, 0); //for animation while idle
    // Do something
    glutMainLoop();

    return 0;
}

