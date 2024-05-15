/*
Following the book of how to learn OpenGL
*/

// FF means Fun Fact
#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>


#include "readfile.hpp"
#include "logger.hpp"
#include "glerror.hpp" 


void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void shaderCompileInfo(unsigned int &shader, std::string shader_type);
void shaderProgramInfo(unsigned int &program);
unsigned int compileShader(unsigned int type, const std::string &source);
unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader);



const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// in variables are basically the vertex attributes, so aPos is a vertex attribute
std::string vertexShaderSource = parseFile(std::string(SHADERS_PATH) + "triangle_shaders/triangle.vert");
std::string fragmentShaderSource = parseFile(std::string(SHADERS_PATH) + "triangle_shaders/triangle.frag");

Logger logger;

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


    // SHADERS ACTION 
    unsigned int shaderProgram = createShader(vertexShaderSource, fragmentShaderSource);


    float vertices[12] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    // it has to be unsigned
    unsigned int indices[6] = {
        0,1,2,
        2,3,0
    };


    // Generating a VBO and a VAO
    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);

    // It stores the id to the VBO variable
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    // debunking some stuff
    // std::cout << VBO << std::endl;
    // std::cout << &VBO << std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    /*
    Quoting from the book:
    • GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    • GL_STATIC_DRAW: the data is set only once and used many times.
    • GL_DYNAMIC_DRAW: the data is changed a lot and used many times
    */

    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW);


    /* parameters
    1. which vertex attribute we want to configure
        This parameter specifies the index of the vertex attribute. 
        In OpenGL, vertex attributes are referenced by their index, which corresponds 
        to the layout location specified in the vertex shader. This index is 
        used to bind vertex data to a particular attribute in the shader program. - ChatGPT
    2. the size of the vertex attribute
    3. the type of the vertex attribute
    4. normalization of data
    5. the stride, the space between consecutive vertex attributes
    6. the starting offset
    */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0); // from what I know: (void*)0 == NULL

    glEnableVertexAttribArray(0);

    unsigned int ibo; // index buffer object
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);



    // while loop of the game
    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        // clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw the triangle
        // we tell OpenGL that it needs to use this program object.
        // OpenGL will use this program object everytime there is a shader or rendercall.
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 4); 
         
        glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr); GCE
        

        //glfwSetWindowPos(window,x,y);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}


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


void shaderCompileInfo(unsigned int &shader, const std::string shader_type)
{
    // Error logging in case there is an error in the shader compilation
    int success;
    char infoLog[512]; //FF: it holds 512 bytes in memory
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);

        logger.customLog(LogLevel::ERR, "SHADER ", shader_type, " COMPILATION FAILED\n", infoLog);
    } else {
        logger.customLog(LogLevel::INFO, "SHADER ", shader_type," COMPILATION SUCCEED" );
    }
}


void shaderProgramInfo(unsigned int &program)
{
    // Error logging in case there is an error in the shader compilation
    int success;
    char infoLog[512]; //FF: it holds 512 bytes in memory
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);

        logger.customLog(LogLevel::ERR, "PROGRAM LINKING FAILED");
    } else {
        logger.customLog(LogLevel::INFO, "PROGRAM LINKING SUCCEED");
    }
}


unsigned int compileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    shaderCompileInfo(id, (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"));

    return id;
} 


unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();

    unsigned int vs, fs; // vs = Vertex shader, fs = fragment shader

    vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    shaderProgramInfo(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
