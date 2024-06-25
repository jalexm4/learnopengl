#pragma once

#include <glad/glad.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>


class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddBuffer(VertexBuffer* buffer, VertexBufferLayout* layout);
	void SetCount(unsigned int count);
	unsigned int GetCount() const;
private:
	GLuint ID;
	unsigned int count;
};