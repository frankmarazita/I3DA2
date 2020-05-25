// Holds a texture which is loaded in via file name through the constructor
// Provides a method to enable the texture and to disable it

#ifndef TEXTURE_H
#define TEXTURE_H

#include "opengl.h"

#include <stdint.h>

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture
{
public:
	Texture(const char* filename);

	void enable();
	void disable();

private:
	GLuint texture;
};

#endif