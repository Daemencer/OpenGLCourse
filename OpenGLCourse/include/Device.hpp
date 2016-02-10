#ifndef __DEVICE_HPP__
#define __DEVICE_HPP__

#include "Singleton.hpp"
#include "ShaderManager.hpp"
#include "CubeModel.hpp"
#include "PyramidModel.hpp"

namespace OpenGL {


class Device :
	public Singleton<Device>
{
public:
	Device();
	~Device();

	auto	Initialize() -> void;
	auto	Shutdown() -> void;

	ShaderManager*	ShaderMgr;

	Model*	model1;

	GLuint GVAO;
	GLuint GVBOpos;
	GLuint GVBOcolor;
	GLuint GVBOtexCoords;
	GLuint GIBO;

	GLuint FBO;

	GLuint texId;
	GLuint quadTextureId;

	void	GenerateQuadVAO();

};


} // OpenGL

#endif /* __DEVICE_HPP__ */