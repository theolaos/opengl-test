/*
Following the book of how to learn OpenGL
*/

// FF means Fun Fact

#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "colortxt.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void shaderCompileInfo(unsigned int &shader, const char *shader_type);
void shaderProgramInfo(unsigned int &program);


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// in variables are basically the vertex attributes, so aPos is a vertex attribute
const char *vertexShaderSource = "#version 460 core\n"
                                 "layout (location = 0) in vec3 aPos;\n" 
                                 "void main()\n"
                                 "{\n"
                                 "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 460 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";


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
    unsigned int vertexShader;
    // We are passing the GL_VERTEX_SHADER because that's the shader we want to create now
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // we attach the vertex source to the vertex object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compiling the attached source in vertex object
    glCompileShader(vertexShader);

    // getting the compile info from the vertex shader
    shaderCompileInfo(vertexShader, "VERTEX");
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // attaching the source to the fragment object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // compiling the attached source in the fragment object
    glCompileShader(fragmentShader);

    // getting the compile info from the fragment shader
    shaderCompileInfo(fragmentShader, "FRAGMENT");

    // Creating a program to link the compiled shaders

    unsigned int shaderProgram;
    // glCreateProgram returns the ID to the newly created Program
    shaderProgram = glCreateProgram();
    
    // we ater attach the shaders to the ID given
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // checking for errors in the linking proccess
    shaderProgramInfo(shaderProgram);

    // deleting the compiled shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);



    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
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

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


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
        glDrawArrays(GL_TRIANGLES, 0, 3); 

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


void shaderCompileInfo(unsigned int &shader, const char *shader_type)
{
    // Error logging in case there is an error in the shader compilation
    int success;
    char infoLog[512]; //FF: it holds 512 bytes in memory
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        coloredText("ERROR",red);
        std::cout << "::SHADER::"<< shader_type << "::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
    } else {
        coloredText("SUCCESS",green);
        std::cout << "::SHADER::"<< shader_type << "::COMILATION_SUCCEED\n" << std::endl;
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
        coloredText("ERROR", red);
        std::cout << "::PROGRAM::LINKING_ERROR\n" << 
            infoLog << std::endl;
    } else {
        coloredText("SUCCESS", green);
        std::cout << "::PROGRAM::LINKING_SUCCEED\n" << std::endl;
    }
}