#ifndef PARTICLE
#define PARTICLE

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
#include "Transform.hpp"

using namespace glm;

class Particle
{
    public:
        float m;
        vec3 s;
        vec3 v;
        vec3 a;
        vec3 F;

        Particle(float m0, vec3 s0, vec3 v0);
        void calculate(vec3 F, float dt);
        void draw(mat4 mv);
};

vec3 circleV0(float x, float y, float z);

#endif
