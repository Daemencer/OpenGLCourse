#ifndef __MESH_HPP__
#define __MESH_HPP__

#include <string>
#include <vector>

#include "glew.h"

#include "GLShader.hpp"

namespace OpenGL {


struct Vector2
{
	Vector2() :
		x(0),
		y(0)
	{ }

	Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	auto	operator == (const Vector2& v) const -> bool
	{
		return (this->x == v.x && this->y == v.y);
	}

	float x, y;
};

struct Vector3
{
	Vector3() :
		x(0),
		y(0),
		z(0)
	{ }

	Vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	auto	operator == (const Vector3& v) const -> bool
	{
		return (this->x == v.x && this->y == v.y && this->z == v.z);
	}

	float x, y, z;
};

struct Vertex
{
	Vertex() { }
	Vertex(Vector3 _position, Vector2 _texcoord, Vector3 _normal) :
		position(_position.x, _position.y, _position.z),
		texcoord(_texcoord.x, _texcoord.y),
		normal(_normal.x, _normal.y, _normal.z)
	{
	}

	auto	operator == (const Vertex& v) const -> bool
	{
		return (this->position == v.position && this->texcoord == v.texcoord && this->normal == v.normal);
	}

	Vector3	position;
	Vector2	texcoord;
	Vector3 normal;
};

struct Texture {
	GLuint id;
	std::string type;
	char const* path;
};

class Mesh {
public:
	/*  Mesh Data  */
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	/*  Functions  */
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);

	void Draw(GLShader* shader);
private:
	/*  Render data  */
	GLuint VAO, VBO, EBO;

	/*  Functions    */
	void _SetupMesh();
};


} // OpenGL

#endif /* __MESH_HPP__ */