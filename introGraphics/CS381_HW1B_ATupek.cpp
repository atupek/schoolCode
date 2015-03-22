// CS381_Assignment1.cpp
// Ann Tupek
// 14 Sep 2014
//
// Graphical application that lets the user change between three seasons
//
// Basic structure based on sample2d.cpp & Kbtext2.cpp
// By Glenn G. Chappell

/*
 The GL Primtives & where they are used, so you don't have to search for them:
    GL_POINTS: snowflakes, bunny's eye
    GL_LINES: tree branches
    GL_LINE_STRIP: tree branches
    GL_LINE_LOOP: bunny
    GL_TRIANGLES: branches
    GL_TRIANGLE_STRIP: ground
    GL_TRIANGLE_FAN: summer leaf-clusters, fall leaf 1 & 3
    GL_QUAD_STRIP: tree trunk
    GL_POLYGON: fall leaf 2
*/
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
#include <sstream>
using std::ostringstream;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;


// Global variables
// Keyboard
const int ESCKEY = 27;         // ASCII value of Escape

// Window/viewport
const int startwinsize = 600;  // Start window width & height (pixels)

//some horribly-named variables for duplicating the placement of a leaf...
//I know a better way to do this must exist...
GLdouble x1 = -0.7;
GLdouble y1 = 0.1;
//and for making it snow
GLdouble y2 = 0;

enum Season_t {SUMMER, FALL, WINTER};
Season_t Season;

