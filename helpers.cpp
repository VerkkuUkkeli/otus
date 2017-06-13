#include "helpers.hpp"
#include <iostream>

using namespace std;



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
    cout << endl;
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
    cout << endl;
}

void printMatrix(glm::mat2 M)
{
    cout.precision(2);
    cout << "[" << setw(8) << M[0].x << setw(8) << M[0].y << "]" << endl;
    cout << "[" << setw(8) << M[1].x << setw(8) << M[1].y << "]" << endl;
    cout << endl;
}

glm::mat3 dual(glm::vec3 v)
{
    return glm::mat3(
            0,     v.z, -v.y,
            -v.z,  0,    v.x,
            v.y,  -v.x,  0);
}

void help()
{
    cout << "\nWelcome to Otus Visualisation Centre.\n\n";
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
