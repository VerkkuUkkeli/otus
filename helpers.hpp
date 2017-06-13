#include <glm/glm.hpp>
#include <math.h>
#include <iomanip>

void rot_h(float rad);
void rot_v(float rad);
void printMatrix(glm::mat4 M);
void printMatrix(glm::mat3 M);
void printMatrix(glm::mat2 M);
void help();
glm::mat3 dual(glm::vec3 v);
