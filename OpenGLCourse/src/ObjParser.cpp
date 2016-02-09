#include <fstream>
#include <string>

#include "ObjParser.hpp"

auto	ObjParser::ParseObj(const std::string& path) -> Mesh&
{
	Mesh mesh;

	std::string str;
	std::ifstream stream;

	stream.open(path);

	if (stream.is_open())
	{
		std::string tmp;
		while (std::getline(stream, tmp))
		{
			std::string	subString = tmp.substr(0, 2);
			if (subString == "o ")
			{
				tmp.erase(0, 2);

			}
			else if (subString == "v ")
			{
				tmp.erase(0, 2);
				// treat a position
				size_t s;
				float x = std::stof(tmp, &s);
				tmp.erase(0, s);
				float y = std::stof(tmp, &s);
				tmp.erase(0, s);
				float z = std::stof(tmp, &s);
				//std::cout << "x: " << x << ", y: " << y << ", z: " << z << std::endl;
				mesh.positions.push_back(Vector3(x, y, z));
			}
			else if (subString == "vt")
			{
				tmp.erase(0, 3);

			}
			else if (subString == "vn")
			{
				tmp.erase(0, 3);

			}
			else if (subString == "f ")
			{
				tmp.erase(0, 2);

			}
			else if (subString == "vp" || subString == "mt" || subString == "us" || subString == "s " || subString == "g ")
			{
				printf("Unrecognized character, discarding the line...");
			}
			else if (subString == "# ") { }
			else
			{
				printf("Failed to read the line, returning...");
				return mesh;
			}
		}
	}
	else
		printf("Failed to open file... Wrong path probably");

	return mesh;
}


auto	ObjParser::TestLine(std::string& s) -> std::string
{
	return _GetLine(s.c_str());
}


auto	ObjParser::TestWord(std::string& s) -> std::string
{
	return _GetWord(s.c_str());
}

auto	ObjParser::_AddPositions() -> void
{
}


auto	ObjParser::_GetLine(char const* string, char separator) -> char*
{
	char* newString = "";
	unsigned int i = 0u;

	while (string[i] != separator)
	{
		newString += string[i];
		++string;
	}

	++string;

	return newString;
}


auto	ObjParser::_GetWord(char const* string, char separator) -> char*
{
	char* newString = "";
	unsigned int i = 0u;

	while (string[i] != separator)
	{
		newString += string[i];
		++string;
	}

	return newString;
}