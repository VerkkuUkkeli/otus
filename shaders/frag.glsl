#version 120

//in vec4 vertex;
//in vec4 normal;
varying vec4 vertex;
varying vec4 normal;
varying vec4 lightpos;
varying vec4 colour;

void main()
{
    vec4 finalcolour = vec4(0.0f);

    bool enable = false;
    if (enable)
    {
        vec4 ambient = vec4(0.1, 0.1, 0.15, 1.0);
        vec4 emission = vec4(0.0);
        vec4 lightcol = vec4(1.0, 1.0, 1.0, 1.0);
        vec4 diffuse = colour;
        vec4 specular = vec4(0.5, 0.5, 0.5, 1.0);
        float shininess = 100;

        vec3 light3 = normalize(vec3(lightpos-vertex)); // point light
        //vec3 light3 = normalize(vec3(-lightpos)); // directional
        vec3 norm3 = normalize(vec3(normal));
        vec3 eye3 = normalize(vec3(-vertex));
        vec3 H = normalize(eye3 + light3);

        finalcolour += ambient + emission;

        finalcolour += lightcol*(diffuse*max(dot(norm3, light3), 0) + specular*pow(max(dot(norm3, H), 0), shininess));
    }
    else
    {
        finalcolour = colour;
    }

    gl_FragColor = finalcolour;
}

