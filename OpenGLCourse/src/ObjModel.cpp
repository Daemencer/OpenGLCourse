#include "ObjModel.hpp"

#include "ObjParser.hpp"

namespace OpenGL {


auto	ObjModel::Initialize(const std::string& modelPath) -> void
{
	Mesh	obj = ObjParser::ParseObj(modelPath);

	std::vector<float> positions;
	std::vector<float> texcoords;
	std::vector<float> normals;

	for (int i = 0; i < obj.points.size(); ++i)
	{
		positions.push_back(obj.points[i].position.x);
		positions.push_back(obj.points[i].position.y);
		positions.push_back(obj.points[i].position.z);

		texcoords.push_back(obj.points[i].texcoord.x);
		texcoords.push_back(obj.points[i].texcoord.y);

		normals.push_back(obj.points[i].normal.x);
		normals.push_back(obj.points[i].normal.y);
		normals.push_back(obj.points[i].normal.z);
	}

	std::vector<unsigned short> indices;
	for (int i = 0; i < obj.indices.size(); ++i)
		indices.push_back(obj.indices[i]);

	_positions.insert(_positions.begin(), positions.data(), positions.data() + positions.size());
	_posisitionCount = _positions.size();

	_texcoords.insert(_texcoords.begin(), texcoords.data(), texcoords.data() + texcoords.size());
	_texcoordCount = _texcoords.size();

	_normals.insert(_normals.begin(), normals.data(), normals.data() + normals.size());
	_normalCount = _normals.size();

	_indices.insert(_indices.begin(), indices.data(), indices.data() + indices.size());
	_indexCount = _indices.size();

	Model::Initialize();
}


} // OpenGL