#ifndef SHADERS_PROGRAM_H
#define SHADERS_PROGRAM_H

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <fstream>

std::string get_file_contents(const char* filename);

class ShadersProgram {
protected:
	bool HasCompiledShader(unsigned int shader, const char* shaderName);
	bool HasCompiledProgram();
	bool _compiled;
public:
	GLuint ID;

	ShadersProgram(const char* vertexShaderSourceFile, const char* fragmentShaderSourceFile);
	void Activate();
	void Delete();
	bool HasCompiled();
	GLuint GetUniform(const GLchar* name);
};

#endif