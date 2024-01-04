#pragma once

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

		template<typename ... Args>
		Program(Args&& ... shaders) {
			id = glCreateProgram();
			(AttachShader(shaders), ...);
		}
		void AttachShader(const Shader& shader)const;

		void LinkProgram()const;
		void operator()()const;

		// Uniforms
		template<Uniform1 Ty>
		void SetUniform1(std::string_view name, Ty&& value) const
		{
			glUniform1f(glGetUniformLocation(id, name.data()), value);
		}

	private:
		GlProgramId id;
	};
}