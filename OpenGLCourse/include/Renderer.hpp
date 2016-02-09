#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

namespace OpenGL {


class Renderer
{
public:
	Renderer(int, char*[]);
	~Renderer();

	auto	Initialize(int, char*[]) -> void;
	auto	Shutdown() -> void;

	auto	Run() -> void;
	
private:
	static	auto	Update() -> void;
	static	auto	Render() -> void;

};


} // OpenGL

#endif /* __RENDERER_HPP__ */