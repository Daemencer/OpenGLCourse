#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <string>

namespace OpenGL {


class Scene
{
public:
	Scene();
	virtual ~Scene();

	auto	Initialize() -> void;
	auto	Shutdown() -> void;

	auto	Update() -> void;
	auto	Draw() -> void;

private:
	std::string		_name;

	//Node*	_root = nullptr;

	bool	_initialized = false;

};


} // OpenGL

#endif /* __SCENE_HPP__ */