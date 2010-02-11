#include "TextureLoader.h"

TextureLoader::TextureLoader(void)
{
}

TextureLoader::~TextureLoader(void)
{
}

void TextureLoader::load(std::string texture, unsigned int* texID)	
{
	// Get the image file type from FreeImage.
	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(texture.c_str(), 0);

	// Actually load the image file.
	FIBITMAP *dib = FreeImage_Load(fifmt, texture.c_str(),0);

	// Now, there is no guarantee that the image file
	// loaded will be GL_RGB, so we force FreeImage to
	// convert the image to GL_RGB.
		dib = FreeImage_ConvertTo24Bits(dib);
	
	if( dib != NULL )
	{
		glGenTextures(1, texID);

		glBindTexture(GL_TEXTURE_2D, *texID);
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

		// This is important to note, FreeImage loads textures in
		// BGR format. Now we could just use the GL_BGR extension
		// But, we will simply swap the B and R components ourselves.
		// Firstly, allocate the new bit data doe the image.
		BYTE *bits = new BYTE[FreeImage_GetWidth(dib) * FreeImage_GetHeight(dib) * 3];

		// get a pointer to FreeImage's data.
		BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);

		// Iterate through the pixels, copying the data
		// from 'pixels' to 'bits' except in RGB format.
		for(unsigned int pix=0; pix<FreeImage_GetWidth(dib) * FreeImage_GetHeight(dib); pix++)
		{
			bits[pix*3+0]=pixels[pix*3+2];
			bits[pix*3+1]=pixels[pix*3+1];
			bits[pix*3+2]=pixels[pix*3+0];

		}
			 
		// The new 'glTexImage2D' function, the prime difference
		// being that it gets the width, height and pixel information
		// from 'bits', which is the RGB pixel data..
		glTexImage2D( GL_TEXTURE_2D, 0, 3, FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 0,
				GL_RGB, GL_UNSIGNED_BYTE, bits );

	/*	glMatrixMode (GL_TEXTURE);
		glLoadIdentity ();
		glScalef (1.0f, -1.0f, 1.0f);
		glTranslatef (0.0f, -1.0f, 0.0f);
		glMatrixMode (GL_MODELVIEW);*/

		// Unload the image.
		// and free the bit data.
		FreeImage_Unload(dib);
		delete bits;
	} else {
		std::cout << "could not load texture" << std::endl;
	}
}

void TextureLoader::loadBw(std::string texture, unsigned int* texID)	
{
	// Get the image file type from FreeImage.
	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(texture.c_str(), 0);

	// Actually load the image file.
	FIBITMAP *dib = FreeImage_Load(fifmt, texture.c_str(),0);

	// Now, there is no guarantee that the image file
	// loaded will be GL_RGB, so we force FreeImage to
	// convert the image to GL_RGB.
		//dib = FreeImage_ConvertTo8Bits(dib);
	
	if( dib != NULL )
	{
		glGenTextures(1, texID);

		glBindTexture(GL_TEXTURE_2D, *texID);
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

		// This is important to note, FreeImage loads textures in
		// BGR format. Now we could just use the GL_BGR extension
		// But, we will simply swap the B and R components ourselves.
		// Firstly, allocate the new bit data doe the image.
		BYTE *bits = new BYTE[FreeImage_GetWidth(dib) * FreeImage_GetHeight(dib)];

		// get a pointer to FreeImage's data.
		BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);

		for(unsigned int pix=0; pix<FreeImage_GetWidth(dib) * FreeImage_GetHeight(dib); pix++)
		{
			bits[pix]=pixels[pix];
		}

		// Iterate through the pixels, copying the data
		// from 'pixels' to 'bits' except in RGB format.
			 
		// The new 'glTexImage2D' function, the prime difference
		// being that it gets the width, height and pixel information
		// from 'bits', which is the RGB pixel data..
		glTexImage2D( GL_TEXTURE_2D, 0, GL_LUMINANCE, FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 0,
				GL_LUMINANCE, GL_UNSIGNED_BYTE, bits );

	/*	glMatrixMode (GL_TEXTURE);
		glLoadIdentity ();
		glScalef (1.0f, -1.0f, 1.0f);
		glTranslatef (0.0f, -1.0f, 0.0f);
		glMatrixMode (GL_MODELVIEW);*/

		// Unload the image.
		// and free the bit data.
		FreeImage_Unload(dib);
		delete bits;
	} else {
		std::cout << "could not load texture" << std::endl;
	}
}
