#pragma once 
#include "OpenGl/OpenGLUtils.h"
#include "Structures/RawBuffer.h"

namespace Renderer::GL {

	namespace Internal {
		class OpenGlBufferBase {
		public:
			// Generates a new buffer using glGenBuffers
			OpenGlBufferBase();

			/*
			* Generates a new buffer using glGenBuffers and binds it
			* @param Buffer type to bind it
			*/
			OpenGlBufferBase(OpenGLUtils::Buffer::BufferType type);

			/*
			* Generates a new buffer using glGenBuffers and binds it using the same type
			*/
			OpenGlBufferBase(const OpenGlBufferBase& o) noexcept;
			OpenGlBufferBase& operator=(const OpenGlBufferBase& o) noexcept;

			/*
			* Generates a new buffer using glGenBuffers and binds it using the same type
			*/
			OpenGlBufferBase(OpenGlBufferBase&& o) noexcept;
			OpenGlBufferBase& operator=(OpenGlBufferBase&& o) noexcept;

			// Destroys the buffer using: glDeleteBuffers
			~OpenGlBufferBase() noexcept;

			/*
			* Binds the buffer object.
			* @param Buffer type to bind
			*/
			void Bind(OpenGLUtils::Buffer::BufferType type);
			inline bool operator==(const OpenGlBufferBase& other)const noexcept;
		private:
			void GenerateBuffer();
			void BindBuffer(OpenGLUtils::Buffer::BufferType type);

		private:
			GLBufferId mBufferID;
			OpenGLUtils::Buffer::BufferType mType;
		};
	}

	template<typename ... T>
	class OpenGlBuffer : public Internal::OpenGlBufferBase, public Renderer::MultiTypeBuffer<T...> {};
}