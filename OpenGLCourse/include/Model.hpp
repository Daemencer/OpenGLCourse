#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include "glew.h"

namespace OpenGL {


class Model
{
public:
	Model();
	~Model();

	auto	Initialize() -> void; // do the actual things here and set the _vao to the proper value
	auto	Shutdown() -> void;

	auto	GetModelVAO() const->GLuint; // just return a value, computing is in Initialize so that it's done only once

private:
	GLuint	_vao = -1;

	GLuint	_VBOpos = -1;
	GLuint	_VBOcolor = -1;
	GLuint	_VBOtexcoords = -1;
	GLuint	_IBO = -1;

};


} // OpenGL

#endif /* __MODEL_HPP__ */