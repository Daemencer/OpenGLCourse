#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#define PI_OVER_360 (3.14159265359 / 360)

namespace OpenGL {


class Camera
{
public:
	Camera() = default;
	~Camera() = default;

	static	auto	GetPerspectiveMatrix(float*, float fov, float aspect, float znear, float zfar) -> void;
	//static	auto	GetOrthoMatrix();

private:

};


} // OpenGL

#endif /* __CAMERA_HPP__ */