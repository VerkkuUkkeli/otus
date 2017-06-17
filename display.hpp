#ifndef DISPLAY
#define DISPLAY

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#ifdef __gnu_linux__
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <GL/glut.h>
#include <glm/glm.hpp>
#include "globals.hpp"
#include "RigidBody.hpp"
#include <iostream>

void drawCursor(glm::vec4 focus);
void drawGround(float r);
void drawAxes();
void display();

glm::vec3 computeGravity(Particle* p1, Particle* p2);

#endif
