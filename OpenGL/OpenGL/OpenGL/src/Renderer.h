#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

// Debug - glGetError()
#define ASSERT(x) if (!(x)) __debugbreak();

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

#ifdef _DEBUG
	#define GLCall(x) GLClearError();\
            x;\
            ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
	#define GLCall(x) x;
#endif // DEBUG

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shade) const;
	
private:

};
