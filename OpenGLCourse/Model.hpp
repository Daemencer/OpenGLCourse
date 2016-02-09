#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include "glew.h"

class Model
{
public:
	Model() = default;
	~Model() = default;

	auto	Initialize() -> void; // do the actual things here and set the _vao to the proper value

	auto	GetModelVAO() const -> GLuint; // just return a value, computing is in Initialize so that it's done only once

private:
	GLuint	_vao = -1;

};

#endif /* __MODEL_HPP__ */