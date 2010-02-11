/*! \file Anaglyph.h
	\brief Anaglyph header file.

	Contains the declarations for the Anaglyph class, used to create and test an anaglyph shader.
	
	Created on February 9, 2010
*/

#ifndef _Anaglyph_h
#define _Anaglyph_h

#include <string>

#include "TextureLoader.h"
#include "Helper.h"

//! @brief Class which is used to create and test an anaglyph shader.
class Anaglyph
{
	public:
		
		//! The constructor.
		//!
		Anaglyph(void);
		
		//! The destructor.
		//!
		virtual ~Anaglyph(void);

		//! Loads the textures and calls createShader.
		//!
		void initialize(void);

		//! Draws the scene according to the current settings.
		//!
		void render(void);

		//! Changes the input color mode.
		//!
		void toggleColor(void);

		//! Changes the shader mode to be used.
		//!
		void toggleShader(void);

	private:

		//! Creates the shader program.
		//!
		void createShader(void);

		//! Stores the current shader mode.
		//!
		int shaderMode;
		
		//! Stores the current input color mode.
		//!
		bool colorMode;

		//! Handle for the shader program.
		//!
		GLuint anaglyphProgram;
		
		//! Handle for the vertex shader.
		//!
		GLuint vertexShader;
		
		//! Handle for the fragment shader
		//!
		GLuint fragmentShader;
		
		//! The name of the RGB texture for the left eye
		//!
		std::string tex1_name;
		
		//! Handle for the RGB texture for the left eye
		//!
		GLuint tex1;
		
		//! The name of the RGB texture for the right eye
		//!
		std::string tex2_name;
		
		//! Handle for the RGB texture for the right eye
		//!
		GLuint tex2;

		
		//! The name of the B/W texture for the left eye
		//!
		std::string tex1bw_name;
		
		//! Handle for the B/W texture for the left eye
		//!
		GLuint tex1bw;
		
		//! The name of the B/W texture for the right eye
		//!
		std::string tex2bw_name;
		
		//! Handle for the B/W texture for the right eye
		//!
		GLuint tex2bw;
};

#endif
