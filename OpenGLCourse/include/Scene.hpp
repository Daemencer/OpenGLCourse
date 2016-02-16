#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <vector>
#include <string>

namespace OpenGL {


class Node;
class Camera;

class Scene
{
public:
	Scene(const std::string& = "Default Scene");
	virtual ~Scene();

	auto	Update() -> void;
	auto	Draw() -> void;

	auto	RegisterCamera(Camera*) -> void;
	auto	RemoveCamera(Camera*) -> void;

protected:
	auto	Initialize(const std::string&) -> void;
	auto	Shutdown() -> void;

private:
	std::string		_name;

	Node*	_root = nullptr;

	std::vector<Camera*> _activeCameras;

	bool	_initialized = false;

};


} // OpenGL

#endif /* __SCENE_HPP__ */