#version 330
layout(location = 0) out vec4 wholeScreenHDR;
layout(location = 1) out vec4 thresholdHDR;

uniform sampler2D baseTexture;
uniform sampler2D depthTexture;

in vec2 texCoords;
uniform float exposure;

float threshold = 0.1f;

void main()
{
    vec3 base = texture(baseTexture, texCoords).rgb;
	float depth = texture(depthTexture, texCoords).r;

	float gamma = 2.2f;

	vec3 mappedColors = vec3(1.0) - exp(-base * exposure);

	mappedColors = pow(mappedColors, vec3(1.0 / gamma));
	

	float brightness = dot(mappedColors, vec3(0.2126, 0.7152, 0.0722)); // Luminance

    if (brightness > threshold && length(depth) != 1.0f)
        thresholdHDR = vec4(mappedColors, 1.0);
    else
        thresholdHDR = vec4(0.0);

	wholeScreenHDR = vec4(mappedColors, 1.0f);
}