#include "OpenGl/Buffer.h"
#include "Core/RenderAssert.h"

namespace Renderer::GL::Internal {

	OpenGlBufferBase::OpenGlBufferBase()
	{
		GenerateBuffer();
	}

	OpenGlBufferBase::OpenGlBufferBase(OpenGLUtils::Buffer::BufferType type)
	{
		GenerateBuffer();
		Bind(type);
	}

	OpenGlBufferBase::OpenGlBufferBase(const OpenGlBufferBase& o) noexcept
	{
		GenerateBuffer();
		Bind(o.mType);
	}

	OpenGlBufferBase& OpenGlBufferBase::operator=(const OpenGlBufferBase& o) noexcept
	{
		GenerateBuffer();
		Bind(o.mType);
		return *this;
	}

	OpenGlBufferBase::OpenGlBufferBase(OpenGlBufferBase&& o) noexcept
	{
		GenerateBuffer();
		Bind(o.mType);
	}

	OpenGlBufferBase& OpenGlBufferBase::operator=(OpenGlBufferBase&& o) noexcept
	{
		GenerateBuffer();
		Bind(o.mType);
		return *this;
	}

	void OpenGlBufferBase::Bind(OpenGLUtils::Buffer::BufferType type)
	{
		mType = type;
		BindBuffer(type);
	}

	inline bool OpenGlBufferBase::operator==(const OpenGlBufferBase& other) const noexcept
	{
		RenderAssert(mBufferID == other.mBufferID, "It should not be possible to have multiple buffers with the same ID");
		return mBufferID == other.mBufferID;
	}

	OpenGlBufferBase::~OpenGlBufferBase() noexcept
	{
		if (mBufferID != 0) {
			glDeleteBuffers(1, &mBufferID);
		}
	}


	/////////////////////////////////////////////////////////////////////////////

	void OpenGlBufferBase::GenerateBuffer()
	{
		RenderAssert(mBufferID > 0, "Trying to generate an already generated buffer");
		glGenBuffers(1, &mBufferID);
	}

	void OpenGlBufferBase::BindBuffer(OpenGLUtils::Buffer::BufferType type)
	{
		glBindBuffer(BufferTypeToOpenglEnum(type), mBufferID);
	}
}