#include "helpers.hpp"
#include <iostream>

using namespace std;

glm::mat4 rotate (glm::vec3 axis, float rad)
{
    // normalise axis
    axis = glm::normalize(axis);

    // declare relevant matrices
    glm::mat3 I = glm::mat3(1.0);
    glm::mat3 A_dual = glm::mat3(0, axis.z, -axis.y, -axis.z, 0, axis.x, axis.y, -axis.x, 0);

    glm::mat3 R3 = I*cosf(rad) + glm::outerProduct(axis, axis)*(1-cosf(rad)) + A_dual*sinf(rad);
    glm::mat4 R4 = glm::mat4(
            R3[0].x, R3[0].y, R3[0].z, 0.0,
            R3[1].x, R3[1].y, R3[1].z, 0.0,
            R3[2].x, R3[2].y, R3[2].z, 0.0,
            0.0, 0.0, 0.0, 1.0);

    return R4;
}

void printMatrix(glm::mat4 M)
{
    cout.precision(2);
    cout << "[" << setw(8) << M[0].x << setw(8) << M[0].y << setw(8)
        << M[0].z << setw(8) << M[0].w << "]" << endl;
    cout << "[" << setw(8) << M[1].x << setw(8) << M[1].y << setw(8)
        << M[1].z << setw(8) << M[1].w << "]" << endl;
    cout << "[" << setw(8) << M[2].x << setw(8) << M[2].y << setw(8)
        << M[2].z << setw(8) << M[2].w << "]" << endl;
    cout << "[" << setw(8) << M[3].x << setw(8) << M[3].y << setw(8)
        << M[3].z << setw(8) << M[3].w << "]" << endl;
}

void printMatrix(glm::mat3 M)
{
    cout.precision(2);
    cout << "[" << setw(8) << M[0].x << setw(8) << M[0].y << setw(8)
        << M[0].z << "]" << endl;
    cout << "[" << setw(8) << M[1].x << setw(8) << M[1].y << setw(8)
        << M[1].z << "]" << endl;
    cout << "[" << setw(8) << M[2].x << setw(8) << M[2].y << setw(8)
        << M[2].z << "]" << endl;
}

void printMatrix(glm::mat2 M)
{
    cout.precision(2);
    cout << "[" << setw(8) << M[0].x << setw(8) << M[0].y << "]" << endl;
    cout << "[" << setw(8) << M[1].x << setw(8) << M[1].y << "]" << endl;
}

void help()
{
    cout << "\nWelcome to otus™ Visualisation Centre.\n\n";
    cout << setw(24) << "CONTROLS" << "\n";

    cout << "General:" << endl;
    cout << setw(8) << "ESC" << " - Exit program" << "\n\n";

    cout << "Navigation:" << endl;
    cout << setw(8) << "c" << " - Toggle camera mode" << endl;
    cout << setw(8) << "w" << " - Move forward"
        << "   (FPS)" << endl;
    cout << setw(8) << "a" << " - Move left"
        << "      (FPS)" << endl;
    cout << setw(8) << "s" << " - Move back"
        << "      (FPS)" << endl;
    cout << setw(8) << "d" << " - Move right"
        << "     (FPS)" << endl;
    cout << setw(8) << "e" << " - Move up"
        << "        (FPS)" << endl;
    cout << setw(8) << "q" << " - Move down"
        << "      (FPS)" << endl;
    cout << setw(8) << "+" << " - Increase speed"
        << " (FPS)" << endl;
    cout << setw(8) << "-" << " - Decrease speed"
        << " (FPS)" << endl;
}
