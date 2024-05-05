/*
Following the book of how to learn OpenGL
*/

// FF means Fun Fact

#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


void shaderCompileInfo(unsigned int &shader){
    // Error logging in case there is an error in the shader compilation
    int success;
    char infoLog[512]; //FF: it holds 512 bytes in memory
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
    }
}

void shaderProgramInfo(unsigned int &program){
    // Error logging in case there is an error in the shader compilation
    int success;
    char infoLog[512]; //FF: it holds 512 bytes in memory
    glGetProgramiv(program, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
    }
}



int main(int argc, char *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    // We register the callback functions here, before the while loop, and after the window init
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    unsigned int VBO;

    // It stores the id to the VBO variable
    glGenBuffers(1, &VBO);

    // debunking some stuff
    std::cout << VBO << std::endl;
    std::cout << &VBO << std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    /*
    Quoting from the book:
    • GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    • GL_STATIC_DRAW: the data is set only once and used many times.
    • GL_DYNAMIC_DRAW: the data is changed a lot and used many times
    */

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const char *vertexShaderSource = "#version 460 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                                     "}\0";

    unsigned int vertexShader;
    // We are passing the GL_VERTEX_SHADER because that's the shader we want to create now
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // we attach the vertex source to the vertex object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compiling the attached source in vertex object
    glCompileShader(vertexShader);

    // getting the compile info from the vertex shader
    shaderCompileInfo(vertexShader);

    
    const char *fragmentShaderSource = "#version 460 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()"
                                       "{\n"
                                       "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\0";
    
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // attaching the source to the fragment object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // compiling the attached source in the fragment object
    glCompileShader(fragmentShader);

    // getting the compile info from the fragment shader
    shaderCompileInfo(fragmentShader);

    // Creating a program to link the compiled shaders

    unsigned int shaderProgram;
    // glCreateProgram returns the ID to the newly created Program
    shaderProgram = glCreateProgram();
    
    // we ater attach the shaders to the ID given
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // deleting the compiled shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // checking for errors in the linking proccess
    shaderProgramInfo(shaderProgram);


    glUseProgram(shaderProgram);


    // while loop of the game
    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        //glfwSetWindowPos(window,x,y);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}