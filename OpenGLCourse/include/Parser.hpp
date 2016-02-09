#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <string>
#include <fstream>

class Parser
{
public:
	Parser() = delete;
	virtual ~Parser() = delete;

	static	auto	ParseFile(const std::string& path) -> std::string;

protected:
	static	auto	_GetLine(char const*, char separator = '\n') -> char*;
	static	auto	_GetWord(char const*, char separator = ' ') -> char*;

};

#endif /* __PARSER_HPP__ */