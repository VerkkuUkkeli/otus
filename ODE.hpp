#include <vector>

using namespace std;

typedef float (*dydt_func)(float t, float y);

vector<float> EulerMethod(vector<float> y0, float t0, float t_end,
        float dt, dydt_func dydt);
