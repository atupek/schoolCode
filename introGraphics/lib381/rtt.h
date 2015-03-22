// rtt.h
// Glenn G. Chappell
// 12 Nov 2014
// 
// For CS 381 Fall 2014
// Header for class RTT: render-to-texture
// There is no associated source file
// Requires GLEW
//
// Before including this file, do not include any GLUT or OpenGL headers
// without including glew.h first.

#ifndef FILE_RTT_H_INCLUDED
#define FILE_RTT_H_INCLUDED

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
#include <string>        // For std::string,
#include <iostream>      // For std::cout, std::cin, std::endl
#include <cstdlib>       // For std::exit


// class RTT
// Render-to-texture
// Handles OpenGL framebuffer objects for render-to-texture. Also
// handles associated renderbuffers (for depth buffering), mimmap
// generation, and management of texture names. Works with both
// ordinary 2-D textures and cube maps.
// Does not handle texture channel/unit activation.
//
// When this class is used, classes Tex2D and TexCube from globj.h are
// unnecessary.
//
// Usage Examples:
//
// To render a 2-D texture and send it to shaders over channel 0.
//
//   Globals:
//     RTT rttex0;
//     const int TEX_WIDTH = 256, TEX_HEIGHT = 256;
//
//   In a function:
//     rttex0.init(GL_TEXTURE_2D, TEX_WIDTH, TEX_HEIGHT);
//         // Above can also be passed as constructor parameters.
//
//     // Note: OpenGL must be initialized for the following
//     glActiveTexture(GL_TEXTURE0);
//     rttex0.beginRender();
//     [ DRAW HERE; do glClear, but not glutSwapBuffers ]
//     rttex0.endRender();
//     glTexParameteri(GL_TEXTURE_2D, ...
//
// To create a 2-D texture and render to it later:
//
//   Globals:
//     RTT rttex1;
//     const int TEX_WIDTH = 256, TEX_HEIGHT = 256;
//
//   In a function:
//     rttex1.init(GL_TEXTURE_2D, TEX_WIDTH, TEX_HEIGHT);
//
//     // Note: OpenGL must be initialized for the following
//     glActiveTexture(GL_TEXTURE0);
//     rttex1.bind();
//     glTexParameteri(GL_TEXTURE_2D, ...
//
//   In another function:
//     rttex1.beginRender();
//     [ DRAW HERE; do glClear, but not glutSwapBuffers ]
//     rttex1.endRender();
//    
// To render a cube map:
//
//   Globals:
//     RTT rtcube0;
//     const int TEX_WIDTH = 256, TEX_HEIGHT = 256;
//
//   In a function:
//     rtcube0.init(GL_TEXTURE_CUBE_MAP, TEX_WIDTH, TEX_HEIGHT);
//
//     // Note: OpenGL must be initialized for the following
//     glActiveTexture(GL_TEXTURE0);
//     rtcube0.beginRender(GL_TEXTURE_CUBE_MAP_POSITIVE_X);
//     [ DRAW +X FACE HERE ]
//     rtcube0.endRender(false);  // "false": no mipmap generation yet
//     rtcube0.beginRender(GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
//     [ DRAW -X FACE HERE ]
//     rtcube0.endRender(false);
//     rtcube0.beginRender(GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
//     [ DRAW +Y FACE HERE ]
//     rtcube0.endRender(false);
//     rtcube0.beginRender(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
//     [ DRAW -Y FACE HERE ]
//     rtcube0.endRender(false);
//     rtcube0.beginRender(GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
//     [ DRAW +Z FACE HERE ]
//     rtcube0.endRender(false);
//     rtcube0.beginRender(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
//     [ DRAW -Z FACE HERE ]
//     rtcube0.endRender(true);   // "true": generate mipmaps now
//     glTexParameteri(GL_TEXTURE_2D, ...
//
class RTT {

// ***** RTT: Ctors, dctor, op= *****
public:

