// ---------------------------------------------------------------------------
//
// GL OpenGL (ES) 2.0 Framework
// Malek Bengougam, 2012							malek.bengougam@gmail.com
//
// ---------------------------------------------------------------------------

#ifndef __GL_SHADER_HPP__
#define __GL_SHADER_HPP__

// --- Includes --------------------------------------------------------------

#include <glew.h>

// --- Classes ---------------------------------------------------------------

class GLShader
{
public:
	GLShader() : m_ProgramObject(0), m_VertexShader(0)
		, m_FragmentShader(0), m_GeometryShader(0)
	{
	}
	~GLShader()
	{
	}

	bool LoadVertexShader(const char *source);
	bool LoadFragmentShader(const char *source);

	bool Create();
	void Destroy();

	GLuint Bind();
	void Unbind();

	inline GLuint GetProgram() const { return m_ProgramObject; }

private:
	// handle du program object
	GLuint m_ProgramObject;
	// handles des shaders
	GLuint m_VertexShader;
	GLuint m_FragmentShader;
	GLuint m_GeometryShader;
};

#endif // __GL_SHADER_HPP__