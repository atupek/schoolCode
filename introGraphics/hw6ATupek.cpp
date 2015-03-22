// hw6.cpp
// Ann Tupek
// 26 Nov 2014
//
// Uses textures on planetary model
// based on proctex.cpp
// uses drawCylinder
// By Glenn G. Chappell

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
#include "lib381/globj.h"
                         // For class Tex2D
#include "lib381/tshapes.h"
                         // For shape-drawing functions
#include "lib381/pnoise.h"
                         // For class PNoise (Perlin-ish noise)
#include <iomanip>
using std::setprecision;
using std::fixed;
#include <sstream>
using std::ostringstream;
#include <string>
using std::string;
#include <iostream>
using std::cerr;
using std::endl;
using std::cout;


// Global variables
// Keyboard
const int ESCKEY = 27;         // ASCII value of Escape

// Window/viewport
const int startwinsize = 600;  // Start window width & height (pixels)
int winw = 1, winh = 1;        // Window width, height (pixels)
                               //  (Initialize to avoid spurious errors)

// Objects
double savetime;               // Time of previous movement (sec)
double rotangle;               // Rotation angle for object (deg)
const double rotspeed = 40.;   // Rotation speed (deg/sec)
bool rotateflag;               // True if object rotating
double lightrotang;            // Angle for light source 0 move (deg)
const double lightrotspeed = 50.;
                               // Speed for above (deg/sec)
bool lightrotflag;             // True if light source is moving

// Shaders
string vshader1fname;          // Filename for vertex shader source
string fshader1fname;          // Filename for fragment shader source
GLhandleARB prog1;             // GLSL Program Object

bool shaderbool1;              // Boolean to send to shaders

GLint tanloc = -1;

// Textures
Tex2D tex0;
const int IMG_WIDTH = 256, IMG_HEIGHT = IMG_WIDTH;
GLubyte teximage[IMG_HEIGHT][IMG_WIDTH][3];  // Texture temp storage
   // The image
   // 3rd subscript 0 = R, 1 = G, 2 = B

double angSun = 0.0;
double angPlanet = 0.0;
double angMoon = 0.0;
int subdivs = 50;


// SetFragMode
// Sets the "myi1" variable passed to the fragment shader
void setFragMode(GLint myi1) {
  GLhandleARB theprog = prog1;
  GLint loc;  // Location for shader vars
  loc = glGetUniformLocationARB(theprog, "myi1");
  if (loc != -1)
    glUniform1i(loc, myi1);
}

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
    drawSphere(0.5, 20.0, 20.0, tanloc);
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
    drawSphere(0.5, 15.0, 15.0, tanloc);
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
    drawSphere(0.5, 10.0, 10.0, tanloc);
}

//draw moon system
void drawMoonSystem()
{
    glPushMatrix();
    setFragMode(3);
    glTranslated(0.0, 0.45, 0.0);
    glRotated(90.0, 0.0, 1.0, 0.0);
    glScaled(0.2, 0.2, 0.2);
    drawMoon();
    setFragMode(0);
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
    glScaled(2.11, 2.11, 1.0);
    drawTorus();
    glPopMatrix();
    
    glPushMatrix();
    setFragMode(2);
    glTranslated(0.0, 1.25, 0.0);
    glRotated(90.0, 0.0, 1.0, 0.0);
    glScaled(0.5, 0.5, 0.5);
    drawPlanet();
    setFragMode(0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.0, 1.25, 0.0);
    glRotated(90.0, 1.0, 0.0, 0.0);
    glScaled(0.5, 0.5, 1.0);
    drawTorus();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.358, 1.25, 0.0);
    glRotated(90.0, 1.0, 0.0, 0.0);
    glScaled(0.1, 0.025, 0.025);
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
    setFragMode(1);
    glRotated(90.0, 0.0, 1.0, 0.0);
    glColor3d(1.0, 1.0, 0.0);
    drawSun();
    setFragMode(0);
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
    setFragMode(0);
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

    GLhandleARB theprog;  // CURRENTLY-used program object or 0 if none

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    theprog = prog1;


    // Set texture transformation
    glActiveTexture(GL_TEXTURE0);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    // Set up 3-D
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glTranslated(0., 0., -4.);  // Camera transformation

    // Position light source 0 & draw ball there
    // Also give spot direction
    GLfloat origin4[] = { 0.f, 0.f, 0.f, 1.f };
    glPushMatrix();
    glTranslated(0.0, 0.0, 1.0);
    glRotated(lightrotang, 1.,0.,0.);
    glTranslated(-1., 1., 1.);
    glLightfv(GL_LIGHT0, GL_POSITION, origin4);
    GLfloat spotdir[] = { 1.f, -1.f, -1.f };
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotdir);
    glUseProgramObjectARB(0);
    glColor3d(1., 1., 1.);
    glutSolidSphere(0.1, 20, 15);
    glPopMatrix();

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

        loc = glGetUniformLocationARB(theprog, "myi1");
        if (loc != -1)
            glUniform1i(loc, shaderbool1);  // Send bool as GLint

        tanloc = glGetAttribLocationARB(theprog, "vtan_in");
    }

    // Draw the appropriate object
    glRotated(rotangle, 0.0,1.0,0.0);
    glColor3d(0.8, 0.4, 0.6);

    glPushMatrix();
    glRotated(90.0, 0.0, 0.0, 1.0);
    drawSolarModel();
    glPopMatrix();

    // Reset polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glUseProgramObjectARB(0);     // No shaders
    glDisable(GL_DEPTH_TEST);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);  // Set up simple ortho projection
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0., double(winw), 0., double(winh));
    glColor3d(0., 0., 0.);
    BitmapPrinter p(20., winh-20., 20.);
    p.print("S      Rotate Sun");
    p.print("P      Rotate Planet");
    p.print("M      Rotate Moon");
    p.print("R      Rotate Entire Model");
    p.print("L      Rotate Light Source");
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

    // Move light source
    if (lightrotflag)
    {
        lightrotang += lightrotspeed * elapsedtime;
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
    case 's':     // S: rotate sun
    case 'S':
        angSun+=10;
        glutPostRedisplay();
        break;
    case 'm':     // S: rotate moon
    case 'M':
        angMoon+=10;
        glutPostRedisplay();
        break;
    case 'p':     // S: rotate planet
    case 'P':
        angPlanet+=10;
        glutPostRedisplay();
        break;
    case 'r':     // R: toggle object rotation
    case 'R':
        rotateflag = !rotateflag;
        break;
    case 'l':     // L: toggle light-source movement
    case 'L':
        lightrotflag = !lightrotflag;
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
    gluPerspective(60., double(w)/h, 0.5, 100.);

    glMatrixMode(GL_MODELVIEW);  // Always go back to model/view mode
}


