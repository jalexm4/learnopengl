#include <Shader.h>

#include <iostream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* VertexPath, const char* FragmentPath)
{
	// Reads Vertex and Fragment Shader from file to memory
	std::string VertexSource = ReadFile(VertexPath);
	std::string FragmentSource = ReadFile(FragmentPath);

	// Compile Shaders
	GLuint VertexShader = CompileShader(VertexSource.c_str(), GL_VERTEX_SHADER);
	GLuint FragmentShader = CompileShader(FragmentSource.c_str(), GL_FRAGMENT_SHADER);
	
	// Link into Shader Program
	this->id = CompileProgram(VertexShader, FragmentShader);

	// Individual Shaders are no longer needed
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(this->id);
}

void Shader::Bind() const
{
	glUseProgram(this->id);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

int Shader::GetUniformLocation(std::string name)
{
	// Check if the uniform is in the uniform lookup cache.
	if (this->UniformLocationCache.find(name) != this->UniformLocationCache.end())
	{
		return this->UniformLocationCache[name];
	}

	// Find uniform location and place into cache
	int loc = glGetUniformLocation(this->id, name.c_str());
	this->UniformLocationCache[name] = loc;

	return loc;
}

void Shader::SetUniform1i(std::string name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniformMatrix(std::string name, glm::mat4 matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

std::string Shader::ReadFile(const char* file)
{
	std::ifstream File(file);

	File.seekg(0, std::ios::end);
	const size_t length = File.tellg();
	File.seekg(0);

	std::string buffer(length, ' ');
	File.read(&buffer[0], length);

	return buffer;
}

GLuint Shader::CompileProgram(GLuint VertexShader, GLuint FragmentShader)
{
	GLuint ShaderProgram = glCreateProgram();
	
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);

	int success;
	char infoLog[512];

	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ShaderProgram, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}

	return ShaderProgram;
}

GLuint Shader::CompileShader(const char* ShaderSource, GLenum ShaderType)
{
	GLuint shader = glCreateShader(ShaderType);
	glShaderSource(shader, 1, &ShaderSource, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}

	return shader;
}