#pragma once

#include <glad/glad.h>


class Texture
{
public:
	Texture(const char *texture);
	~Texture(void);

	void Bind(GLenum TextureUnit);
private:
	GLuint id;
};