// mapColor
// map value in [-1,1] to a color. Used by makeNoiseImage.
// Parameters are value, a double, expected to be in [-1,1],
//  and color, an array of 3 GLubutes.
// Based on value, chooses RGB intensities,
//  and places these in the color array.
void mapColor(double value, GLubyte color[3])
{
    double t = (value + 1.) / 2.;  // Convert to value in [0,1].
    color[0] = GLubyte(t*255);
    color[1] = GLubyte(t*255);
    color[2] = GLubyte(t*255);
}


// makeNoiseImage
// Make Perlin-noise image in teximage.
// Argument which noise selects kind of noise:
//     0: Perlin's noise primitive
//     1: Fake 1/f noise
//     2: Noise with cusps
// Argument freq is x & y frequency of noise, relatve to array
//  dimensions.
void makeNoiseImage(int whichnoise,  // Which kind of noise to make
                    int freq,        // x & y frequency
                    GLubyte img[IMG_HEIGHT][IMG_WIDTH][3])  // Img data
{
    PNoise p(1);  // Make same texture teach time.
                  // For different texture each time, eliminate seed.

    const int freqx = freq;  // "frequency" of noise function
    const int freqy = freq;
    double noisearray[IMG_HEIGHT][IMG_WIDTH]; // Holds noise.
                                              //  Values in [-1., 1.]

    switch (whichnoise)
    {
    case 0:  // 0: noise primitive
        p.pnoise2d(&noisearray[0][0],        // Make noise primitive
                   IMG_HEIGHT, IMG_WIDTH,
                   freqx, freqy);
        break;
    case 1:  // 1: fake 1/f noise
        p.fnoise2d(&noisearray[0][0],        // Make fake 1/f noise ...
                   IMG_HEIGHT, IMG_WIDTH,
                   freqx, freqy);
        p.normalize2d(&noisearray[0][0],     // ... and normalize it.
                      IMG_HEIGHT, IMG_WIDTH);
        break;
    case 2:  // 2: noise with cusps
        p.filterfnoise2d(&noisearray[0][0],  // Make noise w/ cusps ...
                         IMG_HEIGHT, IMG_WIDTH,
                         freqx, freqy);
        p.normalize2d(&noisearray[0][0],     // ... and normalize it.
                      IMG_HEIGHT, IMG_WIDTH);
        break;
    }

    for (int i = 0; i < IMG_WIDTH; ++i)    // Map noise to colors
    {
        for (int j = 0; j < IMG_HEIGHT; ++j)
        {
            mapColor(noisearray[j][i], img[j][i]);
        }
    }
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
    lightrotang = 0.;
    lightrotflag = false;

    shaderbool1 = true;

    // OpenGL Stuff

    // Shaders
    prog1 = makeProgramObjectFromFiles(vshader1fname, fshader1fname);

    // Make Textures

    cout << "Creating textures ...";
    cout.flush();

    // Make texture 0 (noise primitive)
    glActiveTexture(GL_TEXTURE0);
    tex0.bind();
    makeNoiseImage(0, 8, teximage);
    gluBuild2DMipmaps(GL_TEXTURE_2D,
        GL_RGBA,
        IMG_WIDTH, IMG_HEIGHT,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        &teximage[0][0][0]);
    glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T, GL_REPEAT);

    cout << ".";
    cout.flush();

    cout << " DONE" << endl;

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
    glutCreateWindow("CS 381 - Procedural Texture");

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

