#include "Renderer.hpp"

#include <cstdio>
#include <string>

#include "glew.h"
#define FREEGLUT_LIB_PRAGMAS 0
#include "Freeglut.h"

#include "GLShader.hpp"

#include "Device.hpp" // singleton holding everything
#include "Camera.hpp"

namespace OpenGL {


// will be given and set from the obj in the future but for now, that's it
struct Material {
	Vector3 Ke; // emissive color of the surface
	Vector3 Ka; // ambient color of the material
	Vector3 Kd; // diffuse color of the material
	Vector3 Ks; // specular color of the material
	float shininess;
};

struct Light {
	GLfloat la; // ambient light color
	Vector3 ld; // diffuse light color
	Vector3 ls; // specular light color
};


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
	Device::GetInstance()->Update();

	glutPostRedisplay();
}


auto	Renderer::Render() -> void
{
	//glEnable(GL_SCISSOR_TEST);
	//glScissor(0, 0, 640, 480);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, Device::GetInstance()->texId);

	Device::GetInstance()->Draw();

	// will be moved in the update of the concerned node
	/*static float time = 0.0f;
	time += 1.0f / 60.0f;*/

	//////////////////////////////////////////////////////////////////////////////
	//								model matrices								//
	//struct ModelMatrices {
	//	// translate matrix
	//	float translateMatrix[16] = {
	//		1.0f, 0.0f, 0.0f, 0.0f,
	//		0.0f, 1.0f, 0.0f, 0.0f,
	//		0.0f, 0.0f, 1.0f, 0.0f,
	//		0.0f, 0.0f, 0.0f, 1.0f
	//	};

	//	// x rotation
	//	/*float rotationMatrix[16] = {
	//		1.0f,				0.0f,						0.0f,				0.f,
	//		0.0f,				cos(time),					-sin(time),			0.f,
	//		0.0f,				sin(time),					cos(time),			0.f,
	//		0.f,				0.f,						0.f,				1.f
	//	};*/

	//	// y rotation
	//	float rotationMatrix[16] = {
	//		cos(time),			0.0f,						sin(time),			0.f,
	//		0.0f,				1.0f,						0.f,				0.f,
	//		-sin(time),			0.f,						cos(time),			0.f,
	//		0.f,				0.f,						0.f,				1.f
	//	};

	//	// scale matrix
	//	float scaleMatrix[16] = {
	//		1.0f, 0.0f, 0.0f, 0.0f,
	//		0.0f, 1.0f, 0.0f, 0.0f,
	//		0.0f, 0.0f, 1.0f, 0.0f,
	//		0.0f, 0.0f, 0.0f, 1.0f
	//	};
	//} modelMatrices;
	//////////////////////////////////////////////////////////////////////////////

	/*struct CameraMatrices {
		CameraMatrices() {
			float fov = 60.f;
			float aspect = 4.f / 3.f;
			float znear = 1.f;
			float zfar = 1000.f;

			Camera::GetPerspectiveMatrix(project, fov, aspect, znear, zfar);
		}

		float viewMatrix[16] = {
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			1.f, -4.f, -12.f, 1.f
		};

		float project[16];
	}cameraMatrices;*/

	/*auto matrixLocation1 = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(matrixLocation1, 1, GL_FALSE, rotationMatrix);*/

	/*auto matrixLocation3 = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(matrixLocation3, 1, GL_FALSE, viewMatrix);

	auto matrixLocation2 = glGetUniformLocation(program, "project");
	glUniformMatrix4fv(matrixLocation2, 1, GL_TRUE, project);*/


	/*GLuint modelUBO = 0u;
	glGenBuffers(1, &modelUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, modelUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(modelMatrices), &modelMatrices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, modelUBO);*/

	//GLuint camUBO = 0u;
	//glGenBuffers(1, &camUBO);
	//glBindBuffer(GL_UNIFORM_BUFFER, camUBO);
	//glBufferData(GL_UNIFORM_BUFFER, sizeof(cameraMatrices), &cameraMatrices, GL_DYNAMIC_DRAW);
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);

	//glBindBufferBase(GL_UNIFORM_BUFFER, 1, camUBO);

	//GLuint viewPosLoc = glGetUniformLocation(program, "viewPos");
	//glUniform3f(viewPosLoc, 0.0f, 0.0f, 1.0f);

	//////////////////////////////////////////////
	//				LIGHT TESTING				//

	/*GLfloat lightPosition[] = { 
		0.0f, 0.0f, 1.0f
	};

	// uniform buffer object

	auto lightPos = glGetUniformLocation(program, "u_directionalLight.position");
	glUniform3f(lightPos, lightPosition[0], lightPosition[1], lightPosition[2]);*/

	/*float la[] = {
		1.0f, 0.f, 0.f
	};

	auto lightAmbient = glGetUniformLocation(program, "u_directionalLight.la");
	glUniformMatrix4fv(lightAmbient, 1, GL_FALSE, la);*/

	//////////////////////////////////////////////

	// framebuffer drawing
	/*glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);*/

	

	// draw scene
	//std::cout << Device::GetInstance()->model1->GetModelVAO() << std::endl;
	//glBindVertexArray(Device::GetInstance()->model->GetModelVAO());
	//glBindVertexArray(Device::GetInstance()->cube->GetModelVAO());

	//printf("VAO: %d\n", Device::GetInstance()->model1->GetModelVAO());
	//glDrawElements(GL_TRIANGLES, Device::GetInstance()->model->GetModelIndexCount(), GL_UNSIGNED_SHORT, 0);
	//glDrawElements(GL_TRIANGLES, Device::GetInstance()->cube->GetModelIndexCount(), GL_UNSIGNED_SHORT, 0);
	//glBindVertexArray(0);

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