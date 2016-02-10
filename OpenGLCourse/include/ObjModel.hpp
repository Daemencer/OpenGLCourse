#ifndef __OBJ_MODEL_HPP__
#define __OBJ_MODEL_HPP__

#include "Model.hpp"

#include <string>

namespace OpenGL {


class ObjModel :
	public Model
{
public:
	ObjModel() = delete;
	ObjModel(const std::string&);
	ObjModel(const ObjModel&) = default;
	virtual ~ObjModel();

	override	auto	Initialize(const std::string&) -> void; // will set the const float* to the OBJ parsed. If the OBJ isn't yet parsed, parse it, else, get it from resource manager

	auto	operator = (const ObjModel&) -> ObjModel& = default;

};


}

#endif /* __OBJ_MODEL_HPP__ */