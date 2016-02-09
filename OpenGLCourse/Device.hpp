#ifndef __DEVICE_HPP__
#define __DEVICE_HPP__

#include "ShaderManager.hpp"

class Device
{
public:
	Device();
	~Device();

	auto	Initialize() -> void;
	auto	Shutdown() -> void;

	auto	Run(int, char*[]) -> void;

private:
	static auto	_Update() -> void;
	static auto	_Render() -> void;

	ShaderManager*	_shaderMgr = nullptr;
};

#endif /* __DEVICE_HPP__ */