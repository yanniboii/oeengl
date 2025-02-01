#version 330 core
const float offset = 1.0 / 600.0;  

out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D colorTex;
uniform sampler2D depthTex;
    float kernel[9] = float[](
        1, 2, 1,
        2, 4, 2,
        1, 2, 1
    );    
    float kernelEdge[9] = float[](
        -1, -1, -1,
        -1, 20, -1,
        -1, -1, -1
    );
    float kernelDarkEdge[9] = float[](
        50, 50, 50,
        50, -500, 50,
        50, 50, 50
    );
    float kernelBox[9] = float[](
        1, 1, 1,
        1, 1, 1,
        1, 1, 1
    );

void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );

    float depth = texture(depthTex, texCoords).r;

    vec3 sampleTexColors[9];

    for(int i = 0; i < 9; i++){
        sampleTexColors[i] = vec3(texture(colorTex,texCoords.st + offsets[i]));
    };

    vec4 col;

    for(int i = 0; i < 9; i++){
        col += vec4(vec3(sampleTexColors[i]*kernelEdge[i]),1.0f);
    };
    if (depth >= 1.0) {
        FragColor = vec4(sampleTexColors[4].xyz, 1.0); // No effect on background
    } else {
        FragColor = vec4(col.xyz, 1.0); // Darken based on depth
    }
    //FragColor = col;
    //FragColor = vec4(1.0f - vec3(texture(tex,texCoords)),1.0f);
}

// INVERSE
