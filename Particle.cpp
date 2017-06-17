#include "Particle.hpp"

Particle::Particle(float m0, vec3 s0, vec3 v0)
{
    m = m0;
    s = s0;
    v = v0;
}

// F is the net force
void Particle::calculate(vec3 F, float dt)
{
    a = F/m;
    v += a*dt;
    s += v;
}

void Particle::draw(mat4 mv)
{
    /*
    glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(s.x, s.y, s.z);
    glEnd();
    */
    mat4 T = mv*Transform::translate(s.x, s.y, s.z);
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glLoadMatrixf(&T[0][0]);
        glutSolidSphere(0.05f, 8, 16);
    glPopMatrix();
}

vec3 circleV0(float x, float y, float z)
{
    return vec3(y/50.0f, -x/50.0f, 0.0f);
}
