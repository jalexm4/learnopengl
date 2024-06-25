#pragma once

#include <glm/glm.hpp>
#include <Mouse.h>


class Camera
{
public:
	Camera();
	//~Camera();

	void UpdateView();
	glm::mat4 GetView();

	void KeysUpdate(bool* keys, float deltaTime);
	void MouseUpdate(Mouse* mouse);

private:
	glm::mat4 view;
	glm::mat4 projection;

	float speed;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
};