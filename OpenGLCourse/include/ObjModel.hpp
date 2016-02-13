#ifndef __OBJ_MODEL_HPP__
#define __OBJ_MODEL_HPP__

#include "Model.hpp"

#include <string>

namespace OpenGL {


class ObjModel :
	public Model
{
public:
	ObjModel() :
		Model()
	{ }
	ObjModel(const ObjModel&) = default;
	virtual ~ObjModel() = default;

	auto	Initialize(const std::string&) -> void;

	auto	operator = (const ObjModel&) -> ObjModel& = default;

};


}

#endif /* __OBJ_MODEL_HPP__ */