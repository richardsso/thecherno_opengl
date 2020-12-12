#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

/**
 * Compile the shader into 1 program.
 */
static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if ( result == GL_FALSE )
    {
        // get error message
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

/**
 * Link vertexShader and fragmentShader into a shader program.
 * Return a unique identifier of the shader back.
 */
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    // create a shader program
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    // Delete shaders because it has been linked into the program
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    /* init GLFW and GLEW */
    /* Create vertex, link bind buffer and enable vertex attrib pointer */

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    while (!glfwWindowShouldClose(window))
    {
        /* Rendering */
    }

    glDeleteProgram(shader);
    glfwTerminate();

    return 0;
}