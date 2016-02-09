#include "Parser.hpp"

#include <ios>
#include <iostream>
#include <fstream>

auto	Parser::ParseFile(const std::string& path) -> std::string
{
	std::string str;
	std::ifstream stream;

	stream.open(path);

	if (stream.is_open())
	{
		std::string tmp;
		while (std::getline(stream, tmp))
		{
			str.append(tmp + "\n");
		}
		str.erase(str.end() - 1); // removes the last useless \n
	}
	else
		printf("Failed to open file... Wrong path probably");

	return str;
}


auto	Parser::_GetLine(char const* string, char separator) -> char*
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


auto	Parser::_GetWord(char const* string, char separator) -> char*
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