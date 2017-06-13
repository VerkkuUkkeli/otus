#include "Camera.hpp"
#include <iostream>
using namespace std;

Camera::Camera()
{
    loc     = glm::vec4(3.0, 3.0, 3.0, 0.0);
    focus   = glm::vec4(0.0, 0.0, 0.0, 0.0);
    up      = glm::vec4(-1.0, -1.0, 1.0, 0.0);
    dir     = focus - loc;
    far     = 250.0;
    near    = 0.1;
    mode    = CAM_ORBIT;
    speed   = 0.5;
    mb      = -1;
}

void Camera::rot_mouse(int x, int y)
{
    // update FPS mode direction vector to prevent 'jumping'
    // at camera mode change
    dir = glm::normalize(focus - loc);

    // find displacement from point where mouse was pressed
    float dx = x - oldMouseX;
    float dy = y - oldMouseY;

    float xrad = -5e-3 * dx;
    float yrad = -5e-3 * dy;

    // GLUT_LEFT_BUTTON = 0
    // GLUT_RIGHT_BUTTON = 2
    // shift + left = 3
    if (mb == 0) 
    {
        // vertical rotation
        glm::vec3 w = glm::normalize(glm::vec3(loc-focus));
        glm::vec3 v = glm::normalize(glm::vec3(up));
        glm::vec3 u = glm::cross(v, w);
        glm::mat4 R_v = Transform::rotate(u, yrad);

        // horizontal rotation
        glm::mat4 R_h = Transform::rotate(glm::vec3(0.0, 0.0, 1.0), xrad);

        // compose two rotations and rotate location and up vectors
        glm::mat4 R = R_h*R_v;
        loc = focus + R*(loc-focus);
        up = R*up;
    }
    else if (mb == 2)
    {
        // amount of scaling is relative to distance from stored point
        // zoom in if mouse moved upwards, zoom out if mouse moved downwards
        float zoomfactor = 0.005*sqrt(pow(dx, 2) + pow(dy, 2));

        if (dy > 0)
        {
            loc += -(loc-focus)*zoomfactor;
        }
        if (dy < 0)
        {
            loc += (loc-focus)*zoomfactor;
        }
    }
    else if (mb == 3)
    {
        // figure out unit vectors towards right and up
        glm::vec3 up3 = glm::normalize(glm::vec3(up));
        glm::vec3 right = glm::normalize(glm::cross(glm::vec3(focus-loc), up3));

        dx *= -0.01;
        dy *= 0.01;
        
        // scale right and up vectors by mouse displacement in proper direction
        glm::vec3 T3 = dx*right + dy*up3;
        focus += glm::vec4(T3, 0.0);
        loc += glm::vec4(T3, 0.0);
    }

    update();
}

void Camera::rot_fps(int x, int y)
{
    int dx = x - oldMouseX;
    int dy = y - oldMouseY;

    float xrad = -1e-2 * dx;
    float yrad = 1e-2 * dy;

    // vertical rotation
    glm::vec3 w = glm::normalize(glm::vec3(dir.x, dir.y, dir.z));
    glm::vec3 v = glm::normalize(glm::vec3(up.x, up.y, up.z));
    glm::vec3 u = glm::cross(v, w);
    glm::mat4 R_v = Transform::rotate(glm::vec3(u.x, u.y, u.z), yrad);

    // horizontal rotation
    glm::mat4 R_h = Transform::rotate(glm::vec3(0.0, 0.0, 1.0), xrad);

    glm::mat4 R = R_h*R_v;
    dir = R*dir;
    up = R*up;

    update();
}

void Camera::update()
{      
    // calculate new focus before (for FPS movement only)
    if (mode == CAM_FPS)
    {
        focus = loc + dir;
    }

    // reload projection and modelview matrices after changes in
    // camera positioning
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)screenWidth/(float)screenHeight,
            near, far);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // the proper target (centerx, centery, centerz)
    // depend on camera mode
    if (mode == CAM_ORBIT)
    {
        gluLookAt(loc.x, loc.y, loc.z,
                focus.x, focus.y, focus.z,
                up.x, up.y, up.z);
    }
    else if (mode == CAM_FPS)
    {
        gluLookAt(loc.x, loc.y, loc.z,
                loc.x+dir.x, loc.y+dir.y, loc.z+dir.z,
                up.x, up.y, up.z);
    }
}

void Camera::storeMouseLoc(int x, int y, int button)
{
    this->oldMouseX = x;
    this->oldMouseY = y;
    this->mb = button;
}

void Camera::storeScreenSize(int w, int h)
{
    screenWidth = w;
    screenHeight = h;
}

void Camera::toggleMode()
{
    // set focus accordingly
    focus = loc + dir;

    if (mode == CAM_ORBIT)
    {
        cout << "Camera mode: FPS" << endl;
        mode = CAM_FPS;
    }
    else
    {
        cout << "Camera mode: Orbit" << endl;
        mode = CAM_ORBIT;

        focus = loc + dir;

        // make sure that up vector points upwards
        glm::vec3 z = glm::vec3(0.0, 0.0, 1.0);
        glm::vec3 w = glm::normalize(glm::vec3(focus-loc));
        glm::vec3 u = glm::normalize(glm::cross(z, w));

        glm::vec3 up3 = glm::cross(w, u);
        up = glm::vec4(up3.x, up3.y, up3.z, 0.0);

        // if loc is along Z axis, the result will be zero vector.
        // In this case, set up to -X (-1.0, 0.0, 0.0, 0.0) 
        if(glm::length(up3) <= 0.01)
        {
            up = glm::vec4(-1.0, 0.0, 0.0, 0.0);
        }
    }
    update();
    
}

int Camera::getMode()
{
    return mode;
}

void Camera::mov_forward(float amount)
{
    loc += glm::normalize(dir)*amount*speed;
    update();
}

void Camera::mov_upward(float amount)
{
    loc += glm::vec4(0.0, 0.0, 1.0, 0.0)*amount*speed;
    update();
}

void Camera::mov_sideways(float amount)
{
    // find sideways vector
    glm::vec3 z = glm::vec3(0.0, 0.0, 1.0);
    glm::vec3 w = glm::vec3(loc-focus);
    glm::vec3 right3 = glm::normalize(glm::cross(z, w));
    glm::vec4 right4 = glm::vec4(right3.x, right3.y, right3.z, 0.0);

    loc += right4*amount*speed;
    update();
}


void Camera::changeSpeed(float amount)
{
    speed += amount;
    if (speed <= 0.1)
    {
        speed = 0.1;
    }
    cout << "Camera speed changed to " << speed << endl;
}

int Camera::getMouseButton()
{
    return mb;
}
