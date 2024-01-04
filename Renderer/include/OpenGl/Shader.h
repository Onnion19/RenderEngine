#pragma once

#include "Core/types.h"
#include "OpenGl/OpenGLUtils.h"
#include "glad/glad.h"
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
		std::string ReadShaderFromFile(const std::filesystem::path& filePath);
		void Compile();
	private:
		GLShaderId shaderId;
	};
}