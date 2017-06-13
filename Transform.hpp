#ifndef TRANSFORM
#define TRANSFORM

#include <glm/glm.hpp>

using namespace glm;

namespace Transform
{
    mat4 rotate (vec3 axis, float rad);
    mat4 scale (vec3 amount);
    mat4 scale (float sx, float sy, float sz);
    mat4 translate(vec3 s);
    mat4 translate(float dx, float dy, float dz);
}

#endif
