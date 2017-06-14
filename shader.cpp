#include "shader.hpp"

// read text file into string
string readTextFile(const char * filename)
{
    string line, returnstring;
    // open file for reading
    ifstream in;
    in.open(filename);
    if (in.is_open())
    {
        // read first line of file
        getline(in, line);
        while (in)
        {
            // read rest of the file line by line to returstring
            returnstring += line + "\n";
            getline(in, line);
        }
        return returnstring;
    }
    else
    {
        cerr << "Unable to open file " << filename << endl;
        exit(-1);
    }
}

// print out errors in shader program
void programErrors(const GLint program)
{
    GLint length;   // error log length
    GLchar* log;    // string for error log
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
    log = new GLchar[length+1];
    glGetProgramInfoLog(program, length, &length, log);
    cout << "Compile error:\n" << log << endl;
    delete [] log;
}

// print out errors in shader
void shaderErrors(const GLint shader)
{
    GLint length;   // error log length
    GLchar* log;    // error log
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    log = new GLchar[length+1];
    glGetShaderInfoLog(shader, length, &length, log);
    cout << "Compile error:\n" << log << endl;
    delete [] log;
}

GLuint compileShader(GLenum type, const char * filename)
{
    GLuint shader = glCreateShader(type);

    // read shader source
    string source = readTextFile(filename);
    GLchar* cstr = new GLchar[source.size()+1];
    const GLchar* p_cstr = cstr; // const pointer to cstr
    strcpy(cstr, source.c_str());

    // compile
    glShaderSource(shader, 1, &p_cstr, NULL);
    glCompileShader(shader);

    // check for compile errors
    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        shaderErrors(shader);
    }
    return shader;
}

GLuint initProgram(GLuint vertexshader, GLuint fragmentshader)
{
    GLuint program = glCreateProgram();
    GLint linked;
    glAttachShader(program, vertexshader);
    glAttachShader(program, fragmentshader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked)
    {
        glUseProgram(program);
    }
    else
    {
        programErrors(program);
    }
    return program;
}
