// find a file, copy all the content of that file and paste into this file
#include <iostream>

// Macros - usually used for debugging purpose
# define PR_DEBUG 1

#if PR_DEBUG == 1
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x)
#endif

// entry point
// #if 1
int main() {
	// std::cout << "Hello World!" << std::endl;
    LOG("Hello World!");
	std::cin.get();
}
// #endif