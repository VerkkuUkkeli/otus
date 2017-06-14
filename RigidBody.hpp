#ifndef RIGIDBODY
#define RIGIDBODY

#include "Transform.hpp"
#include <glm/glm.hpp>
#include "ODE.hpp"
#include "helpers.hpp"

using namespace glm;

typedef struct
{
    vec3 x;
    mat3 R;
    vec3 P;
    vec3 L;
} State;

class RigidBody
{
    private:
        // constants
        float mass;
        mat3 Ibody;
        mat3 Ibodyinv;

        // state variables
        vec3 x; // displacement of CM from origin
        mat3 R; // Orientation
        vec3 P; // Linear momentum
        vec3 L; // Angular momentum

        // derived quantities
        mat3 Iinv;  
        vec3 v;     // linear velocity
        vec3 omega; // angular velocity

        vec3 force;
        vec3 torque;

        // for drawing (assuming rigid body is a cube)
        float size;

    public:
        RigidBody();
        void reset();                // reset to original state
        void sim_step(float dt);    // simulate one step forward
        mat3 dRdt(float t, mat3 R);
        vec3 dxdt(float t, vec3 M);
        State getState();
        mat4 getTransformation();   // returns the transformation matrix from origin
};

#endif
