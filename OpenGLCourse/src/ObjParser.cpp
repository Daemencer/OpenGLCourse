#include <fstream>

#include "ObjParser.hpp"

auto	ObjParser::ParseObj(const std::string& path) -> s_Obj&
{
	s_Obj obj;

	std::string str;
	std::ifstream stream;

	stream.open(path);

	if (stream.is_open())
	{
		std::string tmp;
		while (std::getline(stream, tmp))
		{
			// process the line you just extracted
			if (tmp.substr(0, 2) == "o ")
			{
				tmp.erase(0, 2);
			}
			else if (tmp.substr(0, 2) == "v ")
			{
				tmp.erase(0, 2);

			}
			else if (tmp.substr(0, 2) == "vt")
			{
				tmp.erase(0, 3);

			}
			else if (tmp.substr(0, 2) == "vn")
			{
				tmp.erase(0, 3);

			}
			else if (tmp.substr(0, 2) == "f ")
			{
				tmp.erase(0, 2);

			}
			else if (tmp.substr(0, 2) == "vp" || tmp.substr(0, 2) == "mt" || tmp.substr(0, 2) == "us" || tmp.substr(0, 2) == "s " || tmp.substr(0, 2) == "g ")
			{
				printf("Unrecognized character, discarding the line...");
			}
			else if (tmp.substr(0, 2) == "# ") { }
			else
			{
				printf("Failed to read the line, returning...");
				return obj;
			}
		}
	}
	else
		printf("Failed to open file... Wrong path probably");

	return obj;
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