#version 150
// ^ Change this to version 130 if you have compatibility issues

//This is a fragment shader. If you've opened this file first, please open and read lambert.vert.glsl before reading on.
//Unlike the vertex shader, the fragment shader actually does compute the shading of geometry.
//For every pixel in your program's output screen, the fragment shader is run for every bit of geometry that particular pixel overlaps.
//By implicitly interpolating the position data passed into the fragment shader by the vertex shader, the fragment shader
//can compute what color to apply to its pixel based on things like vertex position, light position, and vertex color.

uniform vec4 u_Color;//The color with which to render this instance of geometry.

///added code
uniform float u_Time; //add for fun moving

//uniform vec2 uResolution //add for noise

//These are the interpolated values out of the rasterizer, so you can't know
//their specific values without knowing the vertices that contributed to them
in vec4 fs_Nor;
in vec4 fs_LightVec;
in vec4 fs_Col;

//added code
in vec4 fs_Pos;


out vec4 out_Col;//This is the final output color that you will see on your screen for the pixel that is currently being processed.

void main()
{
    // Material base color (before shading)
    vec4 diffuseColor = u_Color;

    // Calculate the diffuse term for Lambert shading
    float diffuseTerm = dot(normalize(fs_Nor), normalize(fs_LightVec));
    // Avoid negative lighting values
    diffuseTerm = clamp(diffuseTerm, 0, 1);

    float ambientTerm = 0.2;

    float lightIntensity = diffuseTerm + ambientTerm;   //Add a small float value to the color multiplier
                                                        //to simulate ambient lighting. This ensures that faces that are not
                                                        //lit by our point light are not completely black.


    ///added code
    vec4 sin_offset = sin(fs_Pos.y + u_Time * 360 * (3.14f/180.0f)) * vec4(1, 0, 0, 1);
    vec4 cos_offset = cos(fs_Pos.x + u_Time * 360 * (3.14f/180.0f)) * vec4(0, 0, 1, 1);

    // Compute final shaded color
    //out_Col = normalize(abs(fs_Nor)); //Visual debugging
    //out_Col = vec4(diffuseColor.rgb * lightIntensity, diffuseColor.a) + sin_offset + cos_offset; //FUN COLOR TIME!!!
     out_Col = vec4(diffuseColor.rgb * lightIntensity, diffuseColor.a);


}
