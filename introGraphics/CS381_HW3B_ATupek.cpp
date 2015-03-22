// CS381_HW3_B_ATupek.cpp
// Ann Tupek
// Due 10/07/14
//
// HW 3
// Move a gray gem around a maze, other gems rotate
// (gray gem's rotation was jerky, so I removed it)
// Couldn't get collision-detection working for walls,
// collision-detection only at borders of maze :-(
//
// Structure based on manip2.cpp by Glenn G Chappell
// drawSquare() by Glenn G Chappell, modified so side length = 1

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


// Global variables
// Keyboard
const int ESCKEY = 27;         // ASCII value of Escape

// Window/viewport
const int startwinsize = 600;  // Start window width & height (pixels)
int winw = 1, winh = 1;        // Window width, height (pixels)
//  (Initialize to avoid spurious errors)

// Objects
double angstep = 10.0;   // for rotation

double posx = 0.0;
double posy = 0.25;

bool gem1exists = true;
bool gem2exists = true;
bool gem3exists = true;

double gem1x = -1.0;
double gem1y = 3.25;
double gem2x = 4.0;
double gem2y = -0.75;
double gem3x = 5.0;
double gem3y = 1.25;

// drawSquare
// Draws a filled square, using current GL states,
//  in the x,y plane, centered at the origin, aligned w/ x,y axes,
//  with side 1.
void drawSquare()
{
    glBegin(GL_POLYGON);
    glVertex2d(-0.5, -0.5);
    glVertex2d( 0.5, -0.5);
    glVertex2d( 0.5,  0.5);
    glVertex2d(-0.5,  0.5);
    glEnd();
}

// draws floor of maze
void drawFloor()
{
    glPushMatrix();
    glRotated(90.0, 1.0, 0.0, 0.0);
    glTranslated(1.0, 0.5, -0.5);
    glScaled(9.0, 8.0, 1.0);
    glColor3d(1.0, 1.0, 1.0);
    drawSquare();
    glPopMatrix();
    
}

//horizontal walls
const int NUM_HORIZONTAL_WALLS = 15;

double wallPosAndLength[NUM_HORIZONTAL_WALLS][3] = {
    1.0, 4.5, 9.0,
    -1.5, 3.5, 2.0,
    2.5, 3.5, 4.0,
    2.0, 2.5, 3.0,
    -1.0, 2.5, 1.0,
    1.0, 1.5, 3.0,
    5.0, 0.5, 1.0,
    1.0, 0.5, 1.0,
    4.0, -0.5, 1.0,
    2.0, -0.5, 1.0,
    0.0, -0.5, 1.0,
    -2.0, -0.5, 1.0,
    1.0, -1.5, 5.0,
    1.0, -2.5, 7.0,
    1.0, -3.5, 9.0
};

void drawWalls() {
    
    for(int ii = 0; ii < NUM_HORIZONTAL_WALLS; ++ii) {
        glPushMatrix();
        glTranslated(wallPosAndLength[ii][0], 0.0, wallPosAndLength[ii][1]);
        glScaled(wallPosAndLength[ii][2], 1.0, 1.0);
        glColor3d(0.0, 0.0, 0.0);
        drawSquare();
        glPopMatrix();
    }
}

//vertical walls
const int NUM_VERTICAL_WALLS = 14;

double wallPosAndLengthV[NUM_VERTICAL_WALLS][3] = {
    -3.5, 0.5, 8.0,
    5.5, 0.5, 8.0,
    -2.5, -1.5, 2.0,
    -2.5, 2.0, 3.0,
    -1.5, 1.0, 3.0,
    -0.5, 3.0, 1.0,
    -0.5, 0.5, 2.0,
    0.5, 0.0, 1.0,
    0.5, 3.0, 1.0,
    2.5, 0.5, 2.0,
    3.5, -1.0, 1.0,
    3.5, 1.5, 2.0,
    4.5, -1.5, 2.0,
    4.5, 2.0, 3.0
};

