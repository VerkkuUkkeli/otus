#ifndef SHADER
#define SHADER

#include <GL/glew.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#ifdef __gnu_linux__
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

string readTextFile(const char * filename);
void programErrors(const GLint program);
void shaderErrors(const GLint shader);
GLuint compileShader(GLenum type, const char * filename);
GLuint initProgram(GLuint vertexshader, GLuint fragmentshader);

#endif
