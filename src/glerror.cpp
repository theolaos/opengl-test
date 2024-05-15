#include "glerror.hpp"
#include "logger.hpp" 
#include "colortxt.hpp"
#include "glad/glad.h"
#include <iostream>


void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}


bool GLCheckError(Logger &logger)
{
    while ( GLenum error = glGetError() ){
        logger.customLog(LogLevel::ERR, colorText("[OPENGL]", color::yellow, true), 
            "Error occured: ", error);
        return false;
    }
    return true;
}

// comment out the definittion if dont want the program to exit on error.
// #define EXIT_ON_GL_ERROR
void GLCheckErrorMacro(const char* function, const char *file, int line)
{
    GLenum error = 0;
    bool is_error = false;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        is_error = true;
        switch (error)
        {
        case GL_INVALID_ENUM: 
            std::cout << colorText("[OPENGL] [ERROR]", color::yellow, true) << " GL_INVALID_ENUM" << std::endl;
            break;
        case GL_INVALID_VALUE:
            std::cout << colorText("[OPENGL] [ERROR]", color::yellow, true) << " GL_INVALID_VALUE" << std::endl;
            break;
        case GL_INVALID_OPERATION:
            std::cout << colorText("[OPENGL] [ERROR]", color::yellow, true) << " INVALID_OPERATION" << std::endl;
            break;
        case GL_STACK_OVERFLOW:
            std::cout << colorText("[OPENGL] [ERROR]", color::yellow, true) << " STACK_OVERFLOW" << std::endl;
            break;
        case GL_STACK_UNDERFLOW: 
            std::cout << colorText("[OPENGL] [ERROR]", color::yellow, true) << " STACK_UNDERFLOW" << std::endl;
            break;
        case GL_OUT_OF_MEMORY:
            std::cout << colorText("[OPENGL] [ERROR]", color::yellow, true) << " OUT_OF_MEMORY" << std::endl;
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            std::cout << colorText("[OPENGL] [ERROR]", color::yellow, true) << " INVALID_FRAMEBUFFER_OPERATION" << std::endl;
            break;
        case GL_CONTEXT_LOST:
            std::cout << colorText("[OPENGL] [ERROR]", color::yellow, true) << " GL_CONTEXT_LOST" << std::endl;
            break;

        default:
            std::cout << colorText("[OPENGL] [ERROR]", color::yellow, true) << "Unknown error code: " << error << std::endl;
        }
        printf("Encountered at function '%s' (%s:%d)\n", function, file, line);
    }
#ifdef EXIT_ON_GL_ERROR
    if (is_error) {
        exit(1);
    }
#endif
}