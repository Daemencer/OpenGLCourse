#if defined(_WIN64)
#pragma comment(lib, "freeglut64.lib")
#elif defined(_WIN32)
#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#endif

#include "Renderer.hpp"

#include "mat4.hpp"

#include "ObjParser.hpp"


using namespace OpenGL;

int main(int ac, char* av[])
{
	///////////////////
	// testing phase //

	//mat4 m1 = {   1.0f, 1.0f, 2.0f, 1.0f
	//			, 1.0f, 1.0f, 1.0f, 2.0f
	//			, 1.0f, 2.0f, 1.0f, 1.0f 
	//			, 2.0f, 1.0f, 1.0f, 1.0f };
	//mat4 m2 = { 2.0f, 1.0f, 1.0f, 1.0f
	//			, 1.0f, 1.0f, 1.0f, 2.0f
	//			, 1.0f, 1.0f, 2.0f, 1.0f
	//			, 1.0f, 2.0f, 1.0f, 1.0f };

	//mat4 m3 = mat4::mult(m1, m2);

	//mat4::print(m3);

	//m3.Scale(3.0f, 3.0f, 3.0f);

	//mat4::print(m3);

	//m3.Rotate(45.0f, 45.0f, 45.0f);

	//mat4::print(m3);

	///////////////////

	//Mesh	mesh = ObjParser::ParseObj("resources/models/test.obj");

	Renderer*	renderer = new Renderer(ac, av);

	renderer->Run();

	delete renderer;

	return 0;
}