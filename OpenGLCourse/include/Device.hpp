#ifndef __DEVICE_HPP__
#define __DEVICE_HPP__

#include "glew.h"

#include "Singleton.hpp"
#include "ShaderManager.hpp"
#include "CubeModel.hpp"
#include "ObjModel.hpp"

namespace OpenGL {


class Scene;
class GLShader;

class Device :
	public Singleton<Device>
{
public:
	Device();
	~Device();

	auto	Initialize() -> void;
	auto	Shutdown() -> void;

	auto	Update() -> void;
	auto	Draw() const -> void;

	//ObjModel*	model;
	//CubeModel*	cube;

	/*GLuint GVAO;
	GLuint GVBOpos;
	GLuint GVBOcolor;
	GLuint GVBOtexCoords;
	GLuint GIBO;

	GLuint FBO;*/

	GLuint texId; // keep the texId here until I manage textures properly
	//GLuint quadTextureId;

	//void	GenerateQuadVAO();

	inline	auto	GetShaderMgr() const -> ShaderManager* { return _shaderMgr; }

	auto	GetScene() const -> Scene*;
	auto	SetScene(Scene*) -> void;

private:
	ShaderManager*	_shaderMgr = nullptr;

	Scene*	_scene;

};


} // OpenGL

#endif /* __DEVICE_HPP__ */