#include <Renderer.h>

#include <glad/glad.h>
#include <glfw/glfw3.h>


Renderer::Renderer(glm::vec3 drawColour, unsigned int renderFlags)
{
	// Set OpenGL Clear colour. Change to store draw colour if its going to be changing
	glClearColor(drawColour.x, drawColour.y, drawColour.z, 1.0f);
	
	
	this->renderFlags = renderFlags;

	this->deltaTime = 0.0f;
	this->lastFrame = 0.0f;
}

void Renderer::UpdateDeltaTime()
{
	float currentFrame = glfwGetTime();
	
	this->deltaTime = currentFrame - this->lastFrame;
	this->lastFrame = currentFrame;
}

float Renderer::GetDeltaTime()
{
	return this->deltaTime;
}

void Renderer::Clear() const
{
	//glClearColor(this->drawColour.x, this->drawColour.y, this->drawColour.z, 1.0f);
	glClear(this->renderFlags);
}

void Renderer::Draw(const VertexArray* VAO, const ElementBuffer* EBO, const Shader* shader)
{
	shader->Bind();
	VAO->Bind();
	
	if (EBO)
	{
		// Use indices to draw if provided
		glDrawElements(GL_TRIANGLES, EBO->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, VAO->GetCount());
	}
}