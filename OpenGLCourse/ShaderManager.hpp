#ifndef __SHADER_MANAGER_HPP__
#define __SHADER_MANAGER_HPP__

#include <map>
#include <string>

#include "glew.h"

class ShaderManager final
{
public:
	ShaderManager() = default;
	~ShaderManager() = default;

	auto	AddNewProgram(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath) -> void;

	auto	GetProgram(const std::string& progName) const -> GLuint;

private:
	std::map<const std::string&, GLShader>		_programs;

};

#endif /* __SHADER_MANAGER_HPP__ */