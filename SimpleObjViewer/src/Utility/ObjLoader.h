#pragma once

#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include <glm/glm.hpp>

#include "VBO.h"
#include "Mesh.h"

bool LoadObj(
	const char * path,
	std::vector<Vertex> & out_vector_vertex,
	std::string & out_texture_file
	);

bool LoadObjToMesh(
	const char * path,
	Mesh & out_mesh,
	Texture2D & out_texture,
	ShadersProgram* shader
	);