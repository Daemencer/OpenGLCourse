#include "Scene.hpp"

#include "Node.hpp"
#include "Camera.hpp"

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


auto	Scene::Draw() -> void
{
	// draw the scene once for each registered camera setting all its data
	for (auto&& cam : _activeCameras)
	{
		// set the camera state and matrices

		_root->Draw();
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

		_root = new Node("Root");

		_activeCameras.clear();

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