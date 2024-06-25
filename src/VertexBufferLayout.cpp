#include <VertexBufferLayout.h>

VertexBufferLayout::VertexBufferLayout()
{
	this->count = 0;
}

void VertexBufferLayout::Push(unsigned int count)
{
	//TODO: Hardcode. Add support for different configurations.

	VertexBufferElement element = {0};
	element.count = count;
	element.type = GL_FLOAT;
	element.normalize = GL_FALSE;

	if (this->elements.size() == 0)
	{
		// First element int the vector should have an offset of 0.
		element.offset = 0;
	}
	else
	{
		element.offset = this->count;
	}

	this->count += count;
	this->elements.push_back(element);
}

const std::vector<VertexBufferElement>* VertexBufferLayout::GetElements() const
{
	return &this->elements;
}

unsigned int VertexBufferLayout::GetCount() const
{
	return this->count;
}