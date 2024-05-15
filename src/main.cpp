/*
Following the book of how to learn OpenGL
*/

// FF means Fun Fact

#include "readfile.hpp"
#include "logger.hpp"
#include "glerror.hpp" 


#include "glad/glad.h" //relative path
#include <GLFW/glfw3.h> // general computer path
#include <iostream>


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
    // synchronize with your monitor
    glfwSwapInterval(1);

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

    glGenVertexArrays(1, &VAO);                             GCE

    // It stores the id to the VBO variable
    glGenBuffers(1, &VBO);                                  GCE

    glBindVertexArray(VAO);                                 GCE

    // debunking some stuff
    // std::cout << VBO << std::endl;
    // std::cout << &VBO << std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, VBO);                     GCE

    /*
    Quoting from the book:
    • GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    • GL_STATIC_DRAW: the data is set only once and used many times.
    • GL_DYNAMIC_DRAW: the data is changed a lot and used many times
    */

    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW);    GCE


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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);     GCE 
    // from what I know: (void*)0 == NULL

    glEnableVertexAttribArray(0);                           GCE

    unsigned int ibo; // index buffer object    
    glGenBuffers(1, &ibo);                                  GCE
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);             GCE
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);   GCE


    glUseProgram(shaderProgram);                            GCE

    int location = glGetUniformLocation(shaderProgram, "u_Color"); GCE
    if (location == -1) {logger.customLog(LogLevel::ERR, "Could not find the uniform location");}    
    glUniform4f(location, 1.0f, 0.5f, 0.2f, 1.0f);                                          GCE


    // draw the triangle
    // we tell OpenGL that it needs to use this program object.
    // OpenGL will use this program object everytime there is a shader or rendercall.
    glBindVertexArray(VAO);                             GCE

    float r(0.0f),g(0.0f),b(0.0f);
    float incr = 0.01f;

    // while loop of the game
    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        // clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);               GCE
        glClear(GL_COLOR_BUFFER_BIT);                       GCE


        glUniform4f(location, r, 0.5f, 0.2f, 1.0f);                                          GCE

        if (r > 1.0f)
            incr = -incr;
        else if (r < 0.0f)
            incr = -incr;

        r += incr;

        // glDrawArrays(GL_TRIANGLES, 0, 4); 
         
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);   GCE
        

        //glfwSetWindowPos(window,x,y);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);                          GCE
    glDeleteBuffers(1, &VBO);                               GCE
    glDeleteProgram(shaderProgram);                         GCE
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
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);     GCE

    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);     GCE

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
    glGetProgramiv(program, GL_LINK_STATUS, &success);      GCE

    if(!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);   GCE

        logger.customLog(LogLevel::ERR, "PROGRAM LINKING FAILED");
    } else {
        logger.customLog(LogLevel::INFO, "PROGRAM LINKING SUCCEED");
    }
}


unsigned int compileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);                 GCE
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, NULL);                      GCE
    glCompileShader(id);                                    GCE

    shaderCompileInfo(id, (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"));  GCE

    return id;
} 


unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();               GCE

    unsigned int vs, fs; // vs = Vertex shader, fs = fragment shader

    vs = compileShader(GL_VERTEX_SHADER, vertexShader);     GCE
    fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader); GCE

    glAttachShader(program, vs);                            GCE
    glAttachShader(program, fs);                            GCE
    glLinkProgram(program);                                 GCE

    shaderProgramInfo(program);

    glDeleteShader(vs);                                     GCE
    glDeleteShader(fs);                                     GCE

    return program;
}
