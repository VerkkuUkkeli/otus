#include "display.hpp"

using namespace std;

void drawCursor(glm::vec4 focus)
{
    float x = focus.x;
    float y = focus.y;
    float z = focus.z;

    // spacing between cursor and line inner point
    float in = 0.02;
    
    // line length
    float len = 0.04;

    // vertical 
    glBegin(GL_LINES);
        // upper
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x, y, z + in);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x, y, z + in + len);

        // lower 
        glColor3f(0.3, 0.3, 0.3);
        glVertex3f(x, y, z - in);
        glColor3f(0.3, 0.3, 0.3);
        glVertex3f(x, y, z - in - len);
    glEnd();

    // x
    glBegin(GL_LINES);
        // positive
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(x + in, y, z);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(x + in + len, y, z);

        // negative 
        glColor3f(0.3, 0.3, 0.3);
        glVertex3f(x - in, y, z);
        glColor3f(0.3, 0.3, 0.3);
        glVertex3f(x - in - len, y, z);
    glEnd();

    // y
    glBegin(GL_LINES);
        // positive
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(x , y + in, z);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(x, y + in + len, z);

        // negative 
        glColor3f(0.3, 0.3, 0.3);
        glVertex3f(x , y - in, z);
        glColor3f(0.3, 0.3, 0.3);
        glVertex3f(x, y - in - len, z);
    glEnd();
}

// compute force on p1 by p2
glm::vec3 computeGravity(Particle* p1, Particle* p2)
{
    float gconst = 1e-6;

    // displacement
    glm::vec3 disp = p2->s - p1->s;
    float r = disp.length();

    glm::vec3 F = (float)((gconst*p1->m*p2->m)/pow(r, 2))*glm::normalize(disp);
    return F;
}

// callback for displaying to the screen
void display()
{
    // moderate framerate and keep track of dt
    static float lastTime = 0.0f;
    float dt = glutGet(GLUT_ELAPSED_TIME) - lastTime;
    float framerate = 60.0f;
    if (dt < 1000/(framerate))
    {
        return;
    }
    lastTime = glutGet(GLUT_ELAPSED_TIME);

        // RigidBody assumes that time is in seconds
    body.sim_step(dt/1000.0f);
    State s = body.getState();
    //cout << s.x.x << " " << s.x.y << " " << s.x.z << endl;

    // clear screen before drawing
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // simulate particles by brute force
    /*
    for (int i = 0; i < particles.size(); i++)
    {
        Particle* current = particles[i];
        glm::vec3 F = glm::vec3(0.0f);
        for (int j = 0; j < particles.size(); j++)
        {
            if (i != j)
            {
                F += computeGravity(current, particles[j]);
            }
        }
        current->calculate(F, dt);
        current->draw(cam.getModelview());
    }
    */

    drawGround(30.0);
    drawAxes();

    mat4 mv = cam.getModelview()*body.getTransformation();
    glPushMatrix();
    glLoadMatrixf(&mv[0][0]);
    glutSolidTeapot(1.0);
    glPopMatrix();

    drawCursor(cam.focus);

    // swap buffers to display image
    glutSwapBuffers();
}

void drawAxes()
{
    // coordinate axes
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_LINES); // X
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
    glEnd();

    glBegin(GL_LINES); // Y
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);
    glEnd();

    glBegin(GL_LINES); // Z
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 1.0);
    glEnd();
    glEnable(GL_DEPTH_TEST);
}

void drawGround(float r)
{
    // ground plane
    glBegin(GL_POLYGON);
        glColor4f(0.5, 0.5, 0.5, 0.5);
        glVertex3f(r, r, 0.0);
        glColor4f(0.5, 0.5, 0.5, 0.5);
        glVertex3f(-r, r, 0.0);
        glColor4f(0.5, 0.5, 0.5, 0.5);
        glVertex3f(-r, -r, 0.0);
        glColor4f(0.5, 0.5, 0.5, 0.5);
        glVertex3f(r, -r, 0.0);
    glEnd();

    // ground grid
    glDisable(GL_DEPTH_TEST);
    for (float i = -r; i <= r; i+=1.0)
    {
        // vertical
        glBegin(GL_LINES);
            glColor3f(0.0, 0.0, 0.0);
            glVertex3f(i, -r, 0);
            glColor3f(0.0, 0.0, 0.0);
            glVertex3f(i, r, 0);
        glEnd();

        // horizontal 
        glBegin(GL_LINES);
            glColor3f(0.0, 0.0, 0.0);
            glVertex3f(-r, i, 0);
            glColor3f(0.0, 0.0, 0.0);
            glVertex3f(r, i, 0);
        glEnd();
    }
    glEnable(GL_DEPTH_TEST);
}
