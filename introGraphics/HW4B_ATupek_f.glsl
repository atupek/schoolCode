// Ann Tupek
// CS381_HW4B_ATupek
// due 21 Oct 2014
// fragment shader for use with useshaders.cpp
//
// changes red component based on ratio of x, y coordinates of surface
// adds a fog effect
//
// based on
// dabble_v.glsl
// by Glenn G. Chappell

varying vec3 surfpt;       // Point on surface (camera coords)


void main()
{
    vec4 mycolor = gl_Color;
    
    //change red component based on x, y ratio
    float redRatio = surfpt.x/surfpt.y;
    mycolor.r=abs(redRatio*gl_Color.r);
    
    vec4 myfoggycolor = mycolor;
    //make it foggy
    float x=surfpt.z/-25.0;
    if(x>=1.0)
        x=1.0;
    myfoggycolor.r=(1.0-x)*(mycolor.r)+x*(0.7);
    myfoggycolor.g=(1.0-x)*(mycolor.g)+x*(0.7);
    myfoggycolor.b=(1.0-x)*(mycolor.b)+x*(0.7);
    
    gl_FragColor = myfoggycolor;
}