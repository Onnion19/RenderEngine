#pragma once 
#include "OpenGl/OpenGLUtils.h"

namespace Renderer::GL {
	class OpenGlBuffer {
	public:

		// Can't be copied
		OpenGlBuffer(const OpenGlBuffer&) = delete;
		OpenGlBuffer& operator=(const OpenGlBuffer&) = delete;

		// Generates a new buffer using glGenBuffers
		OpenGlBuffer();

		/*
		* Generates a new buffer using glGenBuffers and binds it
		* @param Buffer type to bind it
		*/
		OpenGlBuffer(OpenGLUtils::Buffer::BufferType type);

		OpenGlBuffer(OpenGlBuffer&& o);
		OpenGlBuffer& operator=(OpenGlBuffer&& o);

		// Destroys the buffer using: glDeleteBuffers
		~OpenGlBuffer();

		/*
		* Binds the buffer object.
		* @param Buffer type to bind
		*/
		void Bind(OpenGLUtils::Buffer::BufferType type);

		inline bool operator==(const OpenGlBuffer& other)const;

	private:
		void GenerateBuffer();
		void BindBuffer(OpenGLUtils::Buffer::BufferType type);
	private:
		GLBufferId mBufferID;
	};

}