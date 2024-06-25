#pragma once

#include <string>
#include <unordered_map>
#include <glad/glad.h>
#include <glm/glm.hpp>

//TODO: Template SetUniform

class Shader
{
public:
	Shader(const char* VertexPath, const char* FragmentPath);
	~Shader();

	void Bind() const;
	void Unbind();

	int GetUniformLocation(std::string name);
	void SetUniform1i(std::string name, int value);
	void SetUniformMatrix(std::string name, glm::mat4 matrix);	// Only using a 4x4 Matrix (for now).
private:
	GLuint id;
	std::unordered_map<std::string, int> UniformLocationCache;

	std::string ReadFile(const char* file);
	GLuint CompileProgram(GLuint vertex, GLuint fragment);
	GLuint CompileShader(const char *ShaderSource, GLenum ShaderType);
};