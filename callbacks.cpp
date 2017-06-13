#include "callbacks.hpp"

using namespace std;

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
            // button set to -1 to not cause any Orbit mode rotations
            cam.storeMouseLoc(x, y, -1);
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
        // TODO: Add keyboard controls
    }
    glutPostRedisplay();
}

// callback function for mouse press events
void mouse(int button, int state, int x, int y)
{
    if (cam.getMode() == cam.CAM_ORBIT)
    {
        // only left click
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN 
                && glutGetModifiers() != GLUT_ACTIVE_SHIFT)
        {
            cam.storeMouseLoc(x, y, GLUT_LEFT_BUTTON);
        }
        // shift + left click
        else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN 
                && glutGetModifiers() == GLUT_ACTIVE_SHIFT)
        {
            cam.storeMouseLoc(x, y, 3);
        }
        // right click
        else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
            cam.storeMouseLoc(x,y, GLUT_RIGHT_BUTTON);
        }
    }
}

// callback function for mouse drag
void motion(int x, int y)
{
    if (cam.getMode() == cam.CAM_ORBIT)
    {
        cam.rot_mouse(x, y);
        cam.storeMouseLoc(x, y, cam.getMouseButton());
        glutPostRedisplay();
    }
}

// callback function for mouse motion without drag
void passiveMotion(int x, int y)
{
    if (cam.getMode() == cam.CAM_FPS)
    {
        cam.rot_fps(x, y);
        cam.storeMouseLoc(x, y, -1);
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

