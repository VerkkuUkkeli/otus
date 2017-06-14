#include "RigidBody.hpp"
#include <iostream>

using namespace std;

RigidBody::RigidBody()
{
    mass = 1.0;
    Ibody = (mass/12.0f)*mat3(1.0f);
    Ibodyinv = inverse(Ibody);

    x = vec3(0.0f, 0.0f, 2.0f);
    R = mat3(1.0f);
    P = vec3(0.0f);
    L = vec3(0.0f, 0.0f, 0.0f);

    Iinv = R*Ibodyinv*transpose(R);
    v = P/mass;
    omega = Iinv * L;

    force = vec3(0.0f, 0.0f, 0.0f);
    torque = vec3(0.0, 0.0, 0.0);

    size = 0.5f;
}

// TODO: Add initial variables so that reset values are not hardcoded.
void RigidBody::reset()
{
    cout << "Body reset!" << endl;
    mass = 1.0;
    Ibody = (mass/12.0f)*mat3(1.0f);
    Ibodyinv = inverse(Ibody);

    x = vec3(0.0f, 0.0f, 2.0f);
    R = mat3(1.0f);
    P = vec3(0.0f);
    L = vec3(0.0f, 0.0f, 0.0f);

    Iinv = R*Ibodyinv*transpose(R);
    v = P/mass;
    omega = Iinv * L;

    force = vec3(0.0f, 0.0f, 0.0f);
    torque = vec3(0.0, 0.0, 0.0);

    size = 0.5f;
}

// simulate one step forward
// the time step in the argument in in simulation time
void RigidBody::sim_step(float dt)
{
    Iinv = R*Ibodyinv*transpose(R);
    v = P/mass;
    omega = Iinv * L;

    // the time step used by the solver is different (preferably smaller)
    // than the time step of the simulation 
    // forces are constant only (for now) so time is assumed 0 to dt for every update
    // vec3 EulerMethod(vec3 V0, float t0, float t_end, float dt, dV3dt_func dV3dt)
    x = EulerMethod(x, 0, dt, 0.01f, dxdt(0, x));
    R = EulerMethod(R, 0, dt, 0.01f, dRdt(0, R));

    // normalise vectors in R and make sure that they are orthogonal
    vec3 w = normalize(R[2]);
    vec3 u = normalize(cross(R[1], w));
    vec3 v = cross(w, u);
    R = mat3(u, v, w);
    

    P = EulerMethod(P, 0, dt, 0.01f, force);
    L = EulerMethod(L, 0, dt, 0.01f, torque);

}

mat3 RigidBody::dRdt(float t, mat3 R)
{
    // dual defined in helpers.hpp
    return dual(omega)*R;
}

vec3 RigidBody::dxdt(float t, vec3 V)
{
    return v;
};

State RigidBody::getState()
{
    State s;
    s.x = x;
    s.R = R;
    s.P = P;
    s.L = L;
    return s;
}

mat4 RigidBody::getTransformation()
{
    mat4 S = Transform::scale(size, size, size);
    mat4 T = Transform::translate(x);
    mat4 Rot = Transform::rotate(R);
    return T*Rot*S;
}
