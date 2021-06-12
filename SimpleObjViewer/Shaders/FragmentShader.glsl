#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 color;
in vec3 Normal;
in vec3 currentPos;

uniform sampler2D tex0;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - currentPos);

	float diffuseLighting = max(dot(normal, lightDirection), 0.0f);
	float ambientLighting = 0.5f;

	FragColor = vec4(color, 1.0) * vec4(lightColor, 1.0) * (diffuseLighting + ambientLighting);
}