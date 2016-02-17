#include "Camera.hpp"

#include <cmath>
#include "Scene.hpp"

namespace OpenGL {


Camera::Camera(Node* parent, const std::string& name) :
	Node(parent, name)
{
	Initialize();
}


auto	Camera::Initialize() -> void
{
	if (this->GetScene())
		this->GetScene()->RegisterCamera(this);
}


auto	Camera::Shutdown() -> void
{
	if (this->GetScene())
		this->GetScene()->RemoveCamera(this);
}


auto	Camera::GeneratePerspectiveMatrix(float fov, float aspect, float znear, float zfar) -> float*
{
	float m[16];

	float xymax = znear * tan(fov * PI_OVER_360);
	float ymin = -xymax;
	float xmin = -xymax;

	float width = xymax - xmin;
	float height = xymax - ymin;

	float depth = zfar - znear;
	float q = -(zfar + znear) / depth;
	float qn = -2 * (zfar * znear) / depth;

	float w = 2 * znear / width;
	w = w / aspect;
	float h = 2 * znear / height;

	m[0] = w;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;

	m[4] = 0;
	m[5] = h;
	m[6] = 0;
	m[7] = 0;

	m[8] = 0;
	m[9] = 0;
	m[10] = q;
	m[11] = -1;

	m[12] = 0;
	m[13] = 0;
	m[14] = qn;
	m[15] = 0;

	return m;
}


auto	Camera::GetPerspectiveMatrix() const -> float*
{
	float m[16];

	float xymax = _znear * tan(_fov * PI_OVER_360);
	float ymin = -xymax;
	float xmin = -xymax;

	float width = xymax - xmin;
	float height = xymax - ymin;

	float depth = _zfar - _znear;
	float q = -(_zfar + _znear) / depth;
	float qn = -2 * (_zfar * _znear) / depth;

	float w = 2 * _znear / width;
	w = w / _aspect;
	float h = 2 * _znear / height;

	m[0] = w;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;

	m[4] = 0;
	m[5] = h;
	m[6] = 0;
	m[7] = 0;

	m[8] = 0;
	m[9] = 0;
	m[10] = q;
	m[11] = -1;

	m[12] = 0;
	m[13] = 0;
	m[14] = qn;
	m[15] = 0;

	return m;
}


} // OpenGL