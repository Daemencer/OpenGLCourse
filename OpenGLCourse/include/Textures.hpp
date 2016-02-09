#ifndef __TEXTURES_HPP__
#define __TEXTURES_HPP__

#include <string>
#include "glew.h"

namespace OpenGL {


class Textures
{
public:
	Textures() = default;
	~Textures() = default;

	static	auto	CreateTexture(const std::string& name, bool forceAlpha) -> GLuint;
};


}

#endif /* __TEXTURES_HPP__ */