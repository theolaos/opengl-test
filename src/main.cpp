/*
Following the book of how to learn OpenGL
*/

#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window, int *p_x, int *p_y)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        *p_y -= 10;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        *p_y += 10;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        *p_x -= 10;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        *p_x += 10;
    }

    //Collision for the window

    if (*p_x < 0){
        *p_x = 0;
    }
    if (*p_x > 1920-800)
    {
        *p_x = 1920-800;
    }
    
    if (*p_y < 0 ){
        *p_y = 0;
    }
    if (*p_y > 1080-600)
    {
        *p_y = 1080-600;
    }
    
}


int main()
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

    int x = 0;
    int y = 0;


    x = 1920/2-800/2;
    y = 1080/2-600/2;

    int *p_x = &x;
    int *p_y = &y;



    // while loop of the game
    while(!glfwWindowShouldClose(window)) {

        processInput(window, p_x, p_y);

        glfwSetWindowPos(window,x,y);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}