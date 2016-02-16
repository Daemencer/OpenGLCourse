#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <vector>
#include <string>

#include "Transform.hpp"

#include "ObjParser.hpp" // TODO move the Vector struct from ObjParser to utils

namespace OpenGL {


class Model;
class Scene;

class Node
{
public:
	Node(const std::string& = "Default Node");
	virtual ~Node();

	auto	Initialize() -> void;
	auto	Shutdown() -> void;

	auto	Update() -> void;
	auto	Draw() -> void;

	auto	Translate(float x, float y, float z) -> void;
	auto	Translate(Vector3) -> void;
	auto	Rotate(float x, float y, float z) -> void;
	auto	Rotate(Vector3) -> void;
	auto	Rotate(float x, float y, float z, Vector3) -> void;
	auto	Rotate(Vector3, Vector3) -> void;
	auto	Scale(float x, float y, float z) -> void;
	auto	Scale(Vector3) -> void;

	inline	auto	GetName() const -> std::string				{ return _name; }
	inline	auto	SetName(const std::string& name) -> void	{ _name = name; }

	auto	GetScene() const -> Scene*;

	auto	GetParent() const -> Node*;
	//auto	SetParent(Node*) -> void;

	auto	GetChildren() const -> std::vector<Node*>;
	auto	AddChild(Node*) -> void;
	auto	RemoveChild(Node*) -> void;
	auto	RemoveChild(const std::string&) -> void;

	auto	GetGlobalTransform() const -> Transform;
	auto	GetLocalTransform() const -> Transform;

	auto	AddModel(Model*) -> void;

private:
	std::string		_name;
	
	Transform		_transform;

	Scene*				_scene = nullptr;

	Node*				_parent = nullptr;
	std::vector<Node*>	_children;

	std::vector<Model*>	_models;

};


} // OpenGL

#endif /* __NODE_HPP__ */