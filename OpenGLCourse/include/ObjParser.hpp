#ifndef __OBJ_PARSER_HPP__
#define __OBJ_PARSER_HPP__

#include <vector>
#include <unordered_map>
#include <iostream>
#include <functional>

namespace OpenGL {


template <class T>
inline void hash_combine(std::size_t & s, const T & v)
{
	std::hash<T> h;
	s ^= h(v) + 0x9e3779b9 + (s << 6) + (s >> 2);
}

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


struct Mesh
{
	std::vector<Vertex>	points;

	std::vector<unsigned short>	indices;

};

//template <class T>
//class MyHash;
//
//template<>
//struct MyHash<Vertex>
//{
//	auto	operator () (const Vertex& v) const -> std::size_t
//	{
//		std::size_t res = 0;
//		hash_combine(res, v.position.x);
//		hash_combine(res, v.position.y);
//		hash_combine(res, v.position.z);
//		hash_combine(res, v.texcoord.x);
//		hash_combine(res, v.texcoord.y);
//		hash_combine(res, v.normal.x);
//		hash_combine(res, v.normal.y);
//		hash_combine(res, v.normal.z);
//		return res;
//	}
//};


class ObjParser
{
public:
	ObjParser() = delete;
	~ObjParser() = delete;

	static	auto	ParseObj(const std::string& path) -> Mesh;

private:
	static	auto	_GetLine(char const*, char separator = '\n') -> char*;
	static	auto	_GetWord(char const*, char separator = ' ') -> char*;
	static	auto	_GetFaceData(std::string*) -> std::string;
	static	auto	_FindIndex(const Mesh&, const Vertex&) -> unsigned short;
	static	auto	_AddVertex(Mesh*, Vertex) -> void;
	static	auto	_GenerateVertexHash(const Vertex&) -> long long;

	static	std::unordered_map<long long, const Vertex&> _hashTable;

};


} // OpenGL

#endif /* __OBJ_PARSER_HPP__ */