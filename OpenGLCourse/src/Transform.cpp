#include "Transform.hpp"

namespace OpenGL {


auto	Transform::GetTransform() -> mat4
{
	return  _scaleMatrix * _rotateMatrix * _translateMatrix;
}


auto	Transform::Translate(float tx, float ty, float tz) -> void
{
	Translate(Vector3(tx, ty, tz));
}


auto	Transform::Translate(Vector3 t) -> void
{
	mat4 translationMatrix;

	translationMatrix[3] = t.x;
	translationMatrix[7] = t.y;
	translationMatrix[11] = t.z;

	_translateMatrix = mat4::mult(_translateMatrix, translationMatrix);
}


auto	Transform::Rotate(const Vector3& axis, float angle) -> void
{
	mat4 rotationMatrix;

	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	float c = cos(angle);
	float s = sin(angle);

	rotationMatrix.Set({
		(x*x*(1-c)+c),		(x*y*(1-c)-z*s),	(x*z*(1-c)+y*s),	(0.0f),
		(x*y*(1-c)+z*s),	(y*y*(1-c)+c),		(y*z*(1-c)-x*s),	(0.0f),
		(x*z*(1-c)-y*s),	(y*z*(1-c)+x*s),	(z*z*(1-c)+c),		(0.0f),
		(0.0f),				(0.0f),				(0.0f),				(1.0f)
	});

	_rotateMatrix = mat4::mult(_rotateMatrix, rotationMatrix);
}


auto	Transform::Rotate(float rx, float ry, float rz, float angle) -> void
{
	Rotate(Vector3(rx, ry, rz), angle);
}


auto	Transform::Scale(float sx, float sy, float sz) -> void
{
	Scale(Vector3(sx, sy, sz));
}

auto	Transform::Scale(Vector3 s) -> void
{
	mat4 scaleMatrix;

	scaleMatrix[0] = s.x;
	scaleMatrix[5] = s.y;
	scaleMatrix[10] = s.z;

	_scaleMatrix = mat4::mult(_scaleMatrix, scaleMatrix);
}


} // OpenGL