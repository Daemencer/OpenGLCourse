#include "Textures.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"

namespace OpenGL {


auto	Textures::CreateTexture(const std::string& name, bool forceAlpha) -> GLuint
{
	int w, h, depth;
	auto* data = stbi_load(name.c_str()
						   , &w, &h, &depth
						   , forceAlpha ? 4 : 3);

	if (data)
	{
		GLuint texId = 0;
		glGenTextures(1, &texId);
		glBindTexture(GL_TEXTURE_2D, texId);

		glTexImage2D(GL_TEXTURE_2D
					 , 0
					 , GL_RGBA8
					 , w
					 , h
					 , 0
					 , forceAlpha ? GL_RGBA : GL_RGB
					 , GL_UNSIGNED_BYTE
					 , data);

		// alternative to glTexImage2d
		glTexStorage2D(GL_TEXTURE_2D
					   , 1
					   , GL_RGBA8
					   , w
					   , h);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
		stbi_image_free(data);

		return texId;
	}

	return 0;
}


}