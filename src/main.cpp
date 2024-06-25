//
// LearnOpenGL
//

//#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <Callbacks.h>
#include <Camera.h>
#include <ElementBuffer.h>
#include <Mouse.h>
#include <Renderer.h>
#include <Shader.h>
#include <Texture.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <Window.h>


int main(int argc, char** argv)
{
	Window window(1280, 720, "Breakout");

	bool keys[512] = { false };
	
	Mouse mouse = { 0 };
	mouse.firstMouse = true;
	mouse.lastX = window.GetWidth() / 2.0f;
	mouse.lastY = window.GetHeight() / 2.0f;
	mouse.sensitivity = 0.1f;
	mouse.yaw = -90.0f;
	mouse.pitch = 0.0f;

	// 3D cube
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	// Positions of the 10 3D cubes
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	VertexArray VAO;
	VertexBuffer VBO(vertices, sizeof(vertices));
	
	VertexBufferLayout layout;
	layout.Push(3);
	layout.Push(2);

	VAO.AddBuffer(&VBO, &layout);
	VAO.SetCount(36);

	VBO.Unbind();
	VAO.Unbind();

	Texture texture1("assets/container.jpg");
	Texture texture2("assets/face.png");

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), window.GetWidth() / window.GetHeight(), 0.1f, 100.0f);

	Shader shader("shaders/cube.vs", "shaders/cube.frag");
	shader.Bind();
	
	shader.SetUniform1i("texture1", 0);
	shader.SetUniform1i("texture2", 1);

	shader.SetUniformMatrix("projection", projection);

	shader.Unbind();

	texture1.Bind(GL_TEXTURE0);
	texture2.Bind(GL_TEXTURE1);

	Renderer renderer(glm::vec3(0.2f, 0.3f, 0.3f), GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Camera camera;

	// Pointers to objects needed in GLFW callback functions. Only touch from inside a callback.
	CallbackPointers callbackPointers = { 0 };
	callbackPointers.keys = keys;
	callbackPointers.mouse = &mouse;
	callbackPointers.camera = &camera;

	glfwSetWindowUserPointer(window.GetWindow(), &callbackPointers);

	// Vsync - User can override
	//glfwSwapInterval(1);

	// --- Game Loop ---f
	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		renderer.UpdateDeltaTime();

		glfwPollEvents();

		camera.KeysUpdate(keys, renderer.GetDeltaTime());

		renderer.Clear();

		camera.UpdateView();
		shader.Bind();
		shader.SetUniformMatrix("view", camera.GetView());

		for (unsigned int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.SetUniformMatrix("model", model);

			renderer.Draw(&VAO, nullptr, &shader);
		}

		// Switch front and back buffer
		window.Present();
	}

	return 0;
}