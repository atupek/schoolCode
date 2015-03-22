// Ann Tupek
// CS381 HW5
// Due 4 Nov 2014
// HW5ATupek_f.glsl
// fragment shader for use with HW5ATupek.cpp
//
// based on
// bpfrag_f.glsl
// by Glenn G. Chappell

varying vec3 surfpt;       // Point on surface (camera coords)
varying vec3 surfnorm_un;  // Surface normal (camera coords)
uniform float myf1;        // Application float (in [0.,1.]; start: 1.)
uniform float myb2;


// bpLight
// Blinn-Phong illumination model
// Given light-source color & position/direction, surface paint color,
// position, & normal vec (normalized). Return apparent surface color.
vec4 bpLight(
             vec4 lightcolor,
             vec4 lightpos4,  // Homogeneous form
             vec4 paintcolor,
             vec3 surfpt,
             vec3 surfnorm)   // Normalized
{
    // Normalized direction of light source from object (cam coords)
    vec3 lightdir = normalize(lightpos4.xyz - surfpt*lightpos4.w);
    if (lightpos4.w < 0.) lightdir = -lightdir;
    // Odd computation above is correct for both positional and
    //  directional lights.
    
    // Scalar lighting parameters
    float ambientfrac = 0.2;
    // Ambient light color, as fraction of light color
    float shininess = 5. + myf1 * 70.;
    // PHONG model shininess exponent (Blinn-Phong needs 4x larger)
    
    // *** Compute the three parts of the Blinn-Phong model ***
    
    // Ambient
    vec4 ambientcolor = ambientfrac * lightcolor * paintcolor;
    
    // Ddiffuse
    // Lambert cosine (or 0 if this is negative)
    float lambertcos = max(0., dot(surfnorm, lightdir));
    vec4 diffusecolor = lambertcos * lightcolor * paintcolor;
    
    // Specular
    vec3 viewdir = normalize(-surfpt);
    vec3 halfway = normalize(viewdir + lightdir);
    float specularcoeff = pow(max(0., dot(surfnorm, halfway)),
                              4.*shininess);
    // Blinn-Phong needs shininiess 4 * [Phong shininess]
    vec4 specularcolor = specularcoeff * lightcolor;
    
    // *** Put the three parts together ***
    
    return clamp(ambientcolor + diffusecolor + specularcolor,
                 0., 1.);
}


void main()
{
    // Surface paint color
    vec4 paintcolor = gl_Color;
    
    // *** Computations below in camera coordinates ***
    
    // Surface normal
    vec3 surfnorm = normalize(surfnorm_un);
    
    // Light-source 1 color & position (camera coords)
    vec4 light1color = vec4(1., 1., 1., 1.);
    if(myb2==1.0)
    {
        light1color.r=1.0;
        light1color.g=0.0;
        light1color.b=0.0;
    }
    else if(myb2 ==2.0)
    {
        light1color.r=1.0;
        light1color.g=1.0;
        light1color.b=0.0;
    }
    else if(myb2 == 3.0)
    {
        light1color.r=0.0;
        light1color.g=0.0;
        light1color.b=1.0;
    }
    else
    {
        light1color.r=1.0;
        light1color.g=1.0;
        light1color.b=1.0;
    }
    
    vec4 light1pos4 = gl_LightSource[0].position;
    
    if(surfpt.x>0.5)
    {
        paintcolor.r=0.0;
        paintcolor.g=1.0;
        paintcolor.b=1.0;
    }
    
    if(surfpt.x<-0.5)
    {
        paintcolor.r=1.0;
        paintcolor.g=0.0;
        paintcolor.b=1.0;
    }
    
    // Apply Blinn-Phong illumination model for light source 1
    vec4 light1bpcolor =
    bpLight(light1color,
            light1pos4,
            paintcolor,
            surfpt,
            surfnorm);
    
    // Add colors from all light sources and clamp to [0., 1.]
    float light1amt = 1.0;
    gl_FragColor =
    clamp(light1amt*light1bpcolor,
          0., 1.);
}