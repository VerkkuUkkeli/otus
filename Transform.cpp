#include "Transform.hpp"

// Rotate vector about axis by an angle rad
glm::mat4 Transform::rotate(glm::vec3 axis, float rad)
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

// Treat the xyz component of vec3 amount as scale factors
mat4 Transform::scale(vec3 amount)
{
    return mat4(amount.x, 0, 0, 0,
                0, amount.y, 0, 0,
                0, 0, amount.z, 0,
                0, 0,        0, 1);
}

mat4 Transform::scale(float sx, float sy, float sz)
{
    return mat4(sx, 0,  0, 0,
                0, sy,  0, 0,
                0,  0, sz, 0, 
                0,  0,  0, 1);
}

mat4 Transform::translate(vec3 s)
{
    return mat4(1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                s.x, s.y, s.z, 1);
}

mat4 Transform::translate(float dx, float dy, float dz)
{
    return mat4(1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                dx, dy, dz, 1);
}
