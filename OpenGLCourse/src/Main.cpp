#include "Device.hpp"

#if defined(_WIN64)
#pragma comment(lib, "freeglut64.lib")
#elif defined(_WIN32)
#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#endif

using namespace OpenGL;

int main(int ac, char* av[])
{
	Device*	device = new Device();

	device->Run(ac, av);

	delete device;

	return 0;
}