#include "VAO.h"

VAO::VAO()
{
}

VAO VAO::CreateVAO()
{
	VAO vao;
	glGenVertexArrays(1, &vao.ID);
	glBindVertexArray(vao.ID);
	return vao;
}

void VAO::LinkAttribute(VBO vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset)
{
	vbo.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vbo.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}