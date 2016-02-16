#include "Node.hpp"

namespace OpenGL {


Node::Node(Node* parent, const std::string& name)
{
	Initialize(parent, name);
}


Node::~Node()
{
}


auto	Node::Initialize(Node* parent, const std::string& name) -> void
{
	if (!_initialized)
	{
		_name = name;

		if (parent)
		{
			_parent = parent;

			if (_parent->_scene)
				_scene = parent->_scene;
		}
		else
		{
			_parent = nullptr;
			_scene = nullptr;
		}

		_children.clear();
		_models.clear();

		_initialized = true;
	}
}


auto	Node::Shutdown() -> void
{
	if (_initialized)
	{
		for (auto& child : _children)
			child->Shutdown();

		_scene = nullptr;

		_models.clear();

		_initialized = false;
	}
}


auto	Node::Update() -> void
{
	for (auto& child : _children)
		child->Update();
}


auto	Node::Draw() -> void
{
	// set the matrices and draw its models
}


auto	Node::Translate(float tx, float ty, float tz) -> void
{
	_transform.Translate(tx, ty, tz);
}


auto	Node::Translate(const Vector3& tv) -> void
{
	_transform.Translate(tv);
}


auto	Node::Rotate(const Vector3& axis, float angle) -> void
{
	_transform.Rotate(axis, angle);
}

auto	Node::Rotate(float rx, float ry, float rz, float angle) -> void
{
	_transform.Rotate(rx, ry, rz, angle);
}


auto	Node::Scale(float sx, float sy, float sz) -> void
{
	_transform.Scale(sx, sy, sz);
}


auto	Node::Scale(const Vector3& sv) -> void
{
	_transform.Scale(sv);
}


auto	Node::AddChild(Node *) -> void
{
}


auto	Node::RemoveChild(Node *) -> void
{
}


auto	Node::RemoveChild(const std::string &) -> void
{
}


auto Node::GetGlobalTransform() const -> Transform
{
	// calculate the transform from all the parents up to the root node
	return Transform();
}

auto	Node::AddModel(Model* model) -> void
{
	auto it = std::find(_models.begin(), _models.end(), model);
	if (it == _models.end())
		_models.push_back(model);
}


} // OpenGL