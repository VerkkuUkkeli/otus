#include <vector>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

// solve ODE for a vector of equations
//typedef float (*dydt_func)(float t, float y);
//vector<float> EulerMethod(vector<float> y0, float t0, float t_end,
//      float dt, dydt_func dydt);

// solve ODE for a single equation
//float EulerMethod(float y0, float t0, float t_end,
//      float dt, dydt_func dydt);

// solve ODE for a 3x3 matrix value equation
// These functions do not use callback function for evaluating
// the time derivative because non-static member functions cannot
// be used as callback => RigidBody's member functions could not be
// passed to this and therefore have to be evaluated and the 
// result passed to these functions.
mat3 EulerMethod(mat3 M0, float t0, float t_end,
        float dt, mat3 dMdt);
vec3 EulerMethod(vec3 V0, float t0, float t_end,
        float dt, vec3 dV3dt);
