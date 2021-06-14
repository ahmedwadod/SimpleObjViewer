#include "Camera.h"

Camera::Camera(glm::vec3 position)
{
	Position = position;
}

void Camera::Render(float width, float height, ShadersProgram* shader, const char* uniformName)
{
	// Camera view matrix
	glm::mat4 view = glm::mat4(1.0f);
	// Projection matrix
	glm::mat4 proj = glm::mat4(1.0f);

	// Use lookAt to create the matrix from the camera position
	view = glm::lookAt(Position, Position + Orientation, Up);

	// Create the projectionwith 45 degrees and set to the aspect ratio of the view
	proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 1000.0f);

	// Get the uniform of the camera matrix in the shader
	auto uni = shader->GetUniform(uniformName);
	// Set the uniform to the view * projection matrix
	glUniformMatrix4fv(uni, 1, GL_FALSE, glm::value_ptr(proj * view));
}