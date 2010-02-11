#include "Helper.h"

/* OpenGL debugging helper function */
void Helper::check_gl_error (std::string from) {
	std::cout << from + " - ";
	GLenum i;
	switch ((i = glGetError())) {
		case GL_NO_ERROR: std::cout << "no error" << std::endl; break;
		case GL_INVALID_ENUM:          std::cout << "invalid enum" << std::endl;      break;
		case GL_INVALID_VALUE:         std::cout <<  "invalid value" << std::endl;     break;
		case GL_INVALID_OPERATION:     std::cout <<  "invalid operation" << std::endl; break;
		case GL_STACK_OVERFLOW:        std::cout <<  "stack overflow" << std::endl;    break;
		case GL_STACK_UNDERFLOW:       std::cout <<  "stack underflow" << std::endl;   break;
		case GL_OUT_OF_MEMORY:         std::cout <<  "out of memory" << std::endl;     break;
		default:
			std::cout << "unknown error" << std::endl;
			break;
	}
}

char* Helper::readShader(const char *fn) {

	FILE *fp;
	char *content = NULL;
	int count=0;

	if (fn != NULL) {

		fp = fopen(fn,"rt");

		if (fp != NULL) {
										      
			fseek(fp, 0, SEEK_END);
        			count = ftell(fp);
        			rewind(fp);

			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}

			fclose(fp);
		} else {
			std::cout << "could not open file " << fn << std::endl;
		}
	}
	return content;
}

/* Print errors from shaders */
void Helper::printInfoLog(GLhandleARB obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;

	glGetObjectParameterivARB(obj, GL_OBJECT_INFO_LOG_LENGTH_ARB, &infologLength);														
	if (infologLength > 1) {
		infoLog = (char *)malloc(infologLength);
		glGetInfoLogARB(obj, infologLength, &charsWritten, infoLog);
		printf("OpenGL InfoLog: %s\n",infoLog);
		free(infoLog);
	}
}
