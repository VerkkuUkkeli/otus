#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <glm/glm.hpp>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "helpers.hpp"
#include "Camera.hpp"
#include "ODE.hpp"

using namespace std;

Camera cam{};

// Callback Functions
    // keyboard callback function
    void keyboard(unsigned char key, int x, int y)
    {
        switch (key)
        {
            case 27: // ESC
                cout << "Exiting..." << endl;
                exit(0);
                break;
            case 'c':
                cam.toggleMode();
                // store mouse location for fps
                cam.storeMouseLoc(x, y);
                break;
            default:
                break;
        }

        if (cam.getMode() == cam.CAM_FPS)
        {
            switch (key)
            {
                case 'w':
                    cam.mov_forward(1.0);
                    break;
                case 'a':
                    cam.mov_sideways(-1.0);
                    break;
                case 's':
                    cam.mov_forward(-1.0);
                    break;
                case 'd':
                    cam.mov_sideways(1.0);
                    break;
                case 'q':
                    cam.mov_upward(-1.0);
                    break;
                case 'e':
                    cam.mov_upward(1.0);
                    break;
                case '+':
                    cam.changeSpeed(0.1);
                    break;
                case '-':
                    cam.changeSpeed(-0.1);
                    break;
            }
        }
        glutPostRedisplay();
    }

    // callback function for special keys (e.g. arrow keys)
    void SpecialInput(int key, int x, int y)
    {
        if (cam.getMode() == cam.CAM_ORBIT)
        {
            switch (key)
            {
                case GLUT_KEY_LEFT:
                    cam.rot_h(-0.1);
                    break;
                case GLUT_KEY_RIGHT:
                    cam.rot_h(0.1);
                    break;
                case GLUT_KEY_UP:
                    cam.rot_v(-0.1);
                    break;
                case GLUT_KEY_DOWN:
                    cam.rot_v(0.1);
                    break;
            }
        }
        glutPostRedisplay();
    }

    // callback function for mouse press events
    void mouse(int button, int state, int x, int y)
    {
        if (cam.getMode() == cam.CAM_ORBIT)
        {
            if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
            {
                cam.storeMouseLoc(x, y);
            }
        }
    }

    // callback function for mouse drag
    void motion(int x, int y)
    {
        if (cam.getMode() == cam.CAM_ORBIT)
        {
            cam.rot_mouse(x, y);
            cam.storeMouseLoc(x, y);
            glutPostRedisplay();
        }
    }

    // callback function for mouse motion without drag
    void passiveMotion(int x, int y)
    {
        if (cam.getMode() == cam.CAM_FPS)
        {
            cam.rot_fps(x, y);
            cam.storeMouseLoc(x, y);
            glutPostRedisplay();
        }
    }

    // callback for change in window shape
    void reshape(int width, int height)
    {
        glViewport(0, 0, (GLsizei) width, (GLsizei) height);
        cam.storeScreenSize(width, height);
        cam.update();
        glutPostRedisplay();
    }

    // callback for displaying to the screen
    void display()
    {
        // clear screen before drawing
        glClear(GL_COLOR_BUFFER_BIT);

        // radius of xy ground plane
        float r = 30.0;

        // ground plane
        glBegin(GL_POLYGON);
            glColor3f(0.5, 0.5, 0.5);
            glVertex3f(r, r, 0.0);
            glColor3f(0.5, 0.5, 0.5);
            glVertex3f(r, -r, 0.0);
            glColor3f(0.5, 0.5, 0.5);
            glVertex3f(-r, -r, 0.0);
            glColor3f(0.5, 0.5, 0.5);
            glVertex3f(-r, r, 0.0);
        glEnd();

        // ground grid
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

        // coordinate axes
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

        glFlush();
    }

int main(int argc, char* argv[])
{
    // Initialisation
    glutInit(&argc, argv);

    glutInitWindowPosition(1920/8, 1080/8);
    glutInitWindowSize(1920/2, 1080/2);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutCreateWindow("aaa");

    glewInit();
    glClearColor(0.259, 0.525, 0.957, 1.0);
    help();

    // callback functions
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutSpecialFunc(SpecialInput);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passiveMotion);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
