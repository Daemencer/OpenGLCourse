#include "CubeModel.hpp"

namespace OpenGL {


auto	CubeModel::Initialize() -> void
{
	// set the positions and stuff
	float pos[] = {
		// front face
		-0.5f, 0.5f, 0.5f,		// v0
		-0.5f, -0.5f, 0.5f,		// v1
		0.5f, -0.5f, 0.5f,		// v2
		0.5f, 0.5f, 0.5f,		// v3
		// right face
		0.5f, 0.5f, 0.5f,		// v4
		0.5f, -0.5f, 0.5f,		// v5
		0.5f, -0.5f, -0.5f,		// v6
		0.5f, 0.5f, -0.5f,		// v7
		// back face
		0.5f, 0.5f, -0.5f,		// v8
		0.5f, -0.5f, -0.5f,		// v9
		-0.5f, -0.5f, -0.5f,	// v10
		-0.5f, 0.5f, -0.5f,		// v11
		// left face
		-0.5f, 0.5f, -0.5f,		// v12
		-0.5f, -0.5f, -0.5f,	// v13
		-0.5f, -0.5f, 0.5f,		// v14
		-0.5f, 0.5f, 0.5f,		// v15
		// top face
		-0.5f, 0.5f, -0.5f,		// v16
		-0.5f, 0.5f, 0.5f,		// v17
		0.5f, 0.5f, 0.5f,		// v18
		0.5f, 0.5f, -0.5f,		// v19
		// bottom face
		-0.5f, -0.5f, 0.5f,		// v20
		-0.5f, -0.5f, -0.5f,	// v21
		0.5f, -0.5f, -0.5f,		// v22
		0.5f, -0.5f, 0.5f		// v23
	};

	float texcoords[] = {
		// front face
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		// right face
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		// back face
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		// left face
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		// top face
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		// bottom face
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	float normals[] = {
		// front face
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		// right face
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		// back face
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		// left face
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		// top face
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		// bottom face
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f
	};

	unsigned short indices[] = {
		// front face
		0, 1, 2,
		0, 2, 3,
		// right face
		4, 5, 6,
		4, 6, 7,
		// back face
		8, 9, 10,
		8, 10, 11,
		// left face
		12, 13, 14,
		12, 14, 15,
		// top face
		16, 17, 18,
		16, 18, 19,
		// bottom face
		20, 21, 22,
		20, 22, 23
	};

	_positions.insert(_positions.begin(), pos, pos + 24 * 3);
	_texcoords.insert(_texcoords.begin(), texcoords, texcoords + 24 * 2);
	_normals.insert(_normals.begin(), normals, normals + 24 * 3);

	_indices.insert(_indices.begin(), indices, indices + 12 * 3);

	Model::Initialize();
}


} // OpenGL