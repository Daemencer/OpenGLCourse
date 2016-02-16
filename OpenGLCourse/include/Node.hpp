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
	Node(Node* parent = nullptr, const std::string& = "Default Node");
	virtual ~Node();

	auto	Initialize(Node* parent, const std::string&) -> void;
	auto	Shutdown() -> void;

	auto	Update() -> void;
	auto	Draw() -> void;

	auto	Translate(float tx, float ty, float tz) -> void;
	auto	Translate(const Vector3& tv) -> void;
	auto	Rotate(const Vector3& axis, float angle) -> void;
	auto	Rotate(float rx, float ry, float rz, float angle) -> void;
	auto	Scale(float x, float y, float z) -> void;
	auto	Scale(const Vector3&) -> void;

	inline	auto	GetName() const -> std::string				{ return _name; }
	inline	auto	SetName(const std::string& name) -> void	{ _name = name; }

	inline	auto	GetScene() const -> Scene*					{ return _scene; }

	inline	auto	GetParent() const -> Node*					{ return _parent; }

	inline	auto	GetChildren() const -> std::vector<Node*>	{ return _children; }
	auto	AddChild(Node*) -> void;
	auto	RemoveChild(Node*) -> void;
	auto	RemoveChild(const std::string&) -> void;

	inline	auto	GetLocalTransform() const -> mat4 { return _transform.GetTransform(); }

	auto	GetGlobalTransform() const -> Transform;

	auto	AddModel(Model*) -> void;

private:
	bool			_initialized = false;

	std::string		_name;
	
	Transform		_transform;

	Scene*				_scene = nullptr;

	Node*				_parent = nullptr;
	std::vector<Node*>	_children;

	std::vector<Model*>	_models;

};


} // OpenGL

#endif /* __NODE_HPP__ */