#include "glerror.hpp"
#include "logger.hpp" 
#include "colortxt.hpp"
#include "glad/glad.h"
#include <iostream>

// 
static const std::string ERROR_TEXT = colorText("[ERROR]", color::red, true);
static const std::string OPENGL_TEXT = colorText("[OPENGL]", color::yellow, true);


void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}


bool GLCheckError(Logger &logger)
{
    while ( GLenum error = glGetError() ){
        logger.customLog(LogLevel::ERR, OPENGL_TEXT, 
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
            std::cout << ERROR_TEXT << " " << OPENGL_TEXT   << " GL_INVALID_ENUM" << std::endl;
            break;
        case GL_INVALID_VALUE:
            std::cout << ERROR_TEXT << " " << OPENGL_TEXT    << " GL_INVALID_VALUE" << std::endl;
            break;
        case GL_INVALID_OPERATION:
            std::cout << ERROR_TEXT << " " << OPENGL_TEXT   << " INVALID_OPERATION" << std::endl;
            break;
        case GL_STACK_OVERFLOW:
            std::cout << ERROR_TEXT << " " << OPENGL_TEXT   << " STACK_OVERFLOW" << std::endl;
            break;
        case GL_STACK_UNDERFLOW: 
            std::cout << ERROR_TEXT << " " << OPENGL_TEXT   << " STACK_UNDERFLOW" << std::endl;
            break;
        case GL_OUT_OF_MEMORY:
            std::cout << ERROR_TEXT << " " << OPENGL_TEXT   << " OUT_OF_MEMORY" << std::endl;
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            std::cout << ERROR_TEXT << " " << OPENGL_TEXT   << " INVALID_FRAMEBUFFER_OPERATION" << std::endl;
            break;
        case GL_CONTEXT_LOST:
            std::cout << ERROR_TEXT << " " << OPENGL_TEXT   << " GL_CONTEXT_LOST" << std::endl;
            break;

        default:
            std::cout << ERROR_TEXT << " " << OPENGL_TEXT   << "Unknown error code: " << error << std::endl;
        }
        printf("Encountered at function '%s' (%s:%d)\n", function, file, line);
    }
#ifdef EXIT_ON_GL_ERROR
    if (is_error) {
        exit(1);
    }
#endif
}