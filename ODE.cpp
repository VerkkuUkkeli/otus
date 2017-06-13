#include "ODE.hpp"

/*
// solve a vector of differential equations
//vector<float> EulerMethod(vector<float> y0, float t0, float t_end,
        float dt, dydt_func dydt)
{
    vector<float> y_end;

    // verify that t0 < t_end
    if (t0 >= t_end)
    {
        throw "Bad arguments for t0 and t_end. Make sure that t0 < t_end.";
    }
    if (dt <=0)
    {
        throw "Bad argument for dt: Make sure that dt > 0.";
    }


    // solve ODE using Euler's method for all elements in y0
    // y_0i is the ith element of vector y0
    for (float y_0i : y0)
    {
        // initialise variables
        float t = t0;
        float y = y_0i;

        while (t < t_end)
        {
            // step
            y += dydt(t, y)*dt;
            t += dt;
        }
        y_end.push_back(y);
    }

    return y_end;
}
*/

/*
// solve scalar differential equation
float EulerMethod(float y0, float t0, float t_end,
        float dt, dydt_func dydt)
{
    // verify that t0 < t_end
    if (t0 >= t_end)
    {
        throw "Bad arguments for t0 and t_end. Make sure that t0 < t_end.";
    }

    if (dt <=0)
    {
        throw "Bad argument for dt: Make sure that dt > 0.";
    }

    // solve ODE using Euler's method
    float t = t0;
    float y = y0;

    while (t < t_end)
    {
        // step
        y += dydt(t, y)*dt;
        t += dt;
    }

    return y;
}
*/

// solve 3x3 matrix differential equation
mat3 EulerMethod(mat3 M0, float t0, float t_end, float dt,
        mat3 dMdt)
{
    // verify that t0 < t_end
    if (t0 >= t_end)
    {
        throw "Bad arguments for t0 and t_end. Make sure that t0 < t_end.";
    }
    if (dt <=0)
    {
        throw "Bad argument for dt: Make sure that dt > 0.";
    }

    float t = t0;
    mat3 M = M0;

    while (t < t_end)
    {
        M += dMdt*dt;
        t += dt;
    }
    return M;
}

// solve vec3 differential equation
vec3 EulerMethod(vec3 V0, float t0, float t_end, float dt,
        vec3 dV3dt)
{
    // verify that t0 < t_end
    if (t0 >= t_end)
    {
        throw "Bad arguments for t0 and t_end. Make sure that t0 < t_end.";
    }
    if (dt <=0)
    {
        throw "Bad argument for dt: Make sure that dt > 0.";
    }

    float t = t0;
    vec3 V = V0;

    while (t < t_end)
    {
        V += dV3dt*dt;
        t += dt;
    }
    return V;
}