    // Default ctor
    // Leave in un-inited state
    // Member function init should be called later.
    // *** OpenGL init NOT required before call.
    RTT()
       :_isinited(false),
        _texnamegend(false),
        _buffersmade(false),
        _renderingnow(false)
    {}

    // Init ctor
    // Do same action as default ctor, then call init w/ arguments.
    // *** OpenGL init NOT required before call.
    RTT(GLenum textarget_in,
        GLsizei imgwidth_in,
        GLsizei imgheight_in)
       :_isinited(false),
        _texnamegend(false),
        _buffersmade(false),
        _renderingnow(false)
    { init(textarget_in, imgwidth_in, imgheight_in); }

    // Dctor
    // Stops any ongoing render, deletes OpenGL objects, if any.
    // *** OpenGL init NOT required before call.
    ~RTT()
    { free(); }

private:

    // Uncopyable class; no copy ctor, op=
    RTT(const RTT &);
    RTT & operator=(const RTT &);

// ***** RTT: Public functions callable before & after OpenGL init *****
public:

    // init
    // Initialize basic info
    // *** OpenGL init NOT required before call.
    void init(GLenum textarget_in,
             GLsizei imgwidth_in,
             GLsizei imgheight_in)
    {
        if (_renderingnow)
        {
            errorExit("init",
                      "Called during texture render");
        }

        if (_isinited)
            free();

        _textarget = textarget_in;
        _imgwidth= imgwidth_in;
        _imgheight = imgheight_in;

        _iscubemap = (textarget_in == GL_TEXTURE_CUBE_MAP);
        _texnamegend = false;
        _buffersmade = false;
        _renderingnow = false;

        _isinited = true;
    }

// ***** RTT: Public functions callable only after OpenGL init *****
public:

    // bind
    // Bind texture name to given target.
    // If necessary, generate names and make framebuffer objects.
    // Does error checking, exiting on any of the following:
    // - FBO extension not available
    // - RTT object not initialized yet
    // - unsuccessful FBO creation
    // *** OpenGL init REQUIRED before call.
    void bind()
    {
        // Are we ready & able to do this?
        if (_renderingnow)
        {
            errorExit("bind",
                      "Called during texture render");
        }
        if (!_isinited)
        {
            errorExit(
                "bind",
                "First call init or pass params to ctor");
        }
        if (glBindFramebufferEXT == 0)
        {
            errorExit(
                "bind",
                "FBO extension not available\n"
                "    (Hardware/software too old? glewInit not called?");
        }

        // Do the bind, generating texture name if necessary
        if (!_texnamegend)
        {
            glGenTextures(1, &texname_);
            _texnamegend = true;
        }
        glBindTexture(_textarget, texname_);

        // Make buffers, if necessary
        if (_buffersmade)
            return;

        if (_iscubemap)
        {
            for (int i = 0; i < 6; ++i)
                createBuffer(i, indexToFaceTarget(i));
        }
        else
        {
            createBuffer(0, _textarget);
        }

        // Check if successful framebuffer creation
        GLenum fbstat = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
        if (fbstat != GL_FRAMEBUFFER_COMPLETE_EXT)
        {
            std::string errstr = fbStatusToString(fbstat);
            errorExit("bind", "Framebuffer error: " + errstr);
        }
        _buffersmade = true;

        // Return to usual framebuffer
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    }

    // unbind
    // Unbind texture target.
    // For compatibility with classes Tex2D, TexCube from globj.h.
    // *** OpenGL init REQUIRED before call.
    void unbind()
    {
        // Are we ready & able to do this?
        if (_renderingnow)
        {
            errorExit("unbind",
                      "Called during texture render");
        }
        if (!_isinited)
        {
            errorExit(
                "unbind",
                "First call init or pass params to ctor");
        }
        glBindTexture(_textarget, 0);
    }

