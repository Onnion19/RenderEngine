#include "Opengl/Program.h"
#include <gtc/type_ptr.hpp>
Renderer::GL::Program::Program()
{
	id = glCreateProgram();
}

void Renderer::GL::Program::AttachShader(const Shader& shader)const
{
	glAttachShader(id, shader);
}

void Renderer::GL::Program::LinkProgram()const
{
	glLinkProgram(id);

#ifdef RENDERER_DEBUG
	char infoLog[512];
	int success;
	// print linking errors if any
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED: " << id << "\n\t" << infoLog << std::endl;
	}
	else
	{
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_SUCCESS: " << id << std::endl;
	}
#endif
}

void Renderer::GL::Program::operator()()const
{
	glUseProgram(id);
}

void Renderer::GL::Program::SetUniform1(std::string_view name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name.data()), value);
}

void Renderer::GL::Program::SetUniformMatrix4(std::string_view name, const mat4& value)
{
	auto uniformPos = glGetUniformLocation(id, name.data());
	RenderAssert(uniformPos > -1, "Trying to sent an invalid uniform for shader");
	glUniformMatrix4fv(uniformPos, 1, false, glm::value_ptr(value));
}
