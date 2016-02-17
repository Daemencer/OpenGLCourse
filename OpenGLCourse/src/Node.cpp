#include "Node.hpp"

#include "GLShader.hpp"
#include "Model.hpp"
#include "ObjModel.hpp"

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
			parent->AddChild(this);
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
	// updates the components
	static float time = 0.0f;
	time += 1.0f / 60.0f;

	//Rotate(Vector3(0.0f, 1.0f, 0.0f), time);

	for (auto& child : _children)
		child->Update();
}


auto	Node::Draw(GLuint program) const -> void
{
	auto worldMatrixLoc = glGetUniformLocation(program, "u_worldMatrix");
	glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &_transform.GetTransform().data[0]);

	for (auto& model : _models)
	{
		glBindVertexArray(model->GetModelVAO());
		glDrawElements(GL_TRIANGLES, model->GetModelIndexCount(), GL_UNSIGNED_SHORT, 0);
		glBindVertexArray(0);
	}

	for (auto& child : _children)
		child->Draw(program);
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


auto	Node::AddChild(Node* child) -> void
{
	_children.push_back(child);

	child->_parent = this;

	if (_scene)
		child->_scene = this->_scene;
	else
		child->_scene = nullptr;
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