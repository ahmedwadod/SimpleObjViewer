#include "Camera.h"

Camera::Camera(glm::vec3 position)
{
	Position = position;
}

void Camera::Render(float width, float height, ShadersProgram* shader, const char* uniformName)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);

	proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 1000.0f);

	auto uni = shader->GetUniform(uniformName);
	glUniformMatrix4fv(uni, 1, GL_FALSE, glm::value_ptr(proj * view));
}