/*
I followed a video on youtube on how to setup glfw and glad. This was the setup.
*/

#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>


int main(int argc, char *argv[]){
    GLFWwindow* window;

    if(!glfwInit()){
        return -1;
    }

    window = glfwCreateWindow(640,480, "Window!", NULL, NULL);
    glfwMakeContextCurrent(window);
    //char[10] hello = "Hello World";
    std::cout << "Hello World" << std::endl;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Couldn't load opengl" << std::endl;
        glfwTerminate();
        return -1;
    }
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}