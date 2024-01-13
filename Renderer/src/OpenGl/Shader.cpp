#include "OpenGL/Shader.h"
#include "Core/RenderAssert.h"
#include <fstream>
#ifdef RENDERER_DEBUG
#include <iostream>
#endif // DEBUG

Renderer::GL::Shader::Shader(std::filesystem::path filePath, OpenGLUtils::Shader::Type type)
{
	auto contents = ReadShaderFromFile(filePath);
	RenderAssert(contents, contents.error().c_str());
	SetShaderCode(*contents, type);
	Compile();
}

Renderer::GL::Shader::Shader(std::string_view contents, OpenGLUtils::Shader::Type type)
{
	SetShaderCode(contents, type);
	Compile();
}

Renderer::GL::Shader::operator GLShaderId() const noexcept
{
	RenderAssert(shaderId > 0, "Trying to get an unitialized shader info");
	return shaderId;
}

void Renderer::GL::Shader::SetShaderCode(std::string_view contents, OpenGLUtils::Shader::Type type)
{
	const auto glShaderType = OpenGLUtils::EnumToGLEnum(type);
	const char* data = contents.data();

	shaderId = glCreateShader(glShaderType);
	glShaderSource(shaderId, 1, &data, NULL);
}

std::expected<std::string, std::string> Renderer::GL::Shader::ReadShaderFromFile(const std::filesystem::path& filePath)
{
	std::ifstream file(filePath.c_str());
	if (!file.is_open())
	{
		return std::unexpected<std::string>(std::format("Could not open file shader file"));
	}
	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return content;

}

void Renderer::GL::Shader::Compile()
{
	glCompileShader(shaderId);

#ifdef RENDERER_DEBUG
	char logBuffer[500] = {};
	int size = 0;
	glGetShaderInfoLog(shaderId, 500, &size, &logBuffer[0]);
	std::string_view log = (size > 0) ? std::string_view{ logBuffer } : std::string_view{ "Compiled succesfully" };
	std::cout << "Shader " << shaderId << " log: " << std::endl << log << std::endl;
#endif // DEBUG

}
