#include "Device.hpp"

#include <cstdio>
#include <string>

#include "glew.h"
#define FREEGLUT_LIB_PRAGMAS 0
#include "Freeglut.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"

#include "GLShader.hpp"


Device::Device()
{
	_shaderMgr = new ShaderManager();
}


Device::~Device()
{
	delete _shaderMgr;
}


GLShader g_BasicShader;
GLShader g_GrayscaleShader;

GLuint VAO;
GLuint VBOpos;
GLuint VBOcolor;
GLuint VBOtexCoords;
GLuint IBO;

GLuint GVAO;
GLuint GVBOpos;
GLuint GVBOcolor;
GLuint GVBOtexCoords;
GLuint GIBO;

GLuint FBO;

GLuint texId;
GLuint quadTextureId;


GLuint CreateTexture(const std::string& name, bool forceAlpha)
{
	int w, h, depth;
	auto* data = stbi_load(name.c_str()
						   , &w, &h, &depth
						   , forceAlpha ? 4 : 3);

	if (data)
	{
		GLuint texId = 0;
		glGenTextures(1, &texId);
		glBindTexture(GL_TEXTURE_2D, texId);

		glTexImage2D(GL_TEXTURE_2D
					 , 0
					 , GL_RGBA8
					 , w
					 , h
					 , 0
					 , forceAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE
					 , data);

		// alternative to glTexImage2d
		glTexStorage2D(GL_TEXTURE_2D
					   , 1
					   , GL_RGBA8
					   , w
					   , h);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
		stbi_image_free(data);

		return texId;
	}

	return 0;
}


void CreateFramebuffer()
{
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// create a texture for the Framebuffer
	glGenTextures(1, &quadTextureId);
	glBindTexture(GL_TEXTURE_2D, quadTextureId);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//////////

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, quadTextureId, 0);

	// renderbuffer object generation
	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	//////////

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		printf("Yay, framebuffer works\n");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}


void GenerateQuadVAO()
{
	g_GrayscaleShader.LoadVertexShader("basicGrayscale.vs");
	g_GrayscaleShader.LoadFragmentShader("basicGrayscale.fs");
	g_GrayscaleShader.Create();

	static const float g_Positions[] = {
		-1.0f, 1.0f,	// s0
		-1.f, -1.0f,	// s1
		1.0f, -1.0f,	// s2
		1.0f, 1.0f		// s3

	};
	static const float g_Colors[] = {
		1.0f, 1.0f, 1.0f, 1.0f,	// s0
		1.0f, 1.0f, 1.0f, 1.0f,	// s1
		1.0f, 1.0f, 1.0f, 1.0f,	// s2
		1.0f, 1.0f, 1.0f, 1.0f	// s3
	};

	static const GLubyte g_TexCoords[] = {
		0, 1,	// s0
		0, 0,	// s1
		1, 0,	// s2
		1, 1	// s3
	};

	static const unsigned short g_Indices[] = {
		0, 1, 2,	// f0
		0, 2, 3		// f1
	};

	auto program = g_GrayscaleShader.GetProgram();
	glUseProgram(program);

	auto positionLoc = glGetAttribLocation(program, "a_position");
	auto colorLoc = glGetAttribLocation(program, "a_color");
	auto texcoordsLoc = glGetAttribLocation(program, "a_texcoords");

	glGenBuffers(1, &GVBOpos);
	glGenBuffers(1, &GVBOcolor);
	glGenBuffers(1, &GVBOtexCoords);
	glGenBuffers(1, &GIBO);

	// data
	glBindBuffer(GL_ARRAY_BUFFER, GVBOpos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 2, g_Positions, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, GVBOcolor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, g_Colors, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, GVBOtexCoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLubyte) * 4 * 2, g_TexCoords, GL_STATIC_DRAW);

	// indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 3 * 2, g_Indices, GL_STATIC_DRAW);

	// reset binding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// check if not already a vao from previous frames (precaution)
	if (glIsVertexArray(GVAO) == GL_TRUE)
		glDeleteVertexArrays(1, &GVAO);

	// generate and bind the VAO that is going to execute the commands
	glGenVertexArrays(1, &GVAO);
	glBindVertexArray(GVAO);

	// bind all the buffers to explain opengl how to use their data

	// explain openGL how to use the data
	glBindBuffer(GL_ARRAY_BUFFER, GVBOpos);
	glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, GVBOcolor);
	glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, GVBOtexCoords);
	glVertexAttribPointer(texcoordsLoc, 2, GL_UNSIGNED_BYTE, GL_FALSE, 2 * sizeof(GLubyte), 0);

	glEnableVertexAttribArray(positionLoc);
	glEnableVertexAttribArray(colorLoc);
	glEnableVertexAttribArray(texcoordsLoc);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GIBO);

	// reset the VAO binding
	glBindVertexArray(0);

	// unbind to be safe
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


