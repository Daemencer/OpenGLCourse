#include <fstream>
#include <string>
#include <algorithm>

#include "ObjParser.hpp"

namespace OpenGL {


std::unordered_map<long long, const Vertex&> ObjParser::_hashTable = std::unordered_map<long long, const Vertex&>();


auto	ObjParser::ParseObj(const std::string& path) -> Mesh
{
	ObjParser::_hashTable.clear();

	Mesh mesh;

	std::string str;
	std::ifstream stream;

	std::vector<Vector3>	positions;
	std::vector<Vector2>	texcoords;
	std::vector<Vector3>	normals;

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
				size_t s;
				float x = std::stof(tmp, &s);
				tmp.erase(0, s);
				float y = std::stof(tmp, &s);
				tmp.erase(0, s);
				float z = std::stof(tmp, &s);
				positions.push_back(Vector3(x, y, z));
			}
			else if (subString == "vt")
			{
				tmp.erase(0, 3);
				size_t s;
				float x = std::stof(tmp, &s);
				tmp.erase(0, s);
				float y = std::stof(tmp, &s);
				tmp.erase(0, s);
				texcoords.push_back(Vector2(x, y));
			}
			else if (subString == "vn")
			{
				tmp.erase(0, 3);
				size_t s;
				float x = std::stof(tmp, &s);
				tmp.erase(0, s);
				float y = std::stof(tmp, &s);
				tmp.erase(0, s);
				float z = std::stof(tmp, &s);
				normals.push_back(Vector3(x, y, z));
			}
			else if (subString == "f ")
			{
				//// create the faces
				tmp.erase(0, 2);

				Vector3 position;
				Vector2 texcoord;
				Vector3 normal;

				size_t s, token;
				std::string line;
				std::string ret;

				///////////////////////
				line = ObjParser::_GetFaceData(&tmp); // get the line data as string

				token = line.find("/");			// get the token of where the first / is found
				ret = line.substr(0, token);	// get the string of everything before the first found token
				line.erase(0, token + 1);		// erase up to the token + the token itself

				position = positions[std::stoi(ret, &s) - 1];

				token = line.find("/");			// get the token of where the first / is found
				ret = line.substr(0, token);	// get the string of everything before the first found token
				line.erase(0, token + 1);		// erase up to the token + the token itself

				texcoord = texcoords[std::stoi(ret, &s) - 1];

				token = line.find("/");			// get the token of where the first / is found
				ret = line.substr(0, token);	// get the string of everything before the first found token
				line.erase(0, token + 1);		// erase up to the token + the token itself

				normal = normals[std::stoi(ret, &s) - 1];

				Vertex v1(position, texcoord, normal);
				ObjParser::_AddVertex(&mesh, v1);
				///////////////////////

				///////////////////////
				line = ObjParser::_GetFaceData(&tmp); // get the line data as string

				token = line.find("/");			// get the token of where the first / is found
				ret = line.substr(0, token);	// get the string of everything before the first found token
				line.erase(0, token + 1);		// erase up to the token + the token itself

				position = positions[std::stoi(ret, &s) - 1];

				token = line.find("/");			// get the token of where the first / is found
				ret = line.substr(0, token);	// get the string of everything before the first found token
				line.erase(0, token + 1);		// erase up to the token + the token itself

				texcoord = texcoords[std::stoi(ret, &s) - 1];

				token = line.find("/");			// get the token of where the first / is found
				ret = line.substr(0, token);	// get the string of everything before the first found token
				line.erase(0, token + 1);		// erase up to the token + the token itself

				normal = normals[std::stoi(ret, &s) - 1];

				Vertex v2(position, texcoord, normal);
				ObjParser::_AddVertex(&mesh, v2);
				///////////////////////

				///////////////////////
				line = ObjParser::_GetFaceData(&tmp); // get the line data as string

				token = line.find("/");			// get the token of where the first / is found
				ret = line.substr(0, token);	// get the string of everything before the first found token
				line.erase(0, token + 1);		// erase up to the token + the token itself

				position = positions[std::stoi(ret, &s) - 1];

				token = line.find("/");			// get the token of where the first / is found
				ret = line.substr(0, token);	// get the string of everything before the first found token
				line.erase(0, token + 1);		// erase up to the token + the token itself

				texcoord = texcoords[std::stoi(ret, &s) - 1];

				token = line.find("/");			// get the token of where the first / is found
				ret = line.substr(0, token);	// get the string of everything before the first found token
				line.erase(0, token + 1);		// erase up to the token + the token itself

				normal = normals[std::stoi(ret, &s) - 1];

				Vertex v3(position, texcoord, normal);
				ObjParser::_AddVertex(&mesh, v3);
				///////////////////////
			}
			else if (subString == "vp" || subString == "mt" || subString == "us" || subString == "s " || subString == "g ")
			{
				printf("Unrecognized character, discarding the line...\n");
			}
			else if (subString == "# " || subString == "##" || subString == "\n" || subString == "") { }
		}
	}
	else
		printf("Failed to open file... Wrong path probably");

	_hashTable.clear();

	std::cout << mesh.points[12].position.x << ", " << mesh.points[12].position.y << ", " << mesh.points[12].position.z << std::endl;
	std::cout << mesh.points[12].texcoord.x << ", " << mesh.points[12].texcoord.y << std::endl;
	std::cout << mesh.points[12].normal.x << ", " << mesh.points[12].normal.y << ", " << mesh.points[12].normal.z << std::endl;

	std::cout << mesh.points[13].position.x << ", " << mesh.points[13].position.y << ", " << mesh.points[13].position.z << std::endl;
	std::cout << mesh.points[13].texcoord.x << ", " << mesh.points[13].texcoord.y << std::endl;
	std::cout << mesh.points[13].normal.x << ", " << mesh.points[13].normal.y << ", " << mesh.points[13].normal.z << std::endl << std::endl;

	std::cout << mesh.points[14].position.x << ", " << mesh.points[14].position.y << ", " << mesh.points[14].position.z << std::endl;
	std::cout << mesh.points[14].texcoord.x << ", " << mesh.points[14].texcoord.y << std::endl;
	std::cout << mesh.points[14].normal.x << ", " << mesh.points[14].normal.y << ", " << mesh.points[14].normal.z << std::endl << std::endl;

	std::cout << mesh.points[15].position.x << ", " << mesh.points[15].position.y << ", " << mesh.points[15].position.z << std::endl;
	std::cout << mesh.points[15].texcoord.x << ", " << mesh.points[15].texcoord.y << std::endl;
	std::cout << mesh.points[15].normal.x << ", " << mesh.points[15].normal.y << ", " << mesh.points[15].normal.z << std::endl << std::endl;

	return mesh;
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


