#include <Texture.h>

#include <iostream>
#include <stb/stb_image.h>

Texture::Texture(const char* TexturePath)
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load(TexturePath, &width, &height, &nrChannels, 0);
	
	GLuint texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLenum format = GL_RGB;
	switch (nrChannels)
	{
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;
	}

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "[*] Failed to load texture: " << TexturePath << std::endl;
	}
	stbi_image_free(data);

	//glBindTexture(GL_TEXTURE_2D, 0);

	this->id = texture;
}

Texture::~Texture(void)
{
	glDeleteTextures(1, &this->id);
}

void Texture::Bind(GLenum TextureUnit)
{
	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_2D, this->id);
}