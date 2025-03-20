#version 330 core
const float offset = 1.0 / (1080.0 / 1.0);  

out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D colorTex;
uniform sampler2D depthTex;
    float kernel[3] = float[](
        2,
        4,
        2
    );    
    float kernelEdge[3] = float[](
        -5,
        42,
        -5
    );
    float kernelDarkEdge[3] = float[](
        50,
        -500,
        50
    );
    float kernelBox[3] = float[](
        1,
        1,
        1
    );

void main()
{
    vec2 offsets[3] = vec2[](
        vec2( 0.0f,    offset), // top-center
        vec2( 0.0f,    0.0f),   // center-center
        vec2( 0.0f,   -offset)  // bottom-center
    );

    float depth = texture(depthTex, texCoords).r;

    vec3 sampleTexColors[3];

    for(int i = 0; i < 3; i++){
        sampleTexColors[i] = vec3(texture(colorTex,texCoords.st + offsets[i]));
    };

    vec4 col = vec4(0.0);

    float kernelSum = 0.0;

    for(int i = 0; i < 3; i++){
        kernelSum +=                            kernelBox[i];
        col += vec4(vec3(sampleTexColors[i]*    kernelBox[i]),1.0f);
    };
    if (depth >= 1.0) {
        FragColor = vec4(sampleTexColors[2].xyz, 1.0); // No effect on background
    } else {
        FragColor = vec4(col.xyz, 1.0); // Darken based on depth
    }
    FragColor = col / kernelSum;
     //   FragColor = texture(colorTex, texCoords);
    //FragColor = vec4(0.0f + vec3(texture(colorTex,texCoords)),1.0f);
}

// INVERSE
