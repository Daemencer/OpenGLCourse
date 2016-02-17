#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#define PI_OVER_360 (3.14159265359 / 360)

#include "Node.hpp"

namespace OpenGL {


class Camera :
	public Node
{
public:
	Camera(Node* = nullptr, const std::string& = "Default Camera");
	~Camera() { Shutdown(); }

	auto	Initialize() -> void;
	auto	Shutdown() -> void;

	static	auto	GeneratePerspectiveMatrix(float fov, float aspect, float znear, float zfar) -> float*;

	auto	GetPerspectiveMatrix() const -> float*;

	//auto	GetOrthoMatrix();

	// getters setters

private:
	float	_fov	= 60.f;
	float	_aspect	= 4.f / 3.f;
	float	_znear	= 1.f;
	float	_zfar	= 1000.f;

};


} // OpenGL

#endif /* __CAMERA_HPP__ */