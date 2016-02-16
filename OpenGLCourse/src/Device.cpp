#include "Device.hpp"

#include <cstdio>
#include <string>

#include "glew.h"
#define FREEGLUT_LIB_PRAGMAS 0
#include "Freeglut.h"

#include "GLShader.hpp"
#include "Textures.hpp"
#include "Scene.hpp"

namespace OpenGL {


Device::Device()
{
	Initialize();
}


Device::~Device()
{
	Shutdown();
}


void CreateFramebuffer()
{
	glGenFramebuffers(1, &Device::GetInstance()->FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, Device::GetInstance()->FBO);

	// create a texture for the Framebuffer
	glGenTextures(1, &Device::GetInstance()->quadTextureId);
	glBindTexture(GL_TEXTURE_2D, Device::GetInstance()->quadTextureId);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//////////

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Device::GetInstance()->quadTextureId, 0);

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


void	Device::GenerateQuadVAO()
{
	//Device::ShaderMgr->AddNewProgram("grayscale", "basicGrayscale.vs", "basicGrayscale.fs");

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

	auto program = Device::ShaderMgr->GetProgram("basic");
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


auto	Device::GetScene() const -> Scene*
{
	return _scene;
}


auto	Device::SetScene(Scene* scene) -> void
{
	if (_scene)
		delete _scene;

	_scene = scene;
}


auto	Device::Initialize() -> void
{
	printf("Version OpenGL : %s\n", glGetString(GL_VERSION));
	printf("Fabricant : %s\n", glGetString(GL_VENDOR));
	printf("Pilote : %s\n", glGetString(GL_RENDERER));
	printf("Version GLSL : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	ShaderMgr = new ShaderManager();

	ShaderMgr->AddNewProgram("basic", "basic.vs", "basic.fs");

	model = new ObjModel();
	model->Initialize("resources/models/Trex.obj");

	//cube = new CubeModel();
	//cube->Initialize();

	texId = Textures::CreateTexture("resources/textures/Trex.png", true);

	//CreateFramebuffer();

	glUseProgram(0);
}


auto	Device::Shutdown() -> void
{
	glUseProgram(0);

	glDeleteVertexArrays(1, &GVAO);
	glDeleteBuffers(1, &GIBO);
	glDeleteBuffers(1, &GVBOpos);
	glDeleteBuffers(1, &GVBOcolor);

	glDeleteFramebuffers(1, &FBO);

	delete ShaderMgr;
	delete model;
	//delete cube;
}


auto	Device::Update() -> void
{
	_scene->Update();
}


auto	Device::Draw() -> void
{
	_scene->Draw();
}


} // OpenGL