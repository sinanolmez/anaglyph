/*! \file Anaglyph.cpp
	\brief Anaglyph source file.

	Contains the source code for the Anaglyph class, used to create and test an anaglyph shader.
	
	Created on February 9, 2010
*/
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "Anaglyph.h"

#include <stdio.h>

void printInfoLog(GLhandleARB obj);

Anaglyph::Anaglyph(void) {
	colorMode = false;
	shaderMode = 0;
}

Anaglyph::~Anaglyph(void) {
	glDeleteTextures(1, &tex1);
	glDeleteTextures(1, &tex2);
	glDeleteTextures(1, &tex1bw);
	glDeleteTextures(1, &tex2bw);
}

void Anaglyph::initialize(void) {
	tex1_name = "textures/gibberlings_l.tif";
	tex2_name = "textures/gibberlings_r.tif";
	TextureLoader::load(tex1_name, &tex1);
	TextureLoader::load(tex2_name, &tex2);

	tex1bw_name = "textures/gibberlings_l_bw.tif";
	tex2bw_name = "textures/gibberlings_r_bw.tif";
	TextureLoader::loadBw(tex1bw_name, &tex1bw);
	TextureLoader::loadBw(tex2bw_name, &tex2bw);
	
	createShader();
}

void Anaglyph::createShader(void) {
	
	GLint compiledv, compiledf, linked;

	GLchar* fragmentSource;
	GLchar* vertexSource;

	vertexShader = glCreateShaderObjectARB(GL_VERTEX_SHADER);
	fragmentShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER);

	vertexSource = Helper::readShader("shaders/anaglyph.vert");
	fragmentSource = Helper::readShader("shaders/anaglyph.frag");

	glShaderSource(vertexShader, 1, const_cast<const GLchar**>(&vertexSource), 0);
	glShaderSource(fragmentShader, 1, const_cast<const GLchar**>(&fragmentSource), 0);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	anaglyphProgram = glCreateProgram();
	glAttachShader(anaglyphProgram, vertexShader);
	glAttachShader(anaglyphProgram, fragmentShader);
	glLinkProgram(anaglyphProgram);
	
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiledv);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiledf);

	glGetProgramiv(anaglyphProgram, GL_LINK_STATUS, &linked);

	if (!compiledv)
		std::cout << "vertex shader not compiled" << std::endl;
	if (!compiledf)
		std::cout << "fragment shader not compiled" << std::endl;

	if (!linked)
		std::cout << "not linked " << std::endl;

	Helper::printInfoLog(anaglyphProgram);
}

void Anaglyph::render(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, float(499), float(458));
	glOrtho(0.0f,499,458,0.0f,-1.0f,1.0f);	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (shaderMode > 0) {
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

		glActiveTexture(GL_TEXTURE0);
		if (colorMode == true)
			glBindTexture(GL_TEXTURE_2D, tex1);
		else
			glBindTexture(GL_TEXTURE_2D, tex1bw);
		glActiveTexture(GL_TEXTURE1);
		if (colorMode == true)
			glBindTexture(GL_TEXTURE_2D, tex2);
		else
			glBindTexture(GL_TEXTURE_2D, tex2bw);

		glUseProgram(anaglyphProgram);
		glUniform1i(glGetUniformLocation(anaglyphProgram, "tex1"), 0);
		glUniform1i(glGetUniformLocation(anaglyphProgram, "tex2"), 1);
		glUniform1i(glGetUniformLocation(anaglyphProgram, "mode"), shaderMode);
	
	} else {
		glUseProgram(0);
		glDrawBuffer(GL_BACK);
		glReadBuffer(GL_BACK);
		
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE0);
		if (colorMode == true)
			glBindTexture(GL_TEXTURE_2D, tex1);
		else
			glBindTexture(GL_TEXTURE_2D, tex1bw);
		
		glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);
	}
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(0.0f,0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(499.0f,0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(499.0f,458.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(0.0f,458.0f);
	glEnd();
	
	if (shaderMode == 0) {
		glFlush();

		glDrawBuffer(GL_BACK);
		glClear(GL_DEPTH_BUFFER_BIT);
		
		if (colorMode == true)
			glBindTexture(GL_TEXTURE_2D, tex2);
		else
			glBindTexture(GL_TEXTURE_2D, tex2bw);

		glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE);
		
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(0.0f,0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(499.0f,0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(499.0f,458.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(0.0f,458.0f);
		glEnd();
		
		glFlush();
	}
}

void Anaglyph::toggleColor(void) {
	colorMode = !colorMode;
	std::cout << "Input Color Mode: ";
	if (colorMode) {
		std::cout << "RGB" << std::endl;
	} else {
		std::cout << "B/W" << std::endl;
	}
}

void Anaglyph::toggleShader(void) {
	shaderMode = (shaderMode + 1) % 3;
	std::cout << "Shader Mode: ";
	switch (shaderMode) {
		case 0:
			std::cout << "OFF (Color Mask)" << std::endl;
			break;
		case 1:
			std::cout << "SIMPLE" << std::endl;
			break;
		case 2:
			std::cout << "DUBOIS" << std::endl;
			break;
	}
}
