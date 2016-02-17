#include "Scene.hpp"

#include "Node.hpp"
#include "Camera.hpp"
#include "GLShader.hpp"

namespace OpenGL {


Scene::Scene(const std::string& name)
{
	Initialize(name);
}


Scene::~Scene()
{
	Shutdown();

	delete _root;
}


auto	Scene::Update() -> void
{
	_root->Update();
}


auto	Scene::Draw(GLuint program) const -> void
{
	for (std::vector<Camera*>::const_iterator it = _activeCameras.begin(); it != _activeCameras.end(); ++it)
	{
		auto viewMatrixLoc = glGetUniformLocation(program, "u_viewMatrix");
		glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &(*it)->GetLocalTransform().data[0]);

		auto projectMatrixLoc = glGetUniformLocation(program, "u_projectMatrix");
		glUniformMatrix4fv(projectMatrixLoc, 1, GL_TRUE, (*it)->GetPerspectiveMatrix());

		GLuint viewPosLoc = glGetUniformLocation(program, "viewPos");
		glUniform3f(viewPosLoc, 0.0f, 0.0f, 1.0f);

		_root->Draw(program);
	}
}


auto	Scene::RegisterCamera(Camera* cam) -> void
{
	auto it = std::find(_activeCameras.begin(), _activeCameras.end(), cam);
	if (it == _activeCameras.end())
		_activeCameras.push_back(cam);
}


auto	Scene::RemoveCamera(Camera* cam) -> void
{
	auto it = std::find(_activeCameras.begin(), _activeCameras.end(), cam);
	if (it != _activeCameras.end())
		_activeCameras.erase(it);
}


auto	Scene::Initialize(const std::string& name) -> void
{
	if (!_initialized)
	{
		_name = name;

		_root = new Node(nullptr, "Root");
		_root->SetScene(this);

		_initialized = true;
	}
}


auto	Scene::Shutdown() -> void
{
	if (_initialized)
	{
		_root->Shutdown();

		_activeCameras.clear();

		_initialized = false;
	}
}


} // OpenGL