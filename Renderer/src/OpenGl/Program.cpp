#include "Opengl/Program.h"

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
