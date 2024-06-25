#include <ElementBuffer.h>


ElementBuffer::ElementBuffer(const unsigned int* data, unsigned int count)
{
	this->indices = count;

	glGenBuffers(1, &this->ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &this->ID);
}

void ElementBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
}

void ElementBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint ElementBuffer::GetCount() const
{
	return this->indices;
}