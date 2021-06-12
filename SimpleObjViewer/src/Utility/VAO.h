#ifndef VAO_H
#define VAO_H

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "VBO.h"

class VAO {
public:
	GLuint ID;

	VAO();
	static VAO CreateVAO();
	void LinkAttribute(VBO vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};
#endif