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
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "helpers.hpp"
#include "Camera.hpp"
#include "Particle.hpp"
#include "ODE.hpp"
#include "display.hpp"
#include "callbacks.hpp"
#include "shader.hpp"

#include "globals.hpp"

using namespace std;



int main(int argc, char* argv[])
{
    srand(time(NULL));

    // Initialisation
    glutInit(&argc, argv);

    glutInitWindowPosition(1920/8, 1080/8);
    glutInitWindowSize(1920/2, 1080/2);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Otus");

    glewInit();
    glClearColor(0.259, 0.525, 0.957, 1.0);
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // init particles
    // vector<Particle> particles defined in globals.hpp
    /*
    float inc = 4.0f;
    for (float x = -5.0f; x <= 5.0f; x+=inc)
    {
        for (float y = -5.0f; y <= 5.0f; y+=inc)
        {
            for (float z = -1.0f; z <= 1.0f; z+=inc)
            {
                if (pow(x,2) + pow(y,2) < pow(5.0f, 2))
                {
                    particles.push_back(new Particle(0.5f + randf(2),
                                vec3(x+randf(0.2f)-0.1f, y+randf(0.2f)-0.1f, z+randf(0.2f)-0.1f),
                            circleV0(x+randf(2)-1, y+randf(2)-1, z+randf(2)-1)));
                }
            }
        }
    }
    */

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
