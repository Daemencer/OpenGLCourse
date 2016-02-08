#include <cstdio>
#include <string>
#include <iostream>

#include "glew.h"
#define FREEGLUT_LIB_PRAGMAS 0
#include "Freeglut.h"

//#include "GLShader.hpp"

#if defined(_WIN64)
#pragma comment(lib, "freeglut64.lib")
#elif defined(_WIN32)
#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"

int main(int argc, char* argv[])
{
	return 0;
}