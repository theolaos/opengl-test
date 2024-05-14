#include "glerror.hpp"
#include "logger.hpp" 
#include "colortxt.hpp"
#include "glad/glad.h"
#include <iostream>


// #define ASSERT(x) if (!(x))
// using assert alone seems better tbh

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

#define EXIT_ON_GL_ERROR
void GLCheckErrorMacro(const char* function, const char *file, int line)
{
    GLenum error = 0;
    bool is_error = false;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        is_error = true;
        switch (error)
        {
        case GL_INVALID_ENUM: printf("GL_INVALID_ENUM");
            break;
        case GL_INVALID_VALUE: printf("GL_INVALID_VALUE");
            break;
        case GL_INVALID_OPERATION: printf("INVALID_OPERATION");
            break;
        case GL_STACK_OVERFLOW: printf("STACK_OVERFLOW");
            break;
        case GL_STACK_UNDERFLOW: printf("STACK_UNDERFLOW");
            break;
        case GL_OUT_OF_MEMORY: printf("OUT_OF_MEMORY");
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: printf("INVALID_FRAMEBUFFER_OPERATION");
            break;
        case GL_CONTEXT_LOST: printf("GL_CONTEXT_LOST");
            break;

        default:
            printf("Unknown error code %d", error);
        }
        printf(" encountered at function '%s' (%s:%d)\n", function, file, line);
    }
#ifdef EXIT_ON_GL_ERROR
    if (is_error) {
        exit(1);
    }
#endif
}