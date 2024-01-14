#pragma once
#pragma warning(disable : 4201)
#include "Context/GLFWContext.h"
#include "OpenGl/Shader.h"

namespace Renderer::GL {

	// Seems concepts are not working with variadic template constructors...
	template<class T>
	concept ShaderTy = std::is_same_v<Shader, T>;

	template<typename T>
	concept Uniform1 =
		std::is_same_v<bool, T> ||
		std::is_same_v<int, T> ||
		std::is_same_v<float, T>;

	class Program {
	public:
		Program();

		Program(const Program& other) : id(other.id) {}

		Program(const Shader& vs, const Shader& fs);
		void AttachShader(const Shader& shader)const;

		void LinkProgram()const;
		void UseProgram()const;

		void SetUniform1(std::string_view name, float value) const;
		void SetUniform1i(std::string_view name, int value) const;

		void SetUniformMatrix4(std::string_view name, const mat4& value);
	private:
		GlProgramId id;
	};
}