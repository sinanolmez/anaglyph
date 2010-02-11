#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <iostream>
#include <stdlib.h>
#include <GL/gl.h>

class Helper
{
public:
	Helper(void);
	~Helper(void);
	static void check_gl_error(std::string from);
	static char* readShader(const char *fn);
	static void printInfoLog(GLhandleARB obj);
};

#endif
