#ifndef __OBJ_PARSER_HPP__
#define __OBJ_PARSER_HPP__

#include <vector>
#include <iostream>

struct Vector2
{
	Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	float x, y;
};

struct Vector3
{
	Vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	float x, y, z;
};

struct Mesh
{
	std::vector<Vector3>	positions;
	std::vector<Vector3>	colors;
	std::vector<Vector2>	texcoords;
	std::vector<Vector3>	indices;
};

class ObjParser
{
public:
	ObjParser() = delete;
	~ObjParser() = delete;

	static	auto	ParseObj(const std::string& path) -> Mesh&;

	///////////
	static	auto	TestLine(std::string&) -> std::string;
	static	auto	TestWord(std::string&) -> std::string;
	///////////

private:
	static	auto	_AddPositions() -> void;
	static	auto	_AddNormals() -> void;
	static	auto	_AddTexcoords() -> void;
	static	auto	_AddIndices() -> void;

	static	auto	_GetLine(char const*, char separator = '\n') -> char*;
	static	auto	_GetWord(char const*, char separator = ' ') -> char*;

	Mesh*	_wavefront;

};

#endif /* __OBJ_PARSER_HPP__ */