#include <glm/glm.hpp>
#include <math.h>
#include <iomanip>

glm::mat4 rotate(glm::vec3 axis, float rad);
void rot_h(float rad);
void rot_v(float rad);
void printMatrix(glm::mat4 M);
void printMatrix(glm::mat3 M);
void printMatrix(glm::mat2 M);
void help();
