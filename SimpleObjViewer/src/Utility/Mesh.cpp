#include "Mesh.h"

Mesh::Mesh() {}

#define HIGH_POINT_Y 0
#define LOW_POINT_Y 1
#define HIGH_POINT_X 2
#define LOW_POINT_X 3

/// 0: high point Y, 1: low point Y, 2: high point X, 3: low point X
float* getHighestAndLowestPoints(std::vector<Vertex> vertices) {
	float points[4] = { 0 };
	for (int i = 0; i < vertices.size(); i++)
	{
		Vertex v = vertices[i];
		if (v.position.y > points[HIGH_POINT_Y])
			points[HIGH_POINT_Y] = v.position.y;
		if (v.position.y < points[LOW_POINT_Y])
			points[LOW_POINT_Y] = v.position.y;
		if (v.position.x > points[HIGH_POINT_X])
			points[HIGH_POINT_X] = v.position.x;
		if (v.position.x < points[LOW_POINT_X])
			points[LOW_POINT_X] = v.position.x;
	}

	return points;
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, ShadersProgram* shader)
{
	_shader = shader;
	_vao = VAO::CreateVAO();
	_vbo = VBO(vertices);
	_ebo = EBO(indices);
	_indicesCount = indices.size();

	auto points = getHighestAndLowestPoints(vertices);
	_biggestPointY = points[HIGH_POINT_Y];
	_lowestPointY = points[LOW_POINT_Y];
	_biggestPointX = points[HIGH_POINT_X];
	_lowestPointX = points[LOW_POINT_X];

	_vao.Bind();

	_vao.LinkAttribute(_vbo, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	_vao.LinkAttribute(_vbo, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	_vao.LinkAttribute(_vbo, 2, 3, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	_vao.LinkAttribute(_vbo, 3, 2, GL_FLOAT, 11 * sizeof(float), (void*)(9 * sizeof(float)));

	_vao.Unbind();
	_vbo.Unbind();
	_ebo.Unbind();
};

void Mesh::Rotate(float degree, glm::vec3 rotationVec)
{
	_matrix = glm::rotate(_matrix, glm::radians(degree), rotationVec);
}
void Mesh::Translate(glm::vec3 translation)
{
	_matrix = glm::translate(_matrix, translation);
}
void Mesh::Scale(glm::vec3 scale)
{
	_matrix = glm::scale(_matrix, scale);
}

void Mesh::DrawWithTexture(Texture2D* texture, const char* uniformName)
{
	_shader->Activate();

	auto modelUni = _shader->GetUniform(uniformName);
	glUniformMatrix4fv(modelUni, 1, GL_FALSE, glm::value_ptr(_matrix));

	texture->ActivateAndBind();
	_vao.Bind();

	glDrawElements(GL_TRIANGLES, _indicesCount, GL_UNSIGNED_INT, 0);

	texture->DisactivateAndUnbind();
	_vao.Unbind();
}

void Mesh::Draw(const char* uniformName)
{
	_shader->Activate();

	auto modelUni = _shader->GetUniform(uniformName);
	glUniformMatrix4fv(modelUni, 1, GL_FALSE, glm::value_ptr(_matrix));

	_vao.Bind();

	glDrawElements(GL_TRIANGLES, _indicesCount, GL_UNSIGNED_INT, 0);

	_vao.Unbind();
}

void Mesh::Delete()
{
	_vao.Delete();
	_vbo.Delete();
	_ebo.Delete();
}

std::vector<Vertex> set_normals_for_vertices(std::vector<Vertex> vers, std::vector<GLuint> indices)
{
	for (int i = 0; i < indices.size(); i+=3)
	{
		glm::vec3 triangle[] = {
			vers[indices[i]].position, vers[indices[i + 1]].position, vers[indices[i + 2]].position
		};

		glm::vec3 normal;

		// Pseudo-code
		glm::vec3 U(triangle[1] - triangle[0]);
		glm::vec3 V(triangle[2] - triangle[0]);

		normal.x = (U.y * V.z) - (U.z * V.y);
		normal.y = (U.z * V.x) - (U.x * V.z);
		normal.z = (U.x * V.y) - (U.y * V.x);
		//

		vers[indices[i]].normal = normal;
		vers[indices[i + 1]].normal = normal;
		vers[indices[i + 2]].normal = normal;
	}

	return vers;
}

glm::vec3 Mesh::GetOptimalCameraPosition(float extraZ)
{
	float centerY, centerX, z;
	centerY = (_biggestPointY + _lowestPointY) / 2;
	centerX = (_biggestPointX + _lowestPointX) / 2;

	float mHeight = fabs(_lowestPointY) + _biggestPointY;
	float mWidth= fabs(_lowestPointX) + _biggestPointX;

	if (mHeight > mWidth) z = mHeight;
	else z = mWidth;
	z *= 1.45f;
	z += extraZ;

	return glm::vec3(centerX, centerY, z);
}
