#version 330 core
const float offset = 1.0 / 100.0;  

out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D tex;


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
    float kernel[9] = float[](
        1, 2, 1,
        2, 4, 2,
        1, 2, 1
    );

    vec3 sampleTexColors[9];

    for(int i = 0; i < 9; i++){
        sampleTexColors[i] = vec3(texture(tex,texCoords.st + offsets[i]));
    };

    vec4 col;

    for(int i = 0; i < 9; i++){
        col += vec4(vec3(sampleTexColors[i]*kernel[i]),1.0f);
    };

    FragColor = col;
}

// INVERSE
    //FragColor = vec4(1.0f - vec3(texture(tex,texCoords)),1.0f);
