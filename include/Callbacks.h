#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <Camera.h>
#include <Mouse.h>

// Pointer to a struct containing pointers to needed objects from inside callbacks
struct CallbackPointers{
	bool* keys;
	Mouse* mouse;
	Camera* camera;
};

//TODO: Windows Refresh Callback
// Callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);