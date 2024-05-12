#include <iostream>
#include "glerror.hpp" 
#include "glad/glad.h"


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