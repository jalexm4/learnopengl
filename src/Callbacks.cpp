#include <Callbacks.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	// Pointer to a struct containing pointers to needed objects from inside callbacks
	CallbackPointers *callbackPointers = static_cast<CallbackPointers *>(glfwGetWindowUserPointer(window));
	bool* keys = callbackPointers->keys;

	// Set pressed/unpressed keys
	if (key >= 0 && key < 512)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	// Pointer to a struct containing pointers to needed objects from inside callbacks
	CallbackPointers* callbackPointers = static_cast<CallbackPointers*>(glfwGetWindowUserPointer(window));
	Mouse* mouse = callbackPointers->mouse;
	Camera* camera = callbackPointers->camera;

	if (mouse->firstMouse)
	{
		mouse->lastX = xpos;
		mouse->lastY = ypos;
		mouse->firstMouse = false;
	}

	float xoffset = xpos - mouse->lastX;
	float yoffset = mouse->lastY - ypos;
	mouse->lastX = xpos;
	mouse->lastY = ypos;

	xoffset *= mouse->sensitivity;
	yoffset *= mouse->sensitivity;

	mouse->yaw += xoffset;
	mouse->pitch += yoffset;

	if (mouse->pitch > 89.0f)
	{
		mouse->pitch = 89.0f;
	}
	else if (mouse->pitch < -89.0f)
	{
		mouse->pitch = -89.0f;
	}

	// Call camera mouse update
	camera->MouseUpdate(mouse);
}