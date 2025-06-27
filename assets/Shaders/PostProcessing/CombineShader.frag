#version 330 core

out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    vec3 color1 = texture(texture1,texCoords).rgb;
    vec3 color2 = texture(texture2,texCoords).rgb;

    vec3 combined;
    

    combined = color1 + color2;

    FragColor = vec4(combined,1.0f);
}