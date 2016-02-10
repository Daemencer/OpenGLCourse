#ifndef __CUBE_MODEL_HPP__
#define __CUBE_MODEL_HPP__

#include "Model.hpp"

namespace OpenGL {


class CubeModel :
	public Model
{
public:
	CubeModel() :
		Model() 
	{ }
	virtual ~CubeModel() = default;

	auto	Initialize() -> void;

};


} // OpenGL

#endif /* __CUBE_MODEL_HPP__ */