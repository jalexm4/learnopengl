#include <Window.h>

#include <iostream>
#include <stb/stb_image.h>
#include <Callbacks.h>


Window::Window(unsigned int width, unsigned int height, const char *title)
{
	this->width = width;
	this->height = height;

	// Start GLFW
	glfwInit();

	// OpenGL 4.6 Core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window instance
	this->window = glfwCreateWindow(this->width, this->height, title, NULL, NULL);
	if (!window)
	{
		std::cout << "[*] Failed to create window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	// Setup GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return;
	}

	// Accept mouse input and hide cursor
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Callback functions 
	glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);	// Window resize Event
	glfwSetKeyCallback(this->window, key_callback);								// Keyboard Event
	glfwSetCursorPosCallback(this->window, mouse_callback);						// Mouse Event

	// --- OpenGL Configuration ---
	glViewport(0, 0, this->width, this->height);
	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Flip image on load so OpenGL renders correctly
	stbi_set_flip_vertically_on_load(true);
}

Window::~Window()
{
	glfwTerminate();
}

float Window::GetWidth()
{
	return static_cast<float>(this->width);
}

float Window::GetHeight()
{
	return static_cast<float>(this->height);
}

GLFWwindow* Window::GetWindow()
{
	return this->window;
}

void Window::Present()
{
	glfwSwapBuffers(this->window);
}
