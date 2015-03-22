// hw6_f.glsl
// Ann Tupek
// 26 Nov 2014
//
// GLSL Fragment Shader for use with hw6.cpp
// based on brown_textan_f.glsl
// By Glenn G. Chappell


varying vec3 surfpt;       // Point on surface (camera coords)
varying vec3 surfnorm_un;  // Surface normal (camera coords)
                           //  Normalize before & after sending
varying vec2 mytexcoord;   // 2-D texture coordinates
uniform sampler2D mytex0;  // A 2-D texture
varying vec3 vtan_var;     // Tangent vector, vshader -> fshader

uniform int myi1;         // int for texture mode


// perturb
// Given normal, tangent, binormal, texture coordinates, 2-D sampler,
// and float coefficient, returns perturbed normal appropriate for bump
// mapping. Uses red component of sampler as a height map.
vec3 perturb(vec3 normal, vec3 tangent, vec3 binormal,
             vec2 texcoord, sampler2D sampler, float effect)
{
    const float delta = 0.003;    // Delta for derivative estimate

    // Compute x & y nudges to make to normal vector, in surface coords
    vec2 tcx1 = texcoord-vec2(delta, 0.);
    vec2 tcx2 = texcoord+vec2(delta, 0.);
    vec2 tcy1 = texcoord-vec2(0., delta);
    vec2 tcy2 = texcoord+vec2(0., delta);

    float xslope =
        (texture2D(sampler, tcx1)-texture2D(sampler,tcx2)).r/(2.*delta);
    float yslope =
        (texture2D(sampler, tcy1)-texture2D(sampler,tcy2)).r/(2.*delta);
    return normalize(normal
                   + effect*xslope*tangent
                   + effect*yslope*binormal);
}

// sunColor
vec4 sunColor(float f, bool front)
{
    vec4 c1 = vec4(1.0, (front ? 1.0 : 0.5), 0.0, 1.0);
    vec4 c2 = vec4(1.0, .7, 0.0, 1.0);

    vec4 color = mix(c1, c2, 1.0);
    return color;
}

//planetColor
vec4 planetColor(float f, bool front)
{
    vec4 c1 = vec4(1.0, (front ? 1.0 : 0.5), 0.0, 1.0);
    vec4 c2 = vec4(0.0, 1.0, 0.0, 1.0);
    
    vec4 color = mix(c1, c2, 1.0);
    return color;
}

//moonColor
vec4 moonColor(float f, bool front)
{
    vec4 c1 = vec4(1.0, (front ? 1.0 : 0.5), 1.0, 1.0);
    vec4 c2 = vec4(0.7, 0.7, 0.7, 1.0);
    
    vec4 color = mix(c1, c2, 1.0);
    return color;
}


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
    float shininess = 75.;
        // PHONG model shininess exponent (Blinn-Phong needs 4x larger)

    // *** Compute the three parts of the Blinn-Phong model ***

    // Ambient
    vec4 ambientcolor = ambientfrac * lightcolor * paintcolor;

    // Diffuse
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
    // Stretch out one texture coordinate
    vec2 stretchtexcoord = mytexcoord;
    stretchtexcoord.t *= 3.;

    // Paint color from texture, gl_FrontFacing
    vec4 texcolor = texture2D(mytex0, stretchtexcoord);
    vec4 paintcolor = gl_Color;
    //Selectively apply textures
    if(myi1 == 1)
    {
      paintcolor = sunColor(texcolor.r, gl_FrontFacing);
    }
    else if(myi1 == 2)
    {
      paintcolor = planetColor(texcolor.r, gl_FrontFacing);
    }
    else if(myi1 == 3)
    {
      paintcolor = moonColor(texcolor.r, gl_FrontFacing);
    }

    // *** Computations below in camera coordinates ***

    // Compute normalized normal, tangent, binormal, perturb the normal
    vec3 surfnorm = normalize(surfnorm_un);
    vec3 vtan = normalize(vtan_var - dot(vtan_var, surfnorm)*surfnorm);
    vec3 binorm = normalize(cross(surfnorm, vtan));
    vec3 surfnorm_pert = perturb(surfnorm, vtan, binorm,
                                 stretchtexcoord, mytex0, 0.04);
    if (!gl_FrontFacing)
        surfnorm_pert = -surfnorm_pert;

    // Light-source 0 color & position (camera coords)
    vec4 light0color = vec4(1., 1., 1., 1.);
    vec4 light0pos4 = gl_LightSource[0].position;

    // Apply Blinn-Phong illumination model for light source 0
    vec4 light0bpcolor =
        bpLight(
            light0color,
            light0pos4,
            paintcolor,
            surfpt,
            surfnorm_pert);

    // Light-source 1 color & position (camera coords)
    vec4 light1color = vec4(0., 0., 1., 1.);
    vec4 light1pos4 = gl_LightSource[1].position;

    // Apply Blinn-Phong illumination model for light source 1
    vec4 light1bpcolor =
        bpLight(
            light1color,
            light1pos4,
            paintcolor,
            surfpt,
            surfnorm_pert);

    // Add colors from all light sources and clamp to [0., 1.]
    gl_FragColor =
        clamp(light0bpcolor + light1bpcolor,
              0., 1.);
}

