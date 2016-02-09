#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

namespace OpenGL {


class Renderer
{
public:
	Renderer();
	~Renderer();

	auto	Initialize() -> void;
	auto	Shutdown() -> void;

	auto	Run(int, char*[]) -> void;
	
private:
	static	auto	Update() -> void;
	static	auto	Render() -> void;

};


} // OpenGL

#endif /* __RENDERER_HPP__ */