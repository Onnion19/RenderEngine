#pragma once

#include "Context/GLFWContext.h"
#include "OpenGl/OpenGLUtils.h"
#include <string_view>
#include <filesystem>
#include <expected>
namespace Renderer::GL {

	class Shader {
	public:
		Shader(std::filesystem::path filePath, OpenGLUtils::Shader::Type type);
		Shader(std::string_view contents, OpenGLUtils::Shader::Type type);
		operator GLShaderId()const noexcept;
	private:
		void SetShaderCode(std::string_view contents, OpenGLUtils::Shader::Type type);
		std::expected<std::string, std::string> ReadShaderFromFile(const std::filesystem::path& filePath);
		void Compile();
	private:
		GLShaderId shaderId;
	};
}