#ifndef __TRANSFORM_HPP__
#define __TRANSFORM_HPP__

#include "mat4.hpp"

namespace OpenGL {


class Transform
{
public:
	Transform() = default;
	~Transform() = default;

	auto	GetTransform() -> mat4; // combines all 3 matrix to get the transform matrix of the object

	//auto	Translate() -> void;
	//auto	Rotate() -> void;
	//auto	Scale() -> void;

private:
	mat4	_translateMatrix;
	mat4	_rotateMatrix;
	mat4	_scaleMatrix;

};


} // OpenGL

#endif /* __TRANSFORM_HPP__ */