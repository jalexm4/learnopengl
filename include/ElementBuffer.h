#pragma once

#include <glad/glad.h>


class ElementBuffer
{
public:
	ElementBuffer(const unsigned int* data, unsigned int count);
	~ElementBuffer();

	void Bind() const;
	void Unbind();

	GLuint GetCount() const;
private:
	GLuint ID;
	unsigned int indices;
};