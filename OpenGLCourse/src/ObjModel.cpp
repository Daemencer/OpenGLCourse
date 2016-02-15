#include "ObjModel.hpp"

#include "objload.h"
//#include "ObjParser.hpp"

namespace OpenGL {


auto	ObjModel::Initialize(const std::string& modelPath) -> void
{
	//Mesh	obj = ObjParser::ParseObj(modelPath);
	obj::Model obj = obj::loadModelFromFile(modelPath);

	//std::vector<float> positions;
	//std::vector<float> texcoords;
	//std::vector<float> normals;

	//for (int i = 0; i < obj.faces.size(); ++i)
	//{
	//	positions.push_back(obj.points[i].position.x);
	//	positions.push_back(obj.points[i].position.y);
	//	positions.push_back(obj.points[i].position.z);

	//	texcoords.push_back(obj.points[i].texcoord.x);
	//	texcoords.push_back(obj.points[i].texcoord.y);

	//	normals.push_back(obj.points[i].normal.x);
	//	normals.push_back(obj.points[i].normal.y);
	//	normals.push_back(obj.points[i].normal.z);
	//}

	//std::vector<unsigned short> indices;
	//for (int i = 0; i < obj.indices.size(); ++i)
	//	indices.push_back(obj.indices[i]);

	_positions.insert(_positions.begin(), obj.vertex.data(), obj.vertex.data() + obj.vertex.size());
	_posisitionCount = _positions.size();

	_texcoords.insert(_texcoords.begin(), obj.texCoord.data(), obj.texCoord.data() + obj.texCoord.size());
	_texcoordCount = _texcoords.size();

	_normals.insert(_normals.begin(), obj.normal.data(), obj.normal.data() + obj.normal.size());
	_normalCount = _normals.size();

	_indices.insert(_indices.begin(), obj.faces.at("default").data(), obj.faces.at("default").data() + obj.faces.at("default").size());
	_indexCount = _indices.size();

	Model::Initialize();
}


} // OpenGL