void drawWalls2() {
    
    for(int ii = 0; ii < NUM_VERTICAL_WALLS; ++ii) {
        glPushMatrix();
        glRotated(90.0, 0.0, 1.0, 0.0);
        glTranslated(-wallPosAndLengthV[ii][1], 0.0, wallPosAndLengthV[ii][0]);
        glScaled(wallPosAndLengthV[ii][2], 1.0, 1.0);
        glColor3d(0.0, 0.0, 0.0);
        drawSquare();
        glPopMatrix();
    }
}

//for gems
//draw top face of gem
void drawTop()
{
    GLdouble topData[3 * 4] =
    {
        -0.10, -0.10, 0.0,  //vertex 1
        -0.10, 0.10, 0.0, //vertex 2
        0.10, 0.10, 0.0, //vertex 3
        0.10, -0.10, 0.0 //vertex 4
    };
    
    glVertexPointer(
                    2,              //components per vertex
                    GL_DOUBLE,      //type of component
                    3 * sizeof(GLdouble),  //stride
                    topData);
    
    glDisableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3d(0.0, 1.0, 0.0);
    glDrawArrays(GL_POLYGON, 0, 4);
    
}

//draw side face of gem
void drawSide()
{
    GLdouble sideData[(3+3) * 5] =
    {
        0.0, 1.0, 0.0, //color v1
        -0.15, -0.15, -0.15, //vertex 1
        0.0, 1.0, 1.0, //color v2
        -0.1, -0.1, 0.0,     //vertex 2
        0.0, 0.0, 1.0, //color v3
        0.0, -0.15, -0.15,   //vertex 3
        0.0, 1.0, 1.0, //color v4
        0.1, -0.1, 0.0,      //vertex 4
        0.0, 1.0, 0.0, //color v5
        0.15, -0.15, -0.15   //vertex 5
    };
    
    glColorPointer(3, GL_DOUBLE, (3+3)*sizeof(GLdouble), sideData);
    
    glVertexPointer(
                    3,              //components per vertex
                    GL_DOUBLE,      //type of component
                    (3+3) * sizeof(GLdouble),  //stride
                    sideData+3);
    
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
}

