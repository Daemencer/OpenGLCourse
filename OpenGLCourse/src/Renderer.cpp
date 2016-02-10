#include "Renderer.hpp"

#include <cstdio>
#include <string>

#include "glew.h"
#define FREEGLUT_LIB_PRAGMAS 0
#include "Freeglut.h"

#include "GLShader.hpp"

#include "Device.hpp" // singleton holding everything

namespace OpenGL {


Renderer::Renderer(int ac, char* av[])
{
	Initialize(ac, av);
}


Renderer::~Renderer()
{
	Shutdown();
}


auto	Renderer::Initialize(int ac, char* av[]) -> void
{
	glutInit(&ac, av);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL Renderer");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE
		, GLUT_ACTION_CONTINUE_EXECUTION);
	glutIdleFunc(Update);
	glutDisplayFunc(Render);
	glewInit();
}


auto	Renderer::Shutdown() -> void
{
}


auto	Renderer::Run() -> void
{
	glutMainLoop();
}


auto	Renderer::Update() -> void
{
	glutPostRedisplay();
}


auto	Renderer::Render() -> void
{
	//glEnable(GL_SCISSOR_TEST);
	//glScissor(0, 0, 640, 480);
	glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CW);
	/*glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/


	auto program = Device::GetInstance()->ShaderMgr->GetProgram("basic");
	glUseProgram(program);

	static float time = 0.0f;
	time += 1.0f / 60.0f;

	float scale = 200.f;

	float rotationMatrix[16] = {
		scale*cos(time),	scale*sin(time),			0.f,				0.f,
		scale*-sin(time),	scale*cos(time),			0.f,				0.f,
		0.f,				0.f,						1.f,				0.f,
		0.f,				0.f,						0.f,				1.f
	};

	float viewMatrix[16] = {
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		200.f, 0.f, -1.f, 1.f
	};

	float l = -400.f;
	float r = 400.f;
	float b = -300.f;
	float t = 300.f;
	float n = 1.f;
	float f = 10.f;

	float project[] = {
		(2.f*n) / (r - l), 0.f, (r + l) / (r - l), 0.f,
		0.f, (2.f*n) / (t - b), (t + b) / (t - b), 0.f,
		0.f, 0.f, -(f + n) / (f - n), (-2.f*f*n) / (f - n),
		0.f, 0.f, -1.f, 0.f
	};

	// soustraire la moitie de l'ecran puis diviser par la moitie de l'ecran

	auto matrixLocation1 = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(matrixLocation1, 1, GL_FALSE, rotationMatrix);

	auto matrixLocation3 = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(matrixLocation3, 1, GL_FALSE, viewMatrix);

	auto matrixLocation2 = glGetUniformLocation(program, "project");
	glUniformMatrix4fv(matrixLocation2, 1, GL_FALSE, project);

	std::cout << Device::GetInstance()->texId << std::endl;
	glBindTexture(GL_TEXTURE_2D, Device::GetInstance()->texId);

	// framebuffer drawing
	/*glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);*/

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw scene
	std::cout << Device::GetInstance()->model1->GetModelVAO() << std::endl;
	glBindVertexArray(Device::GetInstance()->model1->GetModelVAO());
	//printf("VAO: %d\n", Device::GetInstance()->model1->GetModelVAO());
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);

	// second pass, back to default framebuffer
	//glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	//glViewport(0, 0, 800, 600);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// now draw for real
	//glUseProgram(g_GrayscaleShader.GetProgram());
	//glBindVertexArray(GVAO);
	//glDisable(GL_DEPTH_TEST);
	//glBindTexture(GL_TEXTURE_2D, quadTextureId);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0); // everything to draw a quad
	//glBindVertexArray(0);

	glUseProgram(0);
	glutSwapBuffers();
}


} // OpenGL