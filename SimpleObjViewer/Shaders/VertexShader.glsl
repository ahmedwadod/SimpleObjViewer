#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTex;

out vec2 texCoord;
out vec3 color;
out vec3 Normal;
out vec3 currentPos;

uniform mat4 modelMat;
uniform mat4 cameraMat;

void main()
{
	currentPos = vec3(modelMat * vec4(aPos, 1.0f));
	Normal = aNormal;
	gl_Position = cameraMat * vec4(currentPos, 1.0);
	texCoord = aTex;
	color = aColor;
}