#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include <vector>
#include "glew.h"

namespace OpenGL {


class Model
{
public:
	Model() { }
	virtual ~Model();

	virtual	auto	Initialize() -> void; // do the actual things here and set the _vao to the proper value
	auto	Shutdown() -> void;

	auto	GetModelVAO() const->GLuint; // just return a value, computing is in Initialize so that it's done only once

protected:
	GLuint	_vao			= -1;

	GLuint	_VBOpos			= -1;
	GLuint	_VBOtexcoords	= -1;
	GLuint	_VBOnormals		= -1;
	GLuint	_IBO			= -1;

	std::vector<float>			_positions;
	std::vector<float>			_texcoords;
	std::vector<float>			_normals;
	std::vector<unsigned short>	_indices;

};


} // OpenGL

#endif /* __MODEL_HPP__ */