auto	Device::Initialize() -> void
{
	printf("Version OpenGL : %s\n", glGetString(GL_VERSION));
	printf("Fabricant : %s\n", glGetString(GL_VENDOR));
	printf("Pilote : %s\n", glGetString(GL_RENDERER));
	printf("Version GLSL : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glewInit();

	_shaderMgr->AddNewProgram("basic", "basic.vs", "basic.fs");

	static const float g_Position[] = {
		// position		
		-0.5f, 0.5f,	// s0
		-0.5f, -0.5f,	// s1
		0.5f, -0.5f,	// s2
		0.5f, 0.5f		// s3
	};

	static const float g_Colors[] = {
		1.0f, 1.0f, 1.0f, 1.0f,	// s0
		1.0f, 1.0f, 1.0f, 1.0f,	// s1
		1.0f, 1.0f, 1.0f, 1.0f,	// s2
		1.0f, 1.0f, 1.0f, 1.0f	// s3
	};

	static const GLubyte g_TexCoords[] = {
		0, 1,	// s0
		0, 0,	// s1
		1, 0,	// s2
		1, 1	// s3
	};

	static const unsigned short g_Indices[] = {
		0, 1, 2,	// f0
		0, 2, 3		// f1
	};

	GLuint program = _shaderMgr->GetProgram("basic");
	glUseProgram(program);

	auto positionLoc = glGetAttribLocation(program, "a_position");
	auto colorLoc = glGetAttribLocation(program, "a_color");
	auto texcoordsLoc = glGetAttribLocation(program, "a_texcoords");

	glGenBuffers(1, &VBOpos);
	glGenBuffers(1, &VBOcolor);
	glGenBuffers(1, &VBOtexCoords);
	glGenBuffers(1, &IBO);

	// data
	glBindBuffer(GL_ARRAY_BUFFER, VBOpos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 2, g_Position, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBOcolor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, g_Colors, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBOtexCoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLubyte) * 4 * 2, g_TexCoords, GL_STATIC_DRAW);

	// indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 3 * 2, g_Indices, GL_STATIC_DRAW);

	// reset binding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// check if not already a vao from previous frames (precaution)
	if (glIsVertexArray(VAO) == GL_TRUE)
		glDeleteVertexArrays(1, &VAO);

	// generate and bind the VAO that is going to execute the commands
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// bind all the buffers to explain opengl how to use their data

	// explain openGL how to use the data
	glBindBuffer(GL_ARRAY_BUFFER, VBOpos);
	glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, VBOcolor);
	glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, VBOtexCoords);
	glVertexAttribPointer(texcoordsLoc, 2, GL_UNSIGNED_BYTE, GL_FALSE, 2 * sizeof(GLubyte), 0);

	glEnableVertexAttribArray(positionLoc);
	glEnableVertexAttribArray(colorLoc);
	glEnableVertexAttribArray(texcoordsLoc);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// reset the VAO binding
	glBindVertexArray(0);

	// unbind to be safe
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	texId = CreateTexture("../Textures/test.png", true);

	CreateFramebuffer();

	GenerateQuadVAO();

	glUseProgram(0);
}


auto	Device::Shutdown() -> void
{
	glUseProgram(0);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VBOpos);
	glDeleteBuffers(1, &VBOcolor);

	glDeleteVertexArrays(1, &GVAO);
	glDeleteBuffers(1, &GIBO);
	glDeleteBuffers(1, &GVBOpos);
	glDeleteBuffers(1, &GVBOcolor);

	glDeleteFramebuffers(1, &FBO);

	g_BasicShader.Destroy();
	g_GrayscaleShader.Destroy();
}


auto	Device::Run(int ac, char* av[]) -> void
{
	glutInit(&ac, av);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Triangle VBOs separes");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE
				  , GLUT_ACTION_CONTINUE_EXECUTION);
	glutIdleFunc(_Update);
	glutDisplayFunc(_Render);

	Initialize();

	glutMainLoop();

	Shutdown();
}


auto	Device::_Update() -> void
{
	glutPostRedisplay();
}


auto	Device::_Render() -> void
{
	//glEnable(GL_SCISSOR_TEST);
	//glScissor(0, 0, 640, 480);
	glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CW);
	/*glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

	auto program = g_BasicShader.GetProgram();
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

	glBindTexture(GL_TEXTURE_2D, texId);

	// framebuffer drawing
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glViewport(0, 0, 800, 600);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// draw scene
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);

	// second pass, back to default framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	glViewport(0, 0, 800, 600);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// now draw for real
	glUseProgram(g_GrayscaleShader.GetProgram());
	glBindVertexArray(GVAO);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, quadTextureId);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0); // everything to draw a quad
	glBindVertexArray(0);

	glUseProgram(0);
	glutSwapBuffers();
}