    // beginRender
    // Start texture rendering.
    // Call this function, draw, and then call endRender.
    // Optional parameter is target for cube-map face.
    // *** OpenGL init REQUIRED before call.
    void beginRender(GLenum target = 0)
    {
        if (_renderingnow)
        {
            errorExit("beginRender",
                      "Called twice without intervening endRender");
        }
        bind();

        int index;
        if (_iscubemap)
        {
            index = faceTargetToIndex(target);
            if (index == -1)
                errorExit("beginRender",
                          "Must specify cube-map face target");
        }
        else
        {
            if (target != 0 && target != _textarget)
                errorExit("beginRender",
                          "Incorrect target specified");
            index = 0;
        }

        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fbnames[index]);
        glPushAttrib(GL_VIEWPORT_BIT);
        glViewport(0, 0, _imgwidth, _imgheight);
        _renderingnow = true;
    }

    // endRender
    // End texture rendering.
    // Call beginRender, draw, and then call this function.
    // Generates mipmaps unless false is passed for parameter.
    // *** OpenGL init REQUIRED before call.
    void endRender(bool genMipmaps = true)
    {
        if (!_renderingnow)
            errorExit("endRender",
                      "endRender called without beginRender");

        glPopAttrib();  // Restore viewport
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
                        // Switch rendering back to standard buffers
        _renderingnow = false;

        if (genMipmaps)
            generateMipmaps();
    }

    // generateMipmaps
    // Generate mipmaps for the texture image(s).
    // This function is called automatically if endRender is called
    // with no parameters.
    // *** OpenGL init REQUIRED before call.
    void generateMipmaps()
    {
        if (_renderingnow)
        {
            errorExit("generateMipmaps",
                      "Called during texture render");
        }
        bind();
        glGenerateMipmapEXT(_textarget);
    }

    // free
    // If currently rendering, ends render.
    // Deletes all generated texture, FBO, and RBO names.
    // Provided as a public member function for compatibility with
    // classes Tex2D, TexCube from globj.h.
    // *** OpenGL init NOT required before call.
    void free()
    {
        // End the render if currently rendering.
        // We do not do an error exit here, because this function
        // is called by the RTT destructor. Thus, for example, it
        // might be called because an exception was thrown during
        // a texture render.
        if (_renderingnow)
            endRender(false);

        // Delete texture name
        if (_texnamegend)
            glDeleteTextures(1, &texname_);
        
        // Delete buffer names
        if (_buffersmade)
        {
            int numbuffers = _iscubemap ? 6 : 1;
            glDeleteFramebuffersEXT(numbuffers, _fbnames);
            glDeleteRenderbuffersEXT(numbuffers, _rbnames);
        }
    }

