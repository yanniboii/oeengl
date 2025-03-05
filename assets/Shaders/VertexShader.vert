#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec3 aNorm;
layout (location = 3) in vec2 aUVs;

uniform float time;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 viewPos;

out float vTime;
out vec3 vCol;
out vec3 vNorm;
out vec3 FragPos;
out vec3 vViewPos;

void main()
{
	vec4 rotatedPos = vec4(aPos,1.0f);
	mat4 mvp = projection * view * model;
	gl_Position = mvp * rotatedPos;
	vTime = time;
	vCol = aCol;
	vNorm = aNorm;
	FragPos = vec3(model * vec4(aPos,1.0f));
	vViewPos = viewPos;
}