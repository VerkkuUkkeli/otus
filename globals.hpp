// This file contains all of global variables of this program.
// All of the variables here should contain an explanation 
// about why the variables were allowed to have global scope.

#include "Camera.hpp"
#include "RigidBody.hpp"
#include "Particle.hpp"
#include <vector>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#ifdef __gnu_linux__
#include <GL/gl.h>
#include <GL/glu.h>
#endif

// glut's display routine requires the camera as an argument to the 
// display() callback. display() doesn't support arguments so having
// a global camera is the only way to do this.
extern Camera cam;

// Same issue with display as with camera. RigidBody needs to be able
// to respond to keyboard callbacks but is updated from display function.
extern RigidBody body;

// display needs to access to shaderprogram which is initialised in main
extern GLuint shaderprogram;

// display needs access to particles initialised in main
extern vector<Particle*> particles;
