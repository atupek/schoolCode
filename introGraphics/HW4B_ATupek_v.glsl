// Ann Tupek
// CS381_HW4B_ATupek
// due 21 Oct 2014
// vertex shader for use with useshaders.cpp
//
// this is unchanged from
// dabble_v.glsl
// by Glenn G. Chappell


varying vec3 surfpt;       // Point on surface (camera coords)


void main()
{
    // Compute projected vertex position as usual
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    
    // Compute current position in camera coords
    vec4 surfpt4 = gl_ModelViewMatrix * gl_Vertex;
    surfpt = surfpt4.xyz / surfpt4.w;
    
    // Send color through unchanged
    gl_FrontColor = gl_Color;
}
