#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "helpers.hpp"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <glm/glm.hpp>

class Camera
{
    private:
        int oldMouseX;
        int oldMouseY;
        int screenWidth;
        int screenHeight;
        float far;
        float near;
        float mode;
        float speed;

    public:
        // variables
        glm::vec4 loc;
        glm::vec4 focus;
        glm::vec4 up;
        glm::vec4 dir;
        enum {CAM_ORBIT, CAM_FPS};

        // functions
        Camera();
        void rot_h(float rad);
        void rot_v(float rad);
        void rot_mouse(int x, int y);
        void rot_fps(int x, int y);
        void update();
        void storeMouseLoc(int x, int y);
        void storeScreenSize(int w, int h);
        void toggleMode();
        int getMode();
        void mov_forward(float amount);
        void mov_upward(float amount);
        void mov_sideways(float amount);
        void changeSpeed(float amount);
};
#endif