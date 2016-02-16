#ifndef __TRANSFORM_HPP__
#define __TRANSFORM_HPP__

#include "mat4.hpp"

#include "ObjParser.hpp" // TODO move the Vector struct from ObjParser to utils

namespace OpenGL {


class Transform
{
public:
	Transform() = default;
	~Transform() = default;

	auto	GetTransform() -> mat4;
	auto	GetTransform() const -> const mat4&; // combines all 3 matrix to get the transform matrix of the object

	// translation operations
	auto	Translate(float tx, float ty, float tz) -> void;
	auto	Translate(Vector3 t) -> void;

	// rotation operations
	auto	Rotate(const Vector3& axis, float angle) -> void;
	auto	Rotate(float rx, float ry, float rz, float angle) -> void;

	// scale operations
	auto	Scale(float sx, float sy, float sz) -> void;
	auto	Scale(Vector3 s) -> void;

private:
	mat4	_translateMatrix;
	mat4	_rotateMatrix;
	mat4	_scaleMatrix;

};


} // OpenGL

#endif /* __TRANSFORM_HPP__ */