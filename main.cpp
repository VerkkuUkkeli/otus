#include <GL/glew.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#ifdef __gnu_linux__
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "helpers.hpp"
#include "Camera.hpp"
#include "ODE.hpp"
#include "display.hpp"
#include "callbacks.hpp"
#include "shader.hpp"

#include "globals.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    // Initialisation
    glutInit(&argc, argv);

    glutInitWindowPosition(1920/8, 1080/8);
    glutInitWindowSize(1920/2, 1080/2);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Otus");

    glewInit();
    glClearColor(0.259, 0.525, 0.957, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLuint vertexshader = compileShader(GL_VERTEX_SHADER, "shaders/vert.glsl");
    GLuint fragmentshader = compileShader(GL_FRAGMENT_SHADER, "shaders/frag.glsl");
    shaderprogram = initProgram(vertexshader, fragmentshader);
    help();

    // callback functions
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutSpecialFunc(SpecialInput);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passiveMotion);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);

    glutMainLoop();
    return 0;
}
