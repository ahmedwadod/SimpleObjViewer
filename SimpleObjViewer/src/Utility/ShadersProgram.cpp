#include "ShadersProgram.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream ifs(filename);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	
	ifs.close();
	return content;
}

ShadersProgram::ShadersProgram(const char* vertexShaderSourceFile, const char* fragmentShaderSourceFile)
{
	auto vertexFile = get_file_contents(vertexShaderSourceFile);
	const char* vertexShaderSource = vertexFile.c_str();
	auto fragmentFile = get_file_contents(fragmentShaderSourceFile);
	const char* fragmentShaderSource = fragmentFile.c_str();

	if (vertexFile == "")
	{
		std::cout << "ERROR [ShadersProgram]: Couldn't load file: " << vertexShaderSourceFile << "\n";
		_compiled = false;
		return;
	}
	if (fragmentFile == "")
	{
		std::cout << "ERROR [ShadersProgram]: Couldn't load file: " << fragmentShaderSourceFile << "\n";
		_compiled = false;
		return;
	}

	// Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	// Get compilation errors if any
	_compiled = HasCompiledShader(vertexShader, vertexShaderSourceFile) && 
				HasCompiledShader(fragmentShader, fragmentShaderSourceFile) && 
				HasCompiledProgram();

	// Delete shaders because they're already in memory
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShadersProgram::Activate()
{
	glUseProgram(ID);
}

void ShadersProgram::Delete()
{
	glDeleteProgram(ID);
}

bool ShadersProgram::HasCompiledShader(unsigned int shader, const char* shaderName)
{
	GLint hasCompiled;
	char infoLog[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
	if (hasCompiled == GL_FALSE)
	{
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		std::cout << "ERROR [ShadersProgram]: Compilation FAILED for shader: " << shaderName << "\nLog:\n";
		std::cout << infoLog;
		return false;
	}

	return true;
}

bool ShadersProgram::HasCompiledProgram()
{
	GLint hasCompiled;
	char infoLog[1024];
	glGetProgramiv(ID, GL_COMPILE_STATUS, &hasCompiled);
	if (hasCompiled == GL_FALSE)
	{
		glGetProgramInfoLog(ID, 1024, NULL, infoLog);
		std::cout << "ERROR [ShadersProgram]: Compilation FAILED for Shaders Program!\n " << "Log:\n";
		std::cout << infoLog;
		return false;
	}

	return true;
}

bool ShadersProgram::HasCompiled()
{
	return _compiled;
}

GLuint ShadersProgram::GetUniform(const GLchar* name)
{
	return glGetUniformLocation(ID, name);
}
