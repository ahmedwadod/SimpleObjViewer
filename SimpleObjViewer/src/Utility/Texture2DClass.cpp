#include "Texture2DClass.h"

Texture2D::Texture2D()
{
}

Texture2D::Texture2D(const char* filename, GLenum textureSlot,
						GLenum filter_min, GLenum filter_mag,
						GLenum wrap_s, GLenum wrap_t)
{
	// Get image
	int imgWidth, imgHeight, imgColorChns;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* imgBytes = stbi_load(filename, &imgWidth, &imgHeight, &imgColorChns, 0);

	if (imgBytes == NULL)
	{
		std::cout << "ERROR [Texture2D]: Couldn't load image file: " << filename << "\n";
	}

	// Get color channels for GL
	GLenum imgChannels;
	switch (imgColorChns)
	{
	case 3:
		imgChannels = GL_RGB;
		break;
	case 4:
		imgChannels = GL_RGBA;
		break;
	default:
		imgChannels = GL_RGB;
		break;
	}

	// Texture
	glGenTextures(1, &ID);
	_slot = textureSlot;
	glActiveTexture(_slot);
	glBindTexture(GL_TEXTURE_2D, ID);

	// Settting the filter type
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_mag);

	// Setting the wrap type for STR access
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrap_t);

	// Generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, imgChannels, imgWidth, imgHeight, 0, imgChannels, GL_UNSIGNED_BYTE, imgBytes);
	// Generate differnet sizes
	glGenerateMipmap(GL_TEXTURE_2D);

	// Delete the image
	stbi_image_free(imgBytes);
}

void Texture2D::ActivateAndBind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
	glActiveTexture(_slot);
}

void Texture2D::DisactivateAndUnbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(0);
}

void Texture2D::Delete()
{
	glDeleteTextures(1, &ID);
}