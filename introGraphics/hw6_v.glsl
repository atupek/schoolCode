// hw6_v.glsl
// Ann Tupek
// 26 Nov 2014
//
// GLSL Vertex Shader for use with hw6.cpp
// No change from brown_textan_v.glsl
// By Glenn G. Chappell


varying vec3 surfpt;       // Point on surface (camera coords)
varying vec3 surfnorm_un;  // Surface normal (camera coords)
                           // Normalize before & after sending
varying vec2 mytexcoord;   // 2-D texture coordinates
attribute vec3 vtan_in;    // Tangent vector, from application
varying vec3 vtan_var;     // Tangent vector, vshader -> fshader



void main()
{
    // Compute projected vertex position
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    // Surface paint color
    gl_FrontColor = gl_Color;

    // *** Computations below in camera coordinates ***

    // Surface point (camera coords)
    vec4 surfpt4 = gl_ModelViewMatrix * gl_Vertex;
    surfpt = surfpt4.xyz / surfpt4.w;

    // Surface normal (camera coords)
    surfnorm_un = normalize(gl_NormalMatrix * gl_Normal);

    // Transform texture coords & send 2-D version to frag shader
    vec4 mytexcoord4 = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    mytexcoord = mytexcoord4.st / mytexcoord4.q;

    // Transform Tangent vector and ensure it has length 1
    vtan_var = normalize(gl_NormalMatrix * vtan_in);
}

