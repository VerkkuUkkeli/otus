#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#ifdef __gnu_linux__
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <GL/glut.h>
#include <iostream>
#include "globals.hpp"

void keyboard(unsigned char key, int x, int y);
void SpecialInput(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void passiveMotion(int x, int y);
void reshape(int width, int height);
