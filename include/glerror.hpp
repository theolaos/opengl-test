#ifndef INCLUDE_GLERROR_HPP
#define INCLUDE_GLERROR_HPP

#include "logger.hpp"

void GLClearError();
bool GLCheckError(Logger &logger);

void GLCheckErrorMacro(const char* function, const char *file, int line);

#define CHECK_GL_ERRORS
#ifdef CHECK_GL_ERRORS
#define GCE GLCheckErrorMacro(__FUNCTION__, __FILE__, __LINE__);
#else
#define GCE
#endif

#endif /*INCLUDE_GLERROR_HPP*/