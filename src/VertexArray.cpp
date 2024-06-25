#include <VertexArray.h>


VertexArray::VertexArray()
{
	this->count = 0;

	glGenVertexArrays(1, &this->ID);
	glBindVertexArray(this->ID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &this->ID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(this->ID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(VertexBuffer* buffer, VertexBufferLayout* layout)
{
	// Bind Vertex Buffer
	buffer->Bind();

	// Vector of attributes
	const std::vector<VertexBufferElement>* vector = layout->GetElements();

	for (unsigned int i = 0, n = vector->size(); i < n; i++)
	{
		// Assign Vertex Attributes
		VertexBufferElement data = vector->at(i);
		glVertexAttribPointer(i, data.count, data.type, data.normalize, layout->GetCount() * sizeof(float), (void*)(data.offset * sizeof(float)));
		glEnableVertexAttribArray(i);
	}
}

void VertexArray::SetCount(unsigned int count)
{
	this->count = count;
}

unsigned int VertexArray::GetCount() const
{
	return this->count;
}