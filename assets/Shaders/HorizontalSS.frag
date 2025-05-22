#version 330 core
#define MAX_KERNEL_SIZE 32

const float offset = 1.0 / (1920.0 / 10.0);  

out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D colorTex;
uniform sampler2D baseTex;
uniform sampler2D depthTex;
uniform float kernel[MAX_KERNEL_SIZE];
uniform vec2 kernelOffsets[MAX_KERNEL_SIZE];
uniform int kernelSize;
    float _kernel[3] = float[](
        2, 4, 2
    );    
    float kernelEdge[3] = float[](
        -5, 42, -5
    );
    float kernelDarkEdge[3] = float[](
        50, -500, 50
    );
    float kernelBox[3] = float[](
        1, 1, 1
    );

    uniform bool firstPass;

void main()
{
    vec2 offsets[3] = vec2[](
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f)    // center-right
    );

    float depth = texture(depthTex, texCoords).r;

    vec3 sampleTexColors[MAX_KERNEL_SIZE];

    for(int i = 0; i < kernelSize; i++){
        if(firstPass)
            sampleTexColors[i] = vec3(texture(baseTex,texCoords.st + kernelOffsets[i]));
        else
            sampleTexColors[i] = vec3(texture(colorTex,texCoords.st + kernelOffsets[i]));
    };

    vec4 col = vec4(0.0);
    float kernelNormalize = 0;

    for(int i = 0; i < kernelSize; i++){
        col += vec4(vec3(sampleTexColors[i]*kernel[i]),1.0f);
        kernelNormalize += kernel[i];
    };

    if (depth >= 1.0) {
        FragColor = vec4(sampleTexColors[2].xyz, 1.0); // No effect on background
    } else {
        FragColor = vec4(col.xyz, 1.0); // Darken based on depth
    }



    FragColor = col / kernelNormalize;
//    FragColor = texture(colorTex, texCoords);

    //FragColor = vec4(0.0f + vec3(texture(colorTex,texCoords)),1.0f);
}

// INVERSE
