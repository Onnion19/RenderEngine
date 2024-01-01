#include "OpenGl/Buffer.h"
#include "Core/RenderAssert.h"

namespace Renderer::GL {

	namespace Internal {
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

		void OpenGlBufferBase::Unbind()
		{
			RenderAssert(mBufferID > 0, "Invalid buffer id");
			glBindBuffer(EnumToGLEnum(mType), 0);
		}

		inline bool OpenGlBufferBase::operator==(const OpenGlBufferBase& other) const noexcept
		{
			RenderAssert(mBufferID == other.mBufferID, "It should not be possible to have multiple buffers with the same ID");
			return mBufferID == other.mBufferID;
		}

		OpenGlBufferBase::~OpenGlBufferBase() noexcept
		{
			glDeleteBuffers(1, &mBufferID);
		}

		GLBufferId OpenGlBufferBase::GetID() const
		{
			return mBufferID;
		}

		/////////////////////////////////////////////////////////////////////////////

		void OpenGlBufferBase::GenerateBuffer()
		{
			RenderAssert(mBufferID <= 0, "Trying to generate an already generated buffer");
			glGenBuffers(1, &mBufferID);
		}
	}
	IndexBuffer::IndexBuffer() noexcept
		: OpenGlBufferBase(OpenGLUtils::Buffer::BufferType::ELEMENT_ARRAY)
	{
	}

	IndexBuffer::~IndexBuffer()
	{
	}

	void IndexBuffer::SendDataGPU(OpenGLUtils::Buffer::BufferUsage usage)
	{
		const auto& containerByteSize = buffer.size() * sizeof(Type);
		const auto& GlBufferType = EnumToGLEnum(mType);
		const auto& GlBufferUsage = EnumToGLEnum(usage);
		//Send all the buffer chunk to the GPU :D 
		Bind();
		glBufferData(GlBufferType, containerByteSize, buffer.data(), GlBufferUsage);

	} 
	void IndexBuffer::AddIndex(uint32 indice)
	{
		buffer.push_back(indice);
	}
	void IndexBuffer::RemoveIndexAt(std::size_t position)
	{
		iter it = buffer.begin();
		std::advance(it, position);
		RemoveIndexAt(it);
	}
	void IndexBuffer::RemoveIndexAt(iter it)
	{
		buffer.erase(it);
	}
	void IndexBuffer::RemoveIndicesAt(iter begin, iter end)
	{
		buffer.erase(begin, end);
	}

	IndexBuffer::iter IndexBuffer::begin()
	{
		return buffer.begin();
	}
	IndexBuffer::const_iter IndexBuffer::begin() const
	{
		return buffer.begin();
	}
	IndexBuffer::iter IndexBuffer::end()
	{
		return buffer.end();
	}
	IndexBuffer::const_iter IndexBuffer::end() const
	{
		return buffer.end();
	}

	std::size_t IndexBuffer::size() const noexcept
	{
		return buffer.size();
	}
	bool IndexBuffer::empty() const noexcept
	{
		return buffer.empty();
	}
}