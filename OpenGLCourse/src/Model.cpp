#include "Model.hpp"

#include "glew.h"

#include "Device.hpp"
#include "ShaderManager.hpp"

namespace OpenGL {


Model::~Model()
{
	Shutdown();
}


auto	Model::Initialize() -> void
{
	GLuint program = Device::GetInstance()->ShaderMgr->GetProgram("basic");
	glUseProgram(program);

	auto positionLoc = glGetAttribLocation(program, "a_position");
	//auto colorLoc = glGetAttribLocation(program, "a_normal");
	auto texcoordsLoc = glGetAttribLocation(program, "a_texcoords");

	glGenBuffers(1, &_VBOpos);
	//glGenBuffers(1, &_VBOnormals);
	glGenBuffers(1, &_VBOtexcoords);
	glGenBuffers(1, &_IBO);

	// data
	glBindBuffer(GL_ARRAY_BUFFER, _VBOpos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 24 * 3, _positions.data(), GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, _VBOtexcoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 24 * 2, _texcoords.data(), GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, _VBOnormals);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 24 * 3, _normals.data(), GL_STATIC_DRAW);

	// indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 12 * 3, _indices.data(), GL_STATIC_DRAW);

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
	glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	/*glBindBuffer(GL_ARRAY_BUFFER, _VBOnormals);
	glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);*/
	glBindBuffer(GL_ARRAY_BUFFER, _VBOtexcoords);
	glVertexAttribPointer(texcoordsLoc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);

	glEnableVertexAttribArray(positionLoc);
	//glEnableVertexAttribArray(normalLoc);
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
	_positions.clear();
	_texcoords.clear();
	_normals.clear();
	_indices.clear();

	glDeleteBuffers(1, &_VBOpos);
	//glDeleteBuffers(1, &_VBOnormals);
	glDeleteBuffers(1, &_VBOtexcoords);
	glDeleteBuffers(1, &_IBO);

	glDeleteVertexArrays(1, &_vao);
}


auto	Model::GetModelVAO() const -> GLuint
{
	return _vao;
}


} // OpenGL