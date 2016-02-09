#ifndef __MAT4_HPP__
#define __MAT4_HPP__

#include <initializer_list>

namespace OpenGL {


struct mat4
{
	mat4();
	mat4(std::initializer_list<float>);
	mat4(const mat4&);
	~mat4() = default;

	auto	operator = (const mat4&) -> mat4& = default;

	float data[16];

	static	mat4	Identity;

	// methods

	auto	Set(std::initializer_list<float>) -> void;
	auto	Set(const float[16]) -> void;
	auto	Set(const mat4&) -> void;

	auto	Rotate(float rx, float ry, float rz) -> void;
	auto	Rotate(float dx, float dy, float dz, float angle) -> void;

	auto	Scale(float sx, float sy, float sz) -> void;

	// operations

	auto	mult(const mat4&) -> void;

	static	auto	mult(const mat4&, const mat4&) -> mat4;

	// utils

	static	auto	print(const mat4&) -> void;

	// operators

	auto	operator [] (int) -> float&;

};


}

#endif /* __MAT4_HPP__ */