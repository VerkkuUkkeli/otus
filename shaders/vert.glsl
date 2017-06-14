#version 120

//in vec4 gl_Vertex;
//in vec4 gl_Normal;
//out vec4 vertex;
//out vec4 normal;
varying vec4 vertex;
varying vec4 normal;
varying vec4 lightpos;
varying vec4 colour;

void main()
{
    lightpos = gl_ModelViewMatrix * vec4(0.0, 0.0, 5.0, 1.0);
    vertex = gl_ModelViewMatrix * gl_Vertex;
    normal = gl_ModelViewMatrixInverseTranspose * vec4(gl_Normal, 0.0);
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
    colour = gl_Color;
}
