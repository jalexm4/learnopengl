#pragma once

#include <glm/glm.hpp>

#include <ElementBuffer.h>
#include <VertexArray.h>
#include <Shader.h>


class Renderer
{
public:
	Renderer(glm::vec3 drawColour, unsigned int renderFlags);
	//~Renderer();

	void UpdateDeltaTime();
	float GetDeltaTime();

	void Clear() const; 
	void Draw(const VertexArray *VAO, const ElementBuffer *EBO, const Shader *shader);
private:
	unsigned int renderFlags;

	float deltaTime;
	float lastFrame;
};