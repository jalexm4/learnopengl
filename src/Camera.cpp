#include <Camera.h>

#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera()
{
	this->speed = 3.0f;

	this->view = glm::mat4(1.0f);
	this->projection = glm::mat4(1.0f);

	this->position = glm::vec3(0.0f, 0.0f, 3.0f);
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::UpdateView()
{
	this->view = glm::lookAt(this->position, (this->position + this->front), this->up);
}

glm::mat4 Camera::GetView()
{
	return this->view;
}

void Camera::KeysUpdate(bool *keys, float deltaTime)
{
	float speed = this->speed * deltaTime;
	
	if (keys[GLFW_KEY_W])
	{
		this->position += speed * this->front;
	}
	if (keys[GLFW_KEY_S])
	{
		this->position -= speed * this->front;
	}
	if (keys[GLFW_KEY_A])
	{
		this->position -= glm::normalize(glm::cross(this->front, this->up)) * speed;
	}
	if (keys[GLFW_KEY_D])
	{
		this->position += glm::normalize(glm::cross(this->front, this->up)) * speed;
	}
}

void Camera::MouseUpdate(Mouse *mouse)
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(mouse->yaw)) * cos(glm::radians(mouse->pitch));
	direction.y = sin(glm::radians(mouse->pitch));
	direction.z = sin(glm::radians(mouse->yaw)) * cos(glm::radians(mouse->pitch));
	
	this->front = glm::normalize(direction);
}