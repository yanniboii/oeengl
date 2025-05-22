#version 330
out vec4 FragColor;

uniform sampler2D baseTexture;

in vec2 texCoords;
uniform float exposure;

void main()
{
    vec3 base = texture(baseTexture, texCoords).rgb;

	float gamma = 2.2f;

	vec3 mappedColors = vec3(1.0) - exp(-base * exposure);

	mappedColors = pow(mappedColors, vec3(1.0 / gamma));
	
	FragColor	= vec4(mappedColors,1.0);
}