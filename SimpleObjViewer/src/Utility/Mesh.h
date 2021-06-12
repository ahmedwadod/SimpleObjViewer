#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "ShadersProgram.h"
#include "Texture2DClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

std::vector<Vertex> set_normals_for_vertices(std::vector<Vertex> vertices, std::vector<GLuint> indices);

class Mesh {
protected:
	VAO _vao;
	VBO _vbo;
	EBO _ebo;
	glm::mat4 _matrix = glm::mat4(1.0f);
	GLsizei _indicesCount;
	ShadersProgram* _shader;
public:
	Mesh();
	//Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, ShadersProgram* shader);
	void Rotate(float degree, glm::vec3 rotationVec);
	void Translate(glm::vec3 translation);
	void Scale(glm::vec3 scale);
	void DrawWithTexture(Texture2D* texturePtr, const char* modelMatUniformName);
	void Draw(const char* modelMatrixUniformName);
	void Delete();
};
