#include "OpenGl/Buffer.h"
#include "Core/RenderAssert.h"

namespace Renderer::GL {

	OpenGlBuffer::OpenGlBuffer()
	{
		GenerateBuffer();
	}

	OpenGlBuffer::OpenGlBuffer(OpenGLUtils::Buffer::BufferType type)
	{
		GenerateBuffer();
		Bind(type);
	}

	OpenGlBuffer::OpenGlBuffer(OpenGlBuffer&& o)
	{
		mBufferID = o.mBufferID;
		o.mBufferID = 0;

	}

	OpenGlBuffer& OpenGlBuffer::operator=(OpenGlBuffer&& o)
	{
		mBufferID = o.mBufferID;
		o.mBufferID = 0;
		return *this;
	}

	void OpenGlBuffer::Bind(OpenGLUtils::Buffer::BufferType type)
	{
		BindBuffer(type);
	}

	inline bool OpenGlBuffer::operator==(const OpenGlBuffer& other) const
	{
		RenderAssert(mBufferID == other.mBufferID, "It should not be possible to havem ultiple buffers with the same ID");
		return mBufferID == other.mBufferID;
	}

	OpenGlBuffer::~OpenGlBuffer()
	{
		RenderAssert(mBufferID > 0, "Trying to delete an invalid buffer ID. Has it been generated previously?");
		glDeleteBuffers(1, &mBufferID);
	}


	/////////////////////////////////////////////////////////////////////////////

	void OpenGlBuffer::GenerateBuffer()
	{
		RenderAssert(mBufferID <= 0, "Trying to generate an already generated buffer");
		glGenBuffers(1, &mBufferID);
	}

	void OpenGlBuffer::BindBuffer(OpenGLUtils::Buffer::BufferType type)
	{
		glBindBuffer(BufferTypeToOpenglEnum(type), mBufferID);
	}
}