#pragma once 
#include "OpenGl/OpenGLUtils.h"
#include "Structures/RawBuffer.h"
#include <algorithm>
#include <type_traits>
struct Test { float x, y; };
namespace Renderer::GL {

	namespace Internal {
		class OpenGlBufferBase {
		public:
			// Generates a new buffer using glGenBuffers
			OpenGlBufferBase() = default;

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
			virtual ~OpenGlBufferBase() noexcept;

			/*
			* Gets the GLuint of the buffer
			*/
			[[nodiscard]] GLBufferId GetID()const;

			/*
			* Binds the buffer object.
			*/
			void Bind();

			/*
			* Unbinds any vbo object
			*/
			void Unbind();

			inline bool operator==(const OpenGlBufferBase& other)const noexcept;
		private:
			void GenerateBuffer();

		protected:
			GLBufferId mBufferID = 0;
			OpenGLUtils::Buffer::BufferType mType;
		};
	}

	template<typename ... T>
	class OpenGlBuffer : public Internal::OpenGlBufferBase, public Renderer::MultiTypeBuffer<T...> {
		using containerType = typename Renderer::MultiTypeBuffer<T...>::bufferTy;
	public:

		OpenGlBuffer() = default;
		OpenGlBuffer(OpenGLUtils::Buffer::BufferType type) : Internal::OpenGlBufferBase(type) {}

		void SendDataGPU(OpenGLUtils::Buffer::BufferUsage usage) {
		
			const auto& container = this->GetContainer();
			const auto& containerByteSize = container.size() * sizeof(containerType);
			const auto& GlBufferType = EnumToGLEnum(mType);
			const auto& GlBufferUsage = EnumToGLEnum(usage);
			Bind();
			//Send all the buffer chunk to the GPU :D 
			glBufferData(GlBufferType, containerByteSize, container.data(), GlBufferUsage);
			Unbind();
		}

		/*
		*  Insert a tuple based range to the buffer.
		*	If buffer is type <int, float, char>
		* the range to insert must be type of: std::tuple<int, float, char>.
		*  @return a view of the new inserted elements
		*/
		template<class RangeTy>
			requires std::is_same_v<typename RangeTy::value_type, containerType>
		auto Insert(RangeTy&& range)
		{
			auto& container = this->GetContainer();
			container.append_range(range);
			return InsertResult_internal(range);
		}

		// Version for a single element tuple (std::tuple<int>) allows to send a range of <int> instead
		template<class RangeTy>
			//requires std::is_constructible_v<containerType, RangeTy::value_type>
		auto Insert(RangeTy&& range)
		{
			auto& container = this->GetContainer();
			for (const auto& element : range)
			{
				container.emplace_back(element);
			}
			return InsertResult_internal(range);
		}

		auto size() const { return this->GetContainer().size(); }

	private:
		template<class Range>
		auto InsertResult_internal(Range&& r)
		{
			auto& container = this->GetContainer();
			const auto& dropSize = container.size() - r.size();
			return std::ranges::drop_view(container, dropSize);
		}
	};

	class IndexBuffer : public Internal::OpenGlBufferBase {
	public:
		using Type = uint32;
		using container = std::vector<Type>;
		using iter = typename container::iterator;
		using const_iter = typename container::const_iterator;
		using const_ref =typename  container::const_reference;


		IndexBuffer() noexcept;
		~IndexBuffer();

		void SendDataGPU(OpenGLUtils::Buffer::BufferUsage usage);

		void AddIndex(uint32 indice);
		template<typename Range>
		void AddIndices(Range&& range);

		void RemoveIndexAt(std::size_t position);
		void RemoveIndexAt(iter it);
		void RemoveIndicesAt(iter begin, iter end);

		iter begin();
		const_iter begin() const;

		iter end();
		const_iter end() const;

		std::size_t size() const noexcept;
		bool empty() const noexcept;

	private:
		std::vector<uint32> buffer;
	};

	template<typename Range>
	inline void IndexBuffer::AddIndices(Range&& range)
	{
		buffer.append_range(range);
	}

}