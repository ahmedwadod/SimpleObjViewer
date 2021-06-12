#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <iostream>
#include <stb\stb_image.h>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

class Texture2D {
protected:
	GLenum _slot;
public:
	GLuint ID;
	Texture2D();
	Texture2D(const char* filename, GLenum textureSlot, 
						GLenum filter_min = GL_NEAREST, GLenum filter_mag = GL_NEAREST,
						GLenum wrap_s = GL_REPEAT, GLenum wrap_t = GL_REPEAT);
	void ActivateAndBind();
	void DisactivateAndUnbind();
	void Delete();
};
#endif