auto	ObjParser::_GetFaceData(std::string* s) -> std::string
{
	size_t token = s->find(" ");
	std::string ret = s->substr(0, token);
	s->erase(0, token + 1);
	return ret;
}


auto ObjParser::_FindIndex(const Mesh& mesh, const Vertex& vertex) -> unsigned short
{
	auto	it = std::find_if(mesh.points.begin(), mesh.points.end(), [vertex](const Vertex& v){
		return (v.position == vertex.position && v.texcoord == vertex.texcoord && v.normal == vertex.normal);
	});
	size_t index = std::distance(mesh.points.begin(), it);
	if (index == mesh.points.size())
		return -1;
	else
		return (unsigned short)index;
}


auto	ObjParser::_AddVertex(Mesh* mesh, Vertex v) -> void
{
	long long hash = ObjParser::_GenerateVertexHash(v);

	std::unordered_map<long long, const Vertex&>::const_iterator it = ObjParser::_hashTable.find(hash);

	if (it != _hashTable.end())
	{
		mesh->indices.push_back(ObjParser::_FindIndex(*mesh, it->second));
	}
	else
	{
		_hashTable.emplace(hash, v);
		mesh->points.push_back(v);
		mesh->indices.push_back(ObjParser::_FindIndex(*mesh, v));
	}
}


auto	ObjParser::_GenerateVertexHash(const Vertex& v) -> long long
{
	return (
		v.position.x * 3000000 + 
		v.position.y * -20000 +
		v.position.z * 9 +
		v.texcoord.x * -81 +
		v.texcoord.y * 1050 +
		v.normal.x * -16 +
		v.normal.y * 150 +
		v.normal.z * -4
	);
}


} // OpenGL