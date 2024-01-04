#include "OpenGL/Shader.h"
#include "Core/RenderAssert.h"
#ifdef RENDERER_DEBUG
#include <iostream>
#endif // DEBUG

Renderer::GL::Shader::Shader(std::filesystem::path filePath, OpenGLUtils::Shader::Type type)
    : Shader(std::string_view(ReadShaderFromFile(filePath)), type)
{
}

Renderer::GL::Shader::Shader(std::string_view contents, OpenGLUtils::Shader::Type type)
{
    const auto glShaderType = OpenGLUtils::EnumToGLEnum(type);
    const char* data = contents.data();

    shaderId = glCreateShader(glShaderType);
    glShaderSource(shaderId, 1, &data, NULL);
    Compile();
}

Renderer::GL::Shader::operator GLShaderId() const noexcept
{
    RenderAssert(shaderId > 0, "Trying to get an unitialized shader info");
    return shaderId;
}

std::string Renderer::GL::Shader::ReadShaderFromFile(const std::filesystem::path& /*filePath*/)
{
    return std::string();
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