// ***** RTT: Internal-use functions *****
private:

    // errorExit
    // Given member function name and error string. Prints message and
    // exits.
    // *** OpenGL init NOT required before call.
    static void errorExit(const std::string func,
                          const std::string msg)
    {
        std::cout << "RTT::" << func << ": " << msg << std::endl;
        std::cout << "Press ENTER to quit ";
        while (std::cin.get() != '\n') ;
        std::exit(1);
    }

    // indexToFaceTarget
    // Given index (0-5) returns corresponding OpenGL target for
    // cube-map face.
    // *** OpenGL init NOT required before call.
    static GLenum indexToFaceTarget(int index)
    {
        GLenum facetargets[6] = {
            GL_TEXTURE_CUBE_MAP_POSITIVE_X,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
        };
        return facetargets[index];
    }

    // faceTargetToIndex
    // Given OpenGL target, returns index in range 0-5 if argument is
    // valid cube-map face target. Returns (-1) if argument is not valid
    // cube-map face target.
    // *** OpenGL init NOT required before call.
    static int faceTargetToIndex(GLenum faceTarget)
    {
        switch (faceTarget)
        {
        case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
            return 0;
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
            return 1;
        case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
            return 2;
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
            return 3;
        case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
            return 4;
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
            return 5;
        default:
            return -1;
        }
    }

    // fbStatusToString
    // Given GLenum representing framebuffer status, returns string form
    // of status, or string indicating unknown error if not a valid
    // status.
    // *** OpenGL init NOT required before call.
    static std::string fbStatusToString(GLenum fbstat)
    {
        std::string statstr;
        switch(fbstat)
        {
        case GL_FRAMEBUFFER_COMPLETE_EXT:
            statstr = "GL_FRAMEBUFFER_COMPLETE_EXT";
            break;
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
            statstr = "GL_FRAMEBUFFER_UNSUPPORTED";
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
            statstr = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
            statstr = "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
            statstr = "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
            statstr = "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
            break;
        case GL_FRAMEBUFFER_BINDING_EXT:
            statstr = "GL_FRAMEBUFFER_BINDING";
            break;
        default:
            statstr = "Unknown framebuffer error";
            break;
        }
        return statstr;
    }

    // createBuffer
    // Create framebuffer object as color buffer, attaches renderbuffer
    // object as depth buffer, and allocates memory for all mipmaps.
    // Members _imgwidth, _imgheight used as buffer dimensions.
    // Generates FBO and RBO names and stores these in _fbnames[index],
    // _rbnames[index], respectively.
    // Assumes texture name already generated and bound to teximgtarget.
    // Ends with GL_FRAMEBUFFER_EXT bound to framebuffer target. Does
    // no error checking.
    // *** OpenGL init REQUIRED before call.
    void createBuffer(int index,
                      GLenum teximgtarget)
    {
        // Make Framebuffer Object (FBO)
        glGenFramebuffersEXT(1, &_fbnames[index]);
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fbnames[index]);

        // Add renderbuffer to FBO, as depth buffer
        glGenRenderbuffersEXT(1, &_rbnames[index]);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, _rbnames[index]);

        glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT,
            GL_DEPTH_COMPONENT,
            _imgwidth, _imgheight);

        glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,
            GL_DEPTH_ATTACHMENT_EXT,
            GL_RENDERBUFFER_EXT, _rbnames[index]);
            // Why oh why do I have to pass both the renderbuffer target
            // and the renderbuffer name here? I bound the name to the
            // target, so just the target should be enough. Right?
            // RIGHT?!?!  -GGC-

        // Make space for all mipmpaps with a dummy call to
        //  gluBuild2DMipmaps
        GLuint * dummyimage = new GLuint[_imgwidth * _imgheight * 4];
        gluBuild2DMipmaps(teximgtarget,
            GL_RGBA,
            _imgwidth, _imgheight,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            dummyimage);
        delete [] dummyimage;

        // Attach texture to FBO, as color buffer
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
            GL_COLOR_ATTACHMENT0_EXT,
            teximgtarget, texname_,
            0);  // Mipmap level
    }

// ***** RTT: Data members *****
private:

    bool _isinited;      // True if basic info passed & stored
    bool _texnamegend;   // True if texture name has been generated
    bool _buffersmade;   // True if framebuffer(s) & associated
                         //  renderbuffer(s) named & allocated
    bool _renderingnow;  // True if we are between beginRender,
                         //  endRender calls
    // The following logical implications always hold.
    //   _renderingnow -> _buffersmade -> _texnamegend -> _isinited
    //   _texnamegend -> [OpenGL has been initialized]

    // The following are only valid if _isinited is true.
    bool _iscubemap;     // True if our texture is a cube map
    GLenum _textarget;   // Target for the texture as a whole
    GLsizei _imgwidth;   // Width of texture image (pixels)
    GLsizei _imgheight;  // Height of texture image (pixels)

    // The following is only valid if _texnamegend is true.
    GLuint texname_;     // Generated texture name

    // The following are only valid if _buffersmade is true. In
    //  addition, if _iscubemap is true, then all 6 entries are valid;
    //  otherwise, only the first entry of each array (_fbnames[0],
    //  _rbnames[0]) is valid.
    GLuint _fbnames[6];  // Generated framebuffer names
    GLuint _rbnames[6];  // Generated renderbuffer names

};  // End class RTT


#endif //#ifndef FILE_RTT_H_INCLUDED

