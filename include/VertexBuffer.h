#pragma once

#include <glad/glad.h>


class VertexBuffer
{
public:
	VertexBuffer(const float *data, unsigned int size);
	~VertexBuffer();

	void Bind();
	void Unbind();
private:
	GLuint ID;
};