#include "Transform.hpp"

namespace OpenGL {


auto	Transform::GetTransform() -> mat4
{
	return _translateMatrix * _rotateMatrix * _scaleMatrix;
}


} // OpenGL