#ifndef VBO_H
#define VBO_H

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <glm\glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec2 texLoc;
};

/// Vertices Buffer Object
class VBO {
public:
	GLuint ID;
	VBO();
	VBO(GLfloat *vertices, GLsizeiptr size);
	VBO(std::vector<Vertex>& vertices);
	void Bind();
	void Unbind();
	void Delete();
};

#endif