// myDisplay
// The GLUT display function
void myDisplay()
{
    // Clear the viewport
    glClearColor(0.0f, 0.7f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //the tree trunk
    glColor3d(0.5, 0.5, 0.0);
    glBegin(GL_QUAD_STRIP);
    glVertex2d(0.5, 0.1);
    glVertex2d(0.55, 0.1);
    glVertex2d(0.5, 0.23);
    glVertex2d(0.55, 0.23);
    glVertex2d(0.5, 0.95);
    glVertex2d(0.525, 0.56);
    glEnd();
    
    //some branches
    glColor3d(0.5, 0.5, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2d(0.5, 0.36);
    glVertex2d(0.5, 0.4);
    glVertex2d(0.7, 0.4);
    glVertex2d(0.5, 0.4);
    glVertex2d(0.5, 0.43);
    glVertex2d(0.3, 0.5);
    glVertex2d(0.5, 0.5);
    glVertex2d(0.5, 0.53);
    glVertex2d(0.65, 0.6);
    glVertex2d(0.5, 0.6);
    glVertex2d(0.5, 0.63);
    glVertex2d(0.35, 0.63);
    glVertex2d(0.5, 0.7);
    glVertex2d(0.5, 0.73);
    glVertex2d(0.6, 0.76);
    glVertex2d(0.5, 0.73);
    glVertex2d(0.5, 0.76);
    glVertex2d(0.35, 0.8);
    glVertex2d(0.5, 0.83);
    glVertex2d(0.5, 0.86);
    glVertex2d(0.55, 0.86);
    glEnd();
    
    //more branch stuff
    glColor3d(0.5, 0.5, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2d(0.65, 0.4);
    glVertex2d(0.8, 0.4);
    glVertex2d(0.9, 0.36);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex2d(0.63, 0.59);
    glVertex2d(0.8, 0.63);
    glVertex2d(0.9, 0.6);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex2d(0.58, 0.75);
    glVertex2d(0.8, 0.8);
    glVertex2d(0.95, 0.73);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex2d(0.6, 0.9);
    glVertex2d(0.55, 0.86);
    glVertex2d(0.65, 0.83);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex2d(0.355, 0.8);
    glVertex2d(0.2, 0.76);
    glVertex2d(0.15, 0.7);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex2d(0.355, 0.63);
    glVertex2d(0.15, 0.6);
    glVertex2d(0.1, 0.56);
    glEnd();
    
    //and yet more branch stuff...
    glColor3d(0.5, 0.5, 0.0);
    glBegin(GL_LINES);
    glVertex2d(0.8, 0.63);
    glVertex2d(0.85, 0.66);
    glVertex2d(0.8, 0.8);
    glVertex2d(0.9, 0.83);
    glVertex2d(0.5, 0.86);
    glVertex2d(0.45, 0.90);
    glVertex2d(0.2, 0.76);
    glVertex2d(0.1, 0.8);
    glVertex2d(0.15, 0.6);
    glVertex2d(.05, 0.6);
    glVertex2d(0.31, 0.495);
    glVertex2d(0.2, 0.46);
    glEnd();
    
    //a bunny rabbit
    glColor3d(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(0.4, 0.1);
    glVertex2d(0.45, 0.1);
    glVertex2d(0.45, 0.15);
    glVertex2d(0.47, 0.15);
    glVertex2d(0.47, 0.17);
    glVertex2d(0.45, 0.17);
    glVertex2d(0.45, 0.19);
    glVertex2d(0.445, 0.19);
    glVertex2d(0.445, 0.15);
    glVertex2d(0.412, 0.112);
    glVertex2d(0.4, 0.112);
    glEnd();
    
    //the bunny's eye
    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2d(0.455, 0.163);
    glEnd();
    
    /*============================
                SUMMER
    =============================*/
    if(Season == SUMMER)
    {
    //the ground in summer
    glColor3d(0.0, 0.5, 0.5);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2d(0.0, 0.0);
    glColor3d(0.0, 1.0, 0.0);
    glVertex2d(0.3, 0.06);
    glColor3d(0.0, 0.5, 0.5);
    glVertex2d(0.3, 0.0);
    glColor3d(0.0, 1.0, 0.0);
    glVertex2d(0.4, 0.1);
    glColor3d(0.0, 0.5, 0.5);
    glVertex2d(0.4, 0.0);
    glColor3d(0.0, 1.0, 0.0);
    glVertex2d(0.6, 0.1);
    glColor3d(0.0, 0.5, 0.5);
    glVertex2d(0.6, 0.0);
    glColor3d(0.0, 1.0, 0.0);
    glVertex2d(0.75, 0.06);
    glColor3d(0.0, 0.5, 0.5);
    glVertex2d(0.75, 0.0);
    glColor3d(0.0, 1.0, 0.0);
    glVertex2d(0.85, .03);
    glColor3d(0.0, 0.5, 0.5);
    glVertex2d(1.0, 0.0);
    glEnd();
    
    //some leaf clusters using vertex arrays
    GLdouble leafCluster1[(3+2)*7] = {
        0.0, 1.0, 0.0,
        0.7, 0.4,
        0.0, 0.5, 0.5,
        0.8, 0.46,
        0.0, 1.0, 0.0,
        0.9, 0.46,
        0.0, 0.5, 0.5,
        1.0, 0.4,
        0.0, 1.0, 0.0,
        1.0, 0.3,
        0.0, 0.5, 0.5,
        0.9, 0.23,
        0.0, 1.0, 0.0,
        0.8, 0.26};
    
    glColorPointer(
                    3,
                    GL_DOUBLE,
                    (3+2)*sizeof(GLdouble),
                    leafCluster1);
    
    glVertexPointer(
                    2,
                    GL_DOUBLE,
                    (3+2)*sizeof(GLdouble),
                    leafCluster1+3);
    
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 7);
    
    GLdouble leafCluster2[(3+2)*7] = {
        0.0, 1.0, 0.0,
        0.65, 0.6,
        0.0, 0.5, 0.5,
        0.75, 0.7,
        0.0, 1.0, 0.0,
        0.8, 0.66,
        0.0, 0.5, 0.5,
        0.9, 0.66,
        0.0, 1.0, 0.0,
        0.95, 0.63,
        0.0, 0.5, 0.5,
        0.9, 0.56,
        0.0, 1.0, 0.0,
        0.95, 0.5};
    
    glColorPointer(
                    3,
                    GL_DOUBLE,
                    (3+2)*sizeof(GLdouble),
                    leafCluster2);
    
    glVertexPointer(
                    2,
                    GL_DOUBLE,
                    (3+2)*sizeof(GLdouble),
                    leafCluster2+3);
    
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 7);
    
    GLdouble leafCluster3[(3+2)*6] = {
        0.0, 1.0, 0.0,
        0.6, 0.76,
        0.0, 0.5, 0.5,
        0.85, 0.86,
        0.0, 1.0, 0.0,
        0.95, 0.83,
        0.0, 0.5, 0.5,
        0.9, 0.8,
        0.0, 1.0, 0.0,
        1.0, 0.73,
        0.0, 0.5, 0.5,
        0.95, 0.7};
    
    glColorPointer(
                    3,
                    GL_DOUBLE,
                    (3+2)*sizeof(GLdouble),
                    leafCluster3);
    
    glVertexPointer(
                    2,
                    GL_DOUBLE,
                    (3+2)*sizeof(GLdouble),
                    leafCluster3+3);
    
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
    
    GLdouble leafCluster4[(3+2)*9] = {
        0.0, 1.0, 0.0,
        0.5, 0.83,
        0.0, 0.5, 0.5,
        0.4, 0.86,
        0.0, 1.0, 0.0,
        0.35, 0.93,
        0.0, 0.5, 0.5,
        0.45, 0.93,
        0.0, 1.0, 0.0,
        0.5, 0.96,
        0.0, 0.5, 0.5,
        0.55, 0.93,
        0.0, 1.0, 0.0,
        0.65, 0.93,
        0.0, 0.5, 0.5,
        0.7, 0.86,
        0.0, 1.0, 0.0,
        0.65, 0.8};
    
    glColorPointer(
                    3,
                    GL_DOUBLE,
                    (3+2)*sizeof(GLdouble),
                    leafCluster4);
    
    glVertexPointer(
                    2,
                    GL_DOUBLE,
                    (3+2)*sizeof(GLdouble),
                    leafCluster4+3);
    
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 9);
    
    GLdouble leafCluster5[(3+2)*7] = {
        0.0, 1.0, 0.0,
        0.35, 0.8,
        0.0, 0.5, 0.5,
        0.35, 0.73,
        0.0, 1.0, 0.0,
        0.25, 0.66,
        0.0, 0.5, 0.5,
        0.15, 0.66,
        0.0, 1.0, 0.0,
        0.05, 0.73,
        0.0, 0.5, 0.5,
        0.1, 0.8,
        0.0, 1.0, 0.0,
        0.15, 0.86};
    
    glColorPointer(
                    3,
                    GL_DOUBLE,
                    (3+2)*sizeof(GLdouble),
                    leafCluster5);
    
    glVertexPointer(
                    2,
                    GL_DOUBLE,
                    (3+2)*sizeof(GLdouble),
                    leafCluster5+3);
    
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 7);
    
    GLdouble leafCluster6[(3+2)*5] = {
        0.0, 1.0, 0.0,
        0.35, 0.63,
        0.0, 0.5, 0.5,
        0.3, 0.56,
        0.0, 1.0, 0.0,
        0.2, 0.53,
        0.0, 0.5, 0.5,
        0.1, 0.53,
        0.0, 1.0, 0.0,
        0.05, 0.6};
    
    glColorPointer(
                    3,
                    GL_DOUBLE,
                    (3+2)*sizeof(GLdouble),
                    leafCluster6);
    
    glVertexPointer(
                    2,
                    GL_DOUBLE,
                    (3+2)*sizeof(GLdouble),
                    leafCluster6+3);
    
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 5);
    
    GLdouble leafCluster7[(3+2)*6] = {
        0.0, 1.0, 0.0,
        0.3, 0.5,
        0.0, 0.5, 0.5,
        0.35, 0.43,
        0.0, 1.0, 0.0,
        0.25, 0.4,
        0.0, 0.5, 0.5,
        0.15, 0.33,
        0.0, 1.0, 0.0,
        0.1, 0.43,
        0.0, 0.5, 0.5,
        0.15, 0.5};
    
    glColorPointer(
                    3,
                    GL_DOUBLE,
                    (3+2)*sizeof(GLdouble),
                    leafCluster7);
    
    glVertexPointer(
                    2,
                    GL_DOUBLE,
                    (3+2)*sizeof(GLdouble),
                    leafCluster7+3);
    
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
    }
    /*============================
                FALL
     =============================*/
    else if(Season == FALL)
    {
    //the ground in fall
    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2d(0.0, 0.0);
    glColor3d(1.0, 1.0, 0.0);
    glVertex2d(0.3, 0.06);
    glColor3d(0.9, 0.9, 0.5);
    glVertex2d(0.3, 0.0);
    glColor3d(1.0, 0.5, 0.0);
    glVertex2d(0.4, 0.1);
    glColor3d(1.0, 1.0, 0.0);
    glVertex2d(0.4, 0.0);
    glColor3d(0.9, 0.9, 0.5);
    glVertex2d(0.6, 0.1);
    glColor3d(1.0, 0.5, 0.0);
    glVertex2d(0.6, 0.0);
    glColor3d(1.0, 1.0, 0.0);
    glVertex2d(0.75, 0.06);
    glColor3d(0.9, 0.9, 0.5);
    glVertex2d(0.75, 0.0);
    glColor3d(1.0, 0.0, 0.0);
    glVertex2d(0.85, .03);
    glColor3d(1.0, 1.0, 0.0);
    glVertex2d(1.0, 0.0);
    glEnd();

    //some fall leaves using vertex arrays
    //color & positions of the first leaf
    GLdouble leafData1[(3+2)*8] = {
        1.0, 0.5, 0.0, //rgb for vert 0
        0.9, 0.36, //x, y for vert 0
        0.9, 0.9, 0.5, //rgb for vert 1
        0.8, 0.33, //x, y vert 1
        1.0, 0.5, 0.0,
        0.8, 0.3, //x, y vert 2
        0.9, 0.9, 0.5,
        0.85, 0.3, //x, y vert 3
        1.0, 0.5, 0.0,
        0.9, 0.26, //x, y vert 4
        0.9, 0.9, 0.5,
        0.95, 0.3, //x, y vert 5
        1.0, 0.5, 0.0,
        1.0, 0.3,//x, y vert 6
        0.9, 0.9, 0.5,
        1.0, 0.33//x, y vert 7
    };
    
    glColorPointer(
                    3,
                    GL_DOUBLE,
                    (3+2)*sizeof(GLdouble),
                    leafData1);
    
    glVertexPointer(
                    2,
                    GL_DOUBLE,
                    (3+2)*sizeof(GLdouble),
                    leafData1+3);

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 8);
    
    //color & positions of the second leaf
    GLdouble leafData2[(3+2)*8] = {
        1.0, 1.0, 0.0, //rgb for vert 0
        0.9, 0.6, //x, y for vert 0
        1.0, 0.5, 0.0, //rgb for vert 1
        0.85, 0.6, //x, y vert 1
        1.0, 1.0, 0.0,
        0.8, 0.53, //x, y vert 2
        1.0, 0.5, 0.0,
        0.85, 0.53, //x, y vert 3
        1.0, 1.0, 0.0,
        0.9, 0.5, //x, y vert 4
        1.0, 0.5, 0.0,
        0.95, 0.53, //x, y vert 5
        1.0, 1.0, 0.0,
        1.0, 0.53,//x, y vert 6
        1.0, 0.5, 0.0,
        0.95, 0.6//x, y vert 7
    };
      
        glColorPointer(
                       3,
                       GL_DOUBLE,
                       (3+2)*sizeof(GLdouble),
                       leafData2);
        
        glVertexPointer(
                        2,
                        GL_DOUBLE,
                        (3+2)*sizeof(GLdouble),
                        leafData2+3);
        
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_POLYGON, 0, 8);
        
        //color & positions of the third leaf
        GLdouble leafData3[(3+2)*8] = {
            1.0, 0.5, 0.0, //rgb for vert 0
            0.9+x1, 0.36+y1, //x, y for vert 0
            1.0, 0.0, 0.0, //rgb for vert 1
            0.8+x1, 0.33+y1, //x, y vert 1
            1.0, 0.5, 0.0,
            0.8+x1, 0.3+y1, //x, y vert 2
            1.0, 0.0, 0.0,
            0.85+x1, 0.3+y1, //x, y vert 3
            1.0, 0.5, 0.0,
            0.9+x1, 0.26+y1, //x, y vert 4
            1.0, 0.0, 0.0,
            0.95+x1, 0.3+y1, //x, y vert 5
            1.0, 0.5, 0.0,
            1.0+x1, 0.3+y1,//x, y vert 6
            1.0, 0.0, 0.0,
            1.0+x1, 0.33+y1//x, y vert 7
        };
        
        glColorPointer(
                       3,
                       GL_DOUBLE,
                       (3+2)*sizeof(GLdouble),
                       leafData3);
        
        glVertexPointer(
                        2,
                        GL_DOUBLE,
                        (3+2)*sizeof(GLdouble),
                        leafData3+3);
        
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 8);
    }
    /*============================
                WINTER
     =============================*/
    else if (Season == WINTER)
    {
    //the ground in winter
    glColor3d(0.8, 0.8, 0.8);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2d(0.0, 0.0);
    glColor3d(1.0, 1.0, 1.0);
    glVertex2d(0.3, 0.06);
    glVertex2d(0.3, 0.0);
    glVertex2d(0.4, 0.1);
    glColor3d(0.8, 0.8, 0.8);
    glVertex2d(0.4, 0.0);
    glColor3d(1.0, 1.0, 1.0);
    glVertex2d(0.6, 0.1);
    glColor3d(0.8, 0.8, 0.8);
    glVertex2d(0.6, 0.0);
    glColor3d(1.0, 1.0, 1.0);
    glVertex2d(0.75, 0.06);
    glVertex2d(0.75, 0.0);
    glVertex2d(0.85, .03);
    glColor3d(0.8, 0.8, 0.8);
    glVertex2d(1.0, 0.0);
    glEnd();
    
    //lots of snowflakes
    GLdouble snowflakes[2*86] = {
        0.7, 0.4,
        0.8, 0.46,
        0.9, 0.46,
        1.0, 0.4,
        1.0, 0.3,
        0.9, 0.23,
        0.8, 0.26,
        0.65, 0.62,
        0.75, 0.7,
        0.8, 0.66,
        0.9, 0.66,
        0.95, 0.63,
        0.9, 0.56,
        0.95, 0.5,
        0.6, 0.76,
        0.85, 0.86,
        0.95, 0.83,
        0.9, 0.8,
        1.0, 0.73,
        0.95, 0.7,
        0.35, 0.8,
        0.35, 0.73,
        0.25, 0.66,
        0.15, 0.66,
        0.05, 0.73,
        0.1, 0.8,
        0.15, 0.86,
        0.35, 0.63,
        0.3, 0.56,
        0.2, 0.53,
        0.1, 0.53,
        0.05, 0.6,
        0.3, 0.5,
        0.35, 0.43,
        0.25, 0.4,
        0.15, 0.33,
        0.1, 0.43,
        0.15, 0.5,
        0.5, 0.83,
        0.4, 0.86,
        0.35, 0.93,
        0.45, 0.93,
        0.5, 0.96,
        0.55, 0.93,
        0.65, 0.93,
        0.7, 0.86,
        0.65, 0.8,
        0.05, 0.96,
        0.95, 0.96,
        0.85, 0.93,
        0.25, 0.9,
        0.45, 0.73,
        0.6, 0.7,
        0.55, 0.63,
        0.4, 0.56,
        0.7, 0.53,
        0.45, 0.46,
        0.6, 0.46,
        0.3, 0.36,
        0.4, 0.33,
        0.1, 0.3,
        0.2, 0.3,
        0.65, 0.3,
        0.05, 0.26,
        0.25, 0.26,
        0.6, 0.26,
        0.65, 0.26,
        0.15, 0.2,
        0.75, 0.2,
        0.1, 0.16,
        0.3, 0.16,
        0.65, 0.16,
        0.9, 0.16,
        0.85, 0.13,
        0.95, 0.1,
        0.45, 0.16,
        0.2, 0.13,
        0.75, 0.13,
        0.15, 0.06,
        0.45, 0.06,
        0.64, 0.06,
        0.25, 0.03,
        0.55, 0.03,
        0.8, 0.03,
        0.95, 0.03};
        for(int i=0; i<86; ++i)
            {
            snowflakes[i*2+1]-=y2;
                if(snowflakes[i*2+1]<0.0)
                {
                    snowflakes[i*2+1]+=1.0;
                }
            }
        
    glVertexPointer(
                    2,
                    GL_DOUBLE,
                    2*sizeof(GLdouble),
                    snowflakes);
    
    glDisableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3d(1.0, 1.0, 1.0);
    glDrawArrays(GL_POINTS, 0, 86);
    }

    // Draw documentation
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);  // Set up simple ortho projection
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);
    glColor3d(0., 0., 0.);        // Black text
    BitmapPrinter p(-0.9, 0.9, 0.1);
    p.print("Change the Seasons!");
    p.print("s: summer");
    p.print("f: fall");
    p.print("w: winter");
    p.print("Down-Arrow: make snow fall in winter");
    p.print("ESC to Quit");
    glPopMatrix();                // Restore prev projection
    glMatrixMode(GL_MODELVIEW);
    
    // Send it all down the pipeline
    glFlush();
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
        case 's':     // s: make it summer
            Season = SUMMER;
            glutPostRedisplay();
            break;
        case 'f':     // f: make it fall
            Season = FALL;
            glutPostRedisplay();
            break;
        case 'w':     // w: make it winter
            Season = WINTER;
            y2 = 0;
            glutPostRedisplay();
            break;
    }
}

// mySpecial
// The GLUT special function
void mySpecial(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_DOWN:  // -> make snow fall
            y2 += 0.01;
            if(y2>=1.0)
            {
                y2=0.0;
            }
            glutPostRedisplay();
            break;
    }
}

// init
// Initialize GL states & global data
// Called by main after window creation
void init()
{
    // OpenGL Stuff
    glLineWidth(2.0);
    glPointSize(5.0f);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
    
    glMatrixMode(GL_MODELVIEW);  // Always go back to model/view mode

}


int main(int argc, char ** argv)
{
    // Initialize OpenGL/GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    // Make a window
    glutInitWindowSize((startwinsize/1.5), startwinsize);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("CS 381 - Assignment 1 - Ann Tupek");
    
    // Initialize GL states & register GLUT callbacks
    init();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myIdle);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecial);
    
    // Do something
    glutMainLoop();
    
    return 0;
}


