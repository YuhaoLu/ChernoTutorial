#include <iostream>

#include "Render.h"

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[GL ERROR]: 0x0" << std::hex << error << std::dec << std::endl;
		std::cout << "            " << function << std::endl;
		std::cout << "            " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}