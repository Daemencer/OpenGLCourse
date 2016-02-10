#ifndef __PYRAMID_MODEL_HPP__
#define __PYRAMID_MODEL_HPP__

#include "Model.hpp"

#include <iostream>

namespace OpenGL {


class PyramidModel :
	public Model
{
public:
	PyramidModel() = default;
	virtual ~PyramidModel() = default;

	auto	Initialize() -> void { std::cout << "Wesh" << std::endl; }
};


} // OpenGL

#endif /* __PYRAMID_MODEL_HPP__ */