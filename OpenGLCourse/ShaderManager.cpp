#include "ShaderManager.hpp"

#include "GLShader.hpp"

ShaderManager::ShaderManager()
{

}


ShaderManager::~ShaderManager()
{

}


auto	ShaderManager::AddNewProgram(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath) -> void
{
	GLShader shader;
	shader.LoadVertexShader(vertexShaderPath.c_str());
	shader.LoadFragmentShader(fragmentShaderPath.c_str());
	shader.Create();

	_programs.emplace(name, shader);
}


auto	ShaderManager::GetProgram(const std::string& progName) const -> GLuint
{
	return _programs[progName].GetProgram();
}
