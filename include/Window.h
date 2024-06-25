#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>


class Window
{
public:
	Window(unsigned int width, unsigned int height, const char* title);
	~Window();

	float GetWidth();
	float GetHeight();
	GLFWwindow* GetWindow();

	void Present();

private:
	GLFWwindow* window;
	unsigned int width, height;
};