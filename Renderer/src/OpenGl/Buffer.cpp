#include "OpenGl/Buffer.h"
#include "Core/RenderAssert.h"

namespace Renderer::GL::Internal {


	OpenGlBufferBase::OpenGlBufferBase(OpenGLUtils::Buffer::BufferType type)
	{
		GenerateBuffer();
		mType = type;
	}

	OpenGlBufferBase::OpenGlBufferBase(const OpenGlBufferBase& o) noexcept
	{
		GenerateBuffer();
		mType = o.mType;
	}

	OpenGlBufferBase& OpenGlBufferBase::operator=(const OpenGlBufferBase& o) noexcept
	{
		GenerateBuffer();
		mType = o.mType;
		return *this;
	}

	OpenGlBufferBase::OpenGlBufferBase(OpenGlBufferBase&& o) noexcept
	{
		mBufferID = o.mBufferID;
		o.mBufferID = 0;
		mType = o.mType;
	}

	OpenGlBufferBase& OpenGlBufferBase::operator=(OpenGlBufferBase&& o) noexcept
	{
		mBufferID = o.mBufferID;
		o.mBufferID = 0;
		mType = o.mType;
		return *this;
	}

	void OpenGlBufferBase::Bind()
	{
		glBindBuffer(EnumToGLEnum(mType), mBufferID);
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

	GLBufferId OpenGlBufferBase::GetID() const
	{
		return mBufferID;
	}

	/////////////////////////////////////////////////////////////////////////////

	void OpenGlBufferBase::GenerateBuffer()
	{
		RenderAssert(mBufferID > 0, "Trying to generate an already generated buffer");
		glGenBuffers(1, &mBufferID);
	}
}