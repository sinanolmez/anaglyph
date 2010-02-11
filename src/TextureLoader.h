#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <string>
#include <iostream>
#include <sstream>

#include <GL/gl.h>
#include <FreeImage.h>

class TextureLoader
{
public:
	TextureLoader(void);
	~TextureLoader(void);
	static void load(std::string texture, unsigned int* texID);
	static void loadBw(std::string texture, unsigned int* texID);
};

#endif
