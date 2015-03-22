// Ann Tupek
// CS381 HW5
// Due 4 Nov 2014
// HW5ATupek_v.glsl
// vertex shader for use with HW5ATupek.cpp
//
// unchanged from
// bpfrag_v.glsl
// by Glenn G. Chappell

varying vec3 surfpt;       // Point on surface (camera coords)
varying vec3 surfnorm_un;  // Surface normal (camera coords)
//  Normalize before & after sending


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
}

