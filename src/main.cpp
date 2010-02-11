#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <sys/utsname.h>  // For Systeminfo

#include "Anaglyph.h"

using namespace std;

Anaglyph anaglyph;
GLboolean CheckExtension(char *extName);

int	lastTime = glutGet(GLUT_ELAPSED_TIME),
	timebase = 0,
	frames = 0;

float fps;

int VIEW_WIDTH = 500;
int VIEW_HEIGHT = 459;

void show_system_infos() {
  // shows basic system information
  utsname u;   // requires <sys/utsname.h>
  uname(&u);   // info structure
  cout << "System Information ----" << endl;
  cout << u.sysname << " " << u.release << endl;
  cout << "Version: " << u.version << endl;
  cout << "Architecture: " << u.machine << endl;
  cout << "Hostname: " << u.nodename << endl;
  cout << endl;
  
#ifndef _POSIX_THREAD_PROCESS_SHARED
cout << "GUI: This system does not support process shared mutex" << endl;
exit(EXIT_FAILURE);
#endif
}

/* Search for extName in the extension string */
/* From the OpenGL 1.1 Programming Guide */
GLboolean CheckExtension(const char *extName)
{
    char *p = (char *) glGetString(GL_EXTENSIONS);
    char *end;
    int extNameLen;

    extNameLen = strlen(extName);
    end = p + strlen(p);

    while (p < end) {
        int n = strcspn(p, " ");
        if ((extNameLen == n) && (strncmp(extName, p, n) == 0)) {
            return GL_TRUE;
        }
        p += (n + 1);
    }
    return GL_FALSE;
}

bool show_gl_infos() {
	// shows OpenGL versions
	cout << "OpenGL ----" << endl;
	fprintf(stdout, "GL_VENDOR: %s\n", glGetString(GL_VENDOR));
	fprintf(stdout, "GL_RENDERER: %s\n", glGetString(GL_RENDERER));
	fprintf(stdout, "GL_VERSION: %s\n", glGetString(GL_VERSION));
	
	// GLEW
	cout << "GLEW ----" << endl;
	fprintf(stdout, "GLEW_VERSION: %s\n", glewGetString(GLEW_VERSION));
	cout << endl;
	
	cout << "GL Extensions ----" << endl;
	
	// check for PBO support
	if (glewIsSupported("GL_ARB_pixel_buffer_object"))
	{
		cout << "GL_ARB_pixel_buffer_object";
		cout << " PRESENT" << endl;
	}
	else
	{
		cerr << "GL_ARB_pixel_buffer_object";
		cerr << " NOT SUPPORTED" << endl;
		return false; // return false if the feature is required for the implementation
	}
	
	if ((CheckExtension("GL_ARB_vertex_shader") &&
			CheckExtension("GL_ARB_fragment_shader") &&
			CheckExtension("GL_ARB_shader_objects") &&
			CheckExtension("GL_ARB_shading_language_100")) == GL_TRUE) {
		cout << "You have the support for OpenGL Shading Language (GLSL)" << std::endl;
	}
	else {
		cout << "Missing extensions for OpenGL Shading Language (GLSL)" << std::endl;
		return false;
	}
		
	
	return true;
}

// the display callback function
void display (void) {
	
	//glClearColor (0.0, 0.0, 0.0, 1.0);
	//glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	anaglyph.render();
	
	// clear the screen and buffers
	//drawScene();			// redraw managed by action-manager TM
	glutSwapBuffers(); 		// swap the the front and back buffers
}

// GLUT callback: accomodate window resizing if in windowed mode
void reshape (int w, int h) 
{

}

// GLUT callback: handle mouse events
void processMouse(int button, int state, int x, int y) {

}

// handle special keys; F1 and F2 are used to switch between views
void specialKeyPress(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_F1:
			anaglyph.toggleColor();
			break;
		case GLUT_KEY_F2:
			anaglyph.toggleShader();
			break;
	}
}

// handle keys
void keyPress(unsigned char key, int x, int y) {
	switch (key) {
		case 27:
			exit(0);
			break;
	}
}

// mark the window for redisplay
void idle() {
	glutPostRedisplay();
	
	frames++;
	int currTime = glutGet(GLUT_ELAPSED_TIME);

	if(currTime - timebase > 10)
	{
		printf("FPS: %4.2f\r",fps);
		if(currTime - timebase > 1000)
		{
			fps = frames * 1000 / float(currTime - timebase);
			timebase = currTime;
			frames = 0;
		}
	}
	
}

int main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_ACCUM | GLUT_RGB | GLUT_DEPTH); 	
	
	char gameModeString[12];
	sprintf(gameModeString, "%dx%d:32", VIEW_WIDTH, VIEW_HEIGHT); 
	std::cout << gameModeString << std::endl;
	
	glutGameModeString(gameModeString);
	if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
		glutEnterGameMode();

	} else {
		glutInitWindowSize (VIEW_WIDTH, VIEW_HEIGHT);
		glutInitWindowPosition (0, 0);
		glutCreateWindow ("anaglyph testing");
	}	

	// initialize GLEW (OpenGL extension wrangler) ---------------------
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "GUI: Error: %s\n", glewGetErrorString(err));
		return 1;  // Terminate if Features not present
	}
	
	// Output System Infos to Console
	show_system_infos();	
	
	if (!show_gl_infos())
		return 1;

	// define the glut callback functions
	glutMouseFunc(processMouse);
	glutKeyboardFunc(keyPress);
	glutSpecialFunc(specialKeyPress);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	
	anaglyph.initialize();
	
	glutMainLoop();
	
	return 0;
}

