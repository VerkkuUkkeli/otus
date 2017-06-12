// This file contains all of global variables of this program.
// All of the variables here should contain an explanation 
// about why the variables was allowed to have global scope.

#include "Camera.hpp"

// glut's display routine requires the camera as an argument to the 
// display() callback. display() doesn't support arguments so having
// a global camera is the only way to do this.
extern Camera cam;
