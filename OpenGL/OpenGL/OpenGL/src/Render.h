#pragma once

#include <GL/glew.h>

// Debug - glGetError()
#define ASSERT(x) if ((!x)) __debugbreak();

#ifdef _DEBUG
    #define GLCall(x) GLClearError();\
            x;\
            ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
    #define GLCall(x) x;
#endif // DEBUG

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);
