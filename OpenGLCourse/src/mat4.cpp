#include "mat4.hpp"

#include <cmath>
#include <iostream>

namespace OpenGL {


mat4 Identity = { 1.0f, 0.0f, 0.0f, 0.0f
				, 0.0f, 1.0f, 0.0f, 0.0f
				, 0.0f, 0.0f, 1.0f, 0.0f
				, 0.0f, 0.0f, 0.0f, 1.0f };


mat4::mat4()
{
	for (unsigned int i = 0u; i < 16; ++i)
		data[i] = 0.0f;
}


mat4::mat4(std::initializer_list<float> params)
{
	unsigned int i = 0u;
	for (float param : params)
		data[i++] = param;
}


mat4::mat4(const mat4& mat)
{
	for (unsigned int i = 0u; i < 16; ++i)
		data[i] = mat.data[i];
}


auto	mat4::Set(std::initializer_list<float> params) -> void
{
	unsigned int i = 0u;
	for (float param : params)
		data[i++] = param;
}


auto	mat4::Set(const float params[16]) -> void
{
	for (unsigned int i = 0u; i < 16; ++i)
		data[i] = params[i];
}


auto	mat4::Set(const mat4& mat) -> void
{
	Set(mat.data);
}


auto	mat4::Rotate(float rx, float ry, float rz) -> void
{
	mat4 rotationMatrix = { 
		((cos(ry) * cos(rz)) - (sin(rx) * sin(ry) * sin(rz))),	(-cos(rx) * sin(rz)),	((cos(rz) * sin(ry)) + (sin(rx) * sin(rz) * cos(ry))),	(0.0f),
		((cos(ry) * sin(rz)) + (sin(rx) * sin(ry) * cos(rz))),	(cos(rx) * cos(rz)),	((sin(ry) * sin(rz)) - (sin(rx) * cos(rz) * cos(ry))),	(0.0f),
		(-sin(ry) * cos(rx)),									(sin(rx)),				(cos(rx) * cos(ry)),									(0.0f),
		(0.0f),													(0.0f),					(0.0f),													(1.0f)
	};

	mat4 newMat = mat4::mult(*this, rotationMatrix);
	
	Set(newMat);
}


auto	mat4::Rotate(float dx, float dy, float dz, float angle) -> void
{
	mat4 rotationMatrix = {
		(dx * dx * (1 - cos(angle))),					(dy * dx * (1 - cos(angle)) - dz * sin(angle)),	(dz * dx * (1 - cos(angle)) + dy * sin(angle)),	(0.0f),
		(dx * dy * (1 - cos(angle)) + dz * sin(angle)), (dy * dy * (1 - cos(angle) + cos(angle))),		(dz * dy * (1 - cos(angle) - dx * sin(angle))),	(0.0f),
		(dx * dz * (1 - cos(angle)) - dy * sin(angle)), (dy * dz * (1 - cos(angle)) + dx * sin(angle)), (dz * dz * (1 - cos(angle)) + cos(angle)),		(0.0f),
		(0.0f),											(0.0f),											(0.0f),											(1.0f)
	};

	mat4 newMat = mat4::mult(*this, rotationMatrix);

	Set(newMat);
}


auto	mat4::Scale(float sx, float sy, float sz) -> void
{
	mat4 mat = mat4();

	mat[0] = sx;
	mat[5] = sy;
	mat[10] = sz;

	Set(mat4::mult(*this, mat));
}


auto	mat4::mult(const mat4& r) -> void
{
	Set(mat4::mult(*this, r));
}


auto	mat4::mult(const mat4& l, const mat4& r) -> mat4
{
	mat4 mat = mat4();
	for (unsigned int i = 0u; i < 16; ++i)
	for (unsigned int j = 0u; j < 4; ++j)
		mat[i] += l.data[(i - (i % 4)) + j] * r.data[j * 4 + i % 4];
	return mat;
}


auto	mat4::print(const mat4& mat) -> void
{
	std::cout << "Matrix: [" << std::endl;
	std::cout << mat.data[0] << ", " << mat.data[1] << ", " << mat.data[2] << ", " << mat.data[3] << ", " << std::endl;
	std::cout << mat.data[4] << ", " << mat.data[5] << ", " << mat.data[6] << ", " << mat.data[7] << ", " << std::endl;
	std::cout << mat.data[8] << ", " << mat.data[9] << ", " << mat.data[10] << ", " << mat.data[11] << ", " << std::endl;
	std::cout << mat.data[12] << ", " << mat.data[13] << ", " << mat.data[14] << ", " << mat.data[15] << " ]" << std::endl;
}

auto	mat4::operator [] (int i) -> float&
{
	return data[i];
}


auto	mat4::operator * (const mat4& rhs) const -> mat4
{
	mat4	m;
	for (int i = 0; i < 16; ++i)
		m.data[i] = this->data[i] * rhs.data[i];
	return m;
}


} // OpenGL