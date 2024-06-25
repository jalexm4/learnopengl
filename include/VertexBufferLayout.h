#pragma once

#include <vector>
#include <glad/glad.h>


struct VertexBufferElement
{
	unsigned int count;
	GLenum type;
	GLenum normalize;
	unsigned int offset;
};

class VertexBufferLayout
{
public:
	VertexBufferLayout();
	//~VertexBufferLayout();

	void Push(unsigned int count);
	const std::vector<VertexBufferElement>* GetElements() const;
	unsigned int GetCount() const;
private:
	std::vector<VertexBufferElement> elements;
	unsigned int count;
};