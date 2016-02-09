#ifndef __OBJ_PARSER_HPP__
#define __OBJ_PARSER_HPP__

#include <vector>
#include <regex>

static const std::regex	FloatComponent("(-?\\d+(\\.\\d+(E-?\\d+)?)?)");
static const std::regex	Object("((\\w* ?)+)");
static const std::regex VertexLine("[\\s\\S]*");
static const std::regex	TextureLine("[\\s\\S]*");
static const std::regex	NormalLine("[\\s\\S]*");
static const std::regex	Face("(-?\\d+)\\/(-?\\d*)\\/(-?\\d*) (-?\\d+)\\/(-?\\d*)\\/(-?\\d*) (-?\\d+)\\/(-?\\d*)\\/(-?\\d*)");

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

struct s_Obj
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

	static	auto	ParseObj(const std::string& path) -> s_Obj&;

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

	s_Obj*	_wavefront;

};

#endif /* __OBJ_PARSER_HPP__ */