//draw bottom face of gem
void drawBottom()
{
    GLdouble bottomData[(3+3) * 3] =
    {
        0.0, 1.0, 1.0,
        -0.15, -0.15, -0.15, //vertex 1
        0.0, 1.0, 0.0,
        0.0, 0.0, -0.3,      //vertex 2
        0.0, 0.0, 1.0,
        0.15, -0.15, -0.15   //vertex 3
    };
    
    glColorPointer(3, GL_DOUBLE, (3+3)*sizeof(GLdouble), bottomData);
    
    glVertexPointer(
                    3,              //components per vertex
                    GL_DOUBLE,      //type of component
                    (3+3) * sizeof(GLdouble),  //stride
                    bottomData+3);
    
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

// drawGem0()
void drawGem0()
{

    //top face
    drawTop();
    
    //side face 1
    drawSide();
    
    //side face 2
    glPushMatrix();
    glRotated(90.0, 0.0, 0.0, 1.0);
    drawSide();
    glPopMatrix();
    
    //side face 3
    glPushMatrix();
    glRotated(180.0, 0.0, 0.0, 1.0);
    drawSide();
    glPopMatrix();
    
    //side face 4
    glPushMatrix();
    glRotated(-90., 0.0, 0.0, 1.0);
    drawSide();
    glPopMatrix();
    
    //bottom face 1
    drawBottom();
    
    //bottom face 2
    glPushMatrix();
    glRotated(90., 0.0, 0.0, 1.0);
    drawBottom();
    glPopMatrix();
    
    //bottom face 3
    glPushMatrix();
    glRotated(180., 0.0, 0.0, 1.0);
    drawBottom();
    glPopMatrix();
    
    //bottom face 4
    glPushMatrix();
    glRotated(-90., 0.0, 0.0, 1.0);
    drawBottom();
    glPopMatrix();
}

void drawGem1()
{
    glPushMatrix();
    glTranslated(gem1x, 0.0, gem1y);
    glRotated(angstep, 0.0, 0.0, 1.0);
    glScaled(2.0, 2.0, 2.0);
    drawGem0();
    glPopMatrix();
}

void drawGem2()
{
    glPushMatrix();
    glTranslated(gem2x, 0.0, gem2y);
    glRotated(angstep, 0.0, 0.0, 1.0);
    glScaled(2.0, 2.0, 2.0);
    drawGem0();
    glPopMatrix();
}

void drawGem3()
{
    glPushMatrix();
    glTranslated(gem3x, 0.0, gem3y);
    glRotated(angstep, 0.0, 0.0, 1.0);
    glScaled(2.0, 2.0, 2.0);
    drawGem0();
    glPopMatrix();
}

//top of gray gem
void drawTopG()
{
    GLdouble topData[3 * 4] =
    {
        -0.10, -0.10, 0.0,  //vertex 1
        -0.10, 0.10, 0.0, //vertex 2
        0.10, 0.10, 0.0, //vertex 3
        0.10, -0.10, 0.0 //vertex 4
    };
    
    glVertexPointer(
                    2,              //components per vertex
                    GL_DOUBLE,      //type of component
                    3 * sizeof(GLdouble),  //stride
                    topData);
    
    glDisableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3d(0.5, 0.5, 0.5);
    glDrawArrays(GL_POLYGON, 0, 4);
    
}

//side of gray gem
void drawSideG()
{
    GLdouble sideData[(3+3) * 5] =
    {
        0.0, 0.0, 0.0, //color v1
        -0.15, -0.15, -0.15, //vertex 1
        0.5, 0.5, 0.5, //color v2
        -0.1, -0.1, 0.0,     //vertex 2
        1.0, 1.0, 1.0, //color v3
        0.0, -0.15, -0.15,   //vertex 3
        0.5, 0.5, 0.5, //color v4
        0.1, -0.1, 0.0,      //vertex 4
        0.0, 0.0, 0.0, //color v5
        0.15, -0.15, -0.15   //vertex 5
    };
    
    glColorPointer(3, GL_DOUBLE, (3+3)*sizeof(GLdouble), sideData);
    
    glVertexPointer(
                    3,              //components per vertex
                    GL_DOUBLE,      //type of component
                    (3+3) * sizeof(GLdouble),  //stride
                    sideData+3);
    
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
}

//bottom of gray gem
void drawBottomG()
{
    GLdouble bottomData[(3+3) * 3] =
    {
        1.0, 1.0, 1.0,
        -0.15, -0.15, -0.15, //vertex 1
        0.0, 0.0, 0.0,
        0.0, 0.0, -0.3,      //vertex 2
        0.5, 0.5, 0.5,
        0.15, -0.15, -0.15   //vertex 3
    };
    
    glColorPointer(3, GL_DOUBLE, (3+3)*sizeof(GLdouble), bottomData);
    
    glVertexPointer(
                    3,              //components per vertex
                    GL_DOUBLE,      //type of component
                    (3+3) * sizeof(GLdouble),  //stride
                    bottomData+3);
    
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

// drawGemG()
void drawGemG()
{
    
    //top face
    drawTopG();
    
    //side face 1
    drawSideG();
    
    //side face 2
    glPushMatrix();
    glRotated(90.0, 0.0, 0.0, 1.0);
    drawSideG();
    glPopMatrix();
    
    //side face 3
    glPushMatrix();
    glRotated(180.0, 0.0, 0.0, 1.0);
    drawSideG();
    glPopMatrix();
    
    //side face 4
    glPushMatrix();
    glRotated(-90., 0.0, 0.0, 1.0);
    drawSideG();
    glPopMatrix();
    
    //bottom face 1
    drawBottomG();
    
    //bottom face 2
    glPushMatrix();
    glRotated(90., 0.0, 0.0, 1.0);
    drawBottomG();
    glPopMatrix();
    
    //bottom face 3
    glPushMatrix();
    glRotated(180., 0.0, 0.0, 1.0);
    drawBottomG();
    glPopMatrix();
    
    //bottom face 4
    glPushMatrix();
    glRotated(-90., 0.0, 0.0, 1.0);
    drawBottomG();
    glPopMatrix();
}

//gray gem
void drawGem4()
{
    glPushMatrix();
    glTranslated(posx, 0.0, posy);
    glScaled(2.0, 2.0, 2.0);
    drawGemG();
    glPopMatrix();
    
}

// drawMaze
void drawMaze()
{
    drawWalls();
    drawWalls2();
    drawFloor();
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
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    double currTime = glutGet(GLUT_ELAPSED_TIME)%500;
    angstep=(currTime/1000.0/2*360);
    
    // Draw objects
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glTranslated(-1.0, -1.0, -9.);
    glRotated(-90.0, 1.0, 0.0, 0.0);
    drawMaze();
    
    if(gem1exists)
    {
        drawGem1();
    }
    
    if(gem2exists)
    {
        drawGem2();
    }
    
    if(gem3exists)
    {
        drawGem3();
    }
    
    drawGem4();
    
    // Draw documentation
    glDisable(GL_DEPTH_TEST);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);  // Set up simple ortho projection
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0., double(winw), 0., double(winh));
    glColor3d(0., 0., 0.);        // Black text
    BitmapPrinter p(20., winh-20., 20.);
    p.print("Arrows   Move the Gray Gem");
    p.print("Z        Return Gray Gem to Starting Position");
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

// myKeyboard
// The GLUT keyboard function
void myKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'z':     // Z: reset rotations
        case 'Z':
            posx = 0.0;
            posy = 0.25;
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
        case GLUT_KEY_RIGHT:  // move right
            posx += 0.1;
            if (posx >= 5.0)
                posx = 5.0;
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:   // move left
            posx -= 0.1;
            if (posx <= -3.0)
                posx = -3.0;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:     // move up
            posy += 0.1;
            if (posy >= 4.25)
                posy = 4.25;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:   // move down
            posy -= 0.1;
            if (posy <= -2.75)
                posy = -2.75;
            glutPostRedisplay();
            break;
    }

    //if gray gem reaches other gems, remove them
    if (posx <= -0.8 && posx >= -1.2 &&
        posy >= 3.05 && posy <= 3.45)
    {
        gem1exists = false;
        glutPostRedisplay();
    }
    if (posx >= 3.8 && posx <= 4.2 &&
        posy <= -0.55 && posy >= -0.95)
    {
        gem2exists = false;
        glutPostRedisplay();
    }
    if (posx >= 4.8 && posx <= 5.2 &&
        posy >= 1.05 && posy <= 1.45)
    {
        gem3exists = false;
        glutPostRedisplay();
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
    gluPerspective(60., double(w)/h, 0.1, 50.0);
    
    glMatrixMode(GL_MODELVIEW);  // Always go back to model/view mode
}

// init
// Initialize GL states & global data
// Called by main after window creation
void init()
{
    // Objects
    glMatrixMode(GL_MODELVIEW);
    
    // OpenGL Stuff
    // (Nothing here)
}


int main(int argc, char ** argv)
{
    //startTime = clock();
    // Initialize OpenGL/GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    // Make a window
    glutInitWindowSize(startwinsize, startwinsize);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("CS 381 - Ann Tupek HW 3");
    
    // Initialize GL states & register GLUT callbacks
    init();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myIdle);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecial);
    glutReshapeFunc(myReshape);
    glutTimerFunc(0, timer, 0); //for animation while idle

    
    // Do something
    glutMainLoop();
    
    return 0;
}

