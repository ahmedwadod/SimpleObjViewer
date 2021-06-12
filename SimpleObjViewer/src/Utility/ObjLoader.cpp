#define _CRT_SECURE_NO_WARNINGS

#include "ObjLoader.h"

// Simple OBJ loader.

bool LoadObj(
	const char * path,
	std::vector<Vertex> & out_vector_vertex,
	std::string & out_texture_file
	) {

	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;
	std::vector<Vertex> tmp_vertex;


	FILE * file;
	fopen_s(&file, path, "r");
	if (file == NULL) {
		printf("ERROR [ObjLoader]: Couldn't open file: %s\n", path);
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "usemtl") == 0) {
			char t_f_name[1024];
			fscanf(file, "%s\n", t_f_name);
			out_texture_file = std::string(t_f_name);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			//std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			char f_line[1024];
			fgets(f_line, 1024, file);

			int matches = sscanf(f_line, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches == 9) {
				Vertex vx1, vx2, vx3;
				vx1.position = temp_vertices[vertexIndex[0] - 1];
				vx2.position = temp_vertices[vertexIndex[1] - 1];
				vx3.position = temp_vertices[vertexIndex[2] - 1];

				vx1.normal = temp_normals[normalIndex[0] - 1];
				vx2.normal = temp_normals[normalIndex[1] - 1];
				vx3.normal = temp_normals[normalIndex[2] - 1];

				vx1.texLoc = temp_uvs[uvIndex[0] - 1];
				vx2.texLoc = temp_uvs[uvIndex[1] - 1];
				vx3.texLoc = temp_uvs[uvIndex[2] - 1];

				tmp_vertex.push_back(vx1);
				tmp_vertex.push_back(vx2);
				tmp_vertex.push_back(vx3);
			}
			else
			{
				matches = sscanf(f_line, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
				if (matches == 6) {
					Vertex vx1, vx2, vx3;
					vx1.position = temp_vertices[vertexIndex[0] - 1];
					vx2.position = temp_vertices[vertexIndex[1] - 1];
					vx3.position = temp_vertices[vertexIndex[2] - 1];

					vx1.normal = temp_normals[normalIndex[0] - 1];
					vx2.normal = temp_normals[normalIndex[1] - 1];
					vx3.normal = temp_normals[normalIndex[2] - 1];

					vx1.texLoc = glm::vec3(0.0f);
					vx2.texLoc = glm::vec3(0.0f);
					vx3.texLoc = glm::vec3(0.0f);

					tmp_vertex.push_back(vx1);
					tmp_vertex.push_back(vx2);
					tmp_vertex.push_back(vx3);
				}
				else {
					int matches = sscanf(f_line, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
					if (matches == 6) {
						Vertex vx1, vx2, vx3;
						vx1.position = temp_vertices[vertexIndex[0] - 1];
						vx2.position = temp_vertices[vertexIndex[1] - 1];
						vx3.position = temp_vertices[vertexIndex[2] - 1];

						vx1.normal = temp_normals[normalIndex[0] - 1];
						vx2.normal = temp_normals[normalIndex[1] - 1];
						vx3.normal = temp_normals[normalIndex[2] - 1];

						vx1.texLoc = glm::vec3(0.0f);
						vx2.texLoc = glm::vec3(0.0f);
						vx3.texLoc = glm::vec3(0.0f);

						tmp_vertex.push_back(vx1);
						tmp_vertex.push_back(vx2);
						tmp_vertex.push_back(vx3);
					}
					else {
						matches = sscanf(f_line, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
						if (matches == 3) {
							Vertex vx1, vx2, vx3;
							vx1.position = temp_vertices[vertexIndex[0] - 1];
							vx2.position = temp_vertices[vertexIndex[1] - 1];
							vx3.position = temp_vertices[vertexIndex[2] - 1];

							vx1.normal = glm::vec3(-1.0f);
							vx2.normal = glm::vec3(-1.0f);
							vx3.normal = glm::vec3(-1.0f);

							vx1.color = glm::vec3(0.5f);
							vx2.color = glm::vec3(0.5f);
							vx3.color = glm::vec3(0.5f);

							vx1.texLoc = glm::vec3(0.0f);
							vx2.texLoc = glm::vec3(0.0f);
							vx3.texLoc = glm::vec3(0.0f);

							tmp_vertex.push_back(vx1);
							tmp_vertex.push_back(vx2);
							tmp_vertex.push_back(vx3);
						}
						else {
							printf("ERROR [ObjLoader]: Couldn't parse file: %s. Try another format.\n", path);
							fclose(file);
							return false;
						}
					}
				}
				
			}
		}
		else {
			// Unused data
			char unusedBuffer[1000];
			fgets(unusedBuffer, 1000, file);
		}

	}

	out_vector_vertex = tmp_vertex;
	fclose(file);
	return true;
}

bool LoadObjToMesh(const char * file, Mesh & out_mesh, Texture2D & out_texture, ShadersProgram* shader)
{
	std::vector<Vertex> obj_vertices;
	std::string obj_texture_file;
	if (!LoadObj(file, obj_vertices, obj_texture_file))
		return false;
	std::vector<GLuint> obj_indices;
	for (unsigned int i = 0; i < obj_vertices.size(); i++)
		obj_indices.push_back(i);

	if (obj_texture_file != "")
	{
		out_texture = Texture2D(obj_texture_file.c_str(), GL_TEXTURE0);
		out_texture.DisactivateAndUnbind();
	}

	out_mesh = Mesh(obj_vertices, obj_indices, shader);

	return true;
}
