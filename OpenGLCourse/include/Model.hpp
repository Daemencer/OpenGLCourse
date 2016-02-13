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

	auto	GetModelIndexCount() const -> unsigned int { return _indexCount; }

protected:
	GLuint	_vao			= -1;

	GLuint	_VBOpos			= -1;
	GLuint	_VBOtexcoords	= -1;
	GLuint	_VBOnormals		= -1;
	GLuint	_IBO			= -1;

	unsigned int				_posisitionCount	= 0u;
	std::vector<float>			_positions;

	unsigned int				_texcoordCount		= 0u;
	std::vector<float>			_texcoords;

	unsigned int				_normalCount		= 0u;
	std::vector<float>			_normals;

	unsigned int				_indexCount			= 0u;
	std::vector<unsigned short>	_indices;

};


} // OpenGL

#endif /* __MODEL_HPP__ */