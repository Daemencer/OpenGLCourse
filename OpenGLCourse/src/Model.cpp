#include "Model.hpp"

#include "glew.h"

#include "Device.hpp"
#include "ShaderManager.hpp"

namespace OpenGL {


Model::Model()
{
	Initialize();
}


Model::~Model()
{
	Shutdown();
}


auto	Model::Initialize() -> void
{
	// all of that will become loaded from an obj
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

	GLuint program = Device::GetInstance()->ShaderMgr->GetProgram("basic");
	glUseProgram(program);

	auto positionLoc = glGetAttribLocation(program, "a_position");
	auto colorLoc = glGetAttribLocation(program, "a_color");
	auto texcoordsLoc = glGetAttribLocation(program, "a_texcoords");

	glGenBuffers(1, &_VBOpos);
	glGenBuffers(1, &_VBOcolor);
	glGenBuffers(1, &_VBOtexcoords);
	glGenBuffers(1, &_IBO);

	// data
	glBindBuffer(GL_ARRAY_BUFFER, _VBOpos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 2, g_Position, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, _VBOcolor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, g_Colors, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, _VBOtexcoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLubyte) * 4 * 2, g_TexCoords, GL_STATIC_DRAW);

	// indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 3 * 2, g_Indices, GL_STATIC_DRAW);

	// reset binding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// check if not already a vao from previous frames (precaution)
	if (glIsVertexArray(_vao) == GL_TRUE)
		glDeleteVertexArrays(1, &_vao);

	// generate and bind the VAO that is going to execute the commands
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	// bind all the buffers to explain opengl how to use their data

	// explain openGL how to use the data
	glBindBuffer(GL_ARRAY_BUFFER, _VBOpos);
	glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, _VBOcolor);
	glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, _VBOtexcoords);
	glVertexAttribPointer(texcoordsLoc, 2, GL_UNSIGNED_BYTE, GL_FALSE, 2 * sizeof(GLubyte), 0);

	glEnableVertexAttribArray(positionLoc);
	glEnableVertexAttribArray(colorLoc);
	glEnableVertexAttribArray(texcoordsLoc);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);

	// reset the VAO binding
	glBindVertexArray(0);

	// unbind to be safe
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


auto	Model::Shutdown() -> void
{
	glDeleteBuffers(1, &_VBOpos);
	glDeleteBuffers(1, &_VBOcolor);
	glDeleteBuffers(1, &_VBOtexcoords);
	glDeleteBuffers(1, &_IBO);

	glDeleteVertexArrays(1, &_vao);
}


auto	Model::GetModelVAO() const -> GLuint
{
	return _vao;
}


} // OpenGL