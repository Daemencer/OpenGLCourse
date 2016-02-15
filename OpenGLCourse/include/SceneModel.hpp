#ifndef __SCENE_MODEL_HPP__
#define __SCENE_MODEL_HPP__

#include <vector>
#include <string>
#include "scene.h"

#include "GLShader.hpp"
#include "Mesh.hpp"

namespace OpenGL {


class Model
{
public:
	/*  Functions   */
	Model(const char* path)
	{
		this->loadModel(path);
	}

	void Draw(GLShader* shader);

private:
	/*  Model Data  */
	std::vector<Mesh> meshes;
	std::string directory;

	/*  Functions   */
	void loadModel(std::string path);

	void processNode(aiNode* node, const aiScene* scene);

	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
										 std::string typeName);
};


} // OpenGL

#endif /* __SCENE_MODEL_HPP__ */