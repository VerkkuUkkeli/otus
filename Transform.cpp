#include "Transform.hpp"

// Rotate vector about axis by an angle rad
mat4 Transform::rotate(vec3 axis, float rad)
{
    // normalise axis
    axis = normalize(axis);

    // declare relevant matrices
    mat3 I = mat3(1.0);
    mat3 A_dual = mat3(0, axis.z, -axis.y, -axis.z, 0, axis.x, axis.y, -axis.x, 0);

    mat3 R3 = I*cosf(rad) + outerProduct(axis, axis)*(1-cosf(rad)) + A_dual*sinf(rad);
    mat4 R4 = mat4(
            R3[0].x, R3[0].y, R3[0].z, 0.0,
            R3[1].x, R3[1].y, R3[1].z, 0.0,
            R3[2].x, R3[2].y, R3[2].z, 0.0,
            0.0, 0.0, 0.0, 1.0);

    return R4;
}

mat4 Transform::rotate(mat3 R)
{
    return mat4(
            R[0].x, R[0].y, R[0].z, 0.0f,
            R[1].x, R[1].y, R[1].z, 0.0f,
            R[2].x, R[2].y, R[2].z, 0.0f,
            0.0f,     0.0f,   0.0f, 1.0f);
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
