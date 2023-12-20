#pragma once 
#include "OpenGl/OpenGLUtils.h"
#include "Structures/RawBuffer.h"
#include <algorithm>
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
			~OpenGlBufferBase() noexcept;

			/*
			* Gets the GLuint of the buffer
			*/
			[[nodiscard]] GLBufferId GetID()const;

			/*
			* Binds the buffer object.
			*/
			void Bind();

			inline bool operator==(const OpenGlBufferBase& other)const noexcept;
		private:
			void GenerateBuffer();

		protected:
			GLBufferId mBufferID;
			OpenGLUtils::Buffer::BufferType mType;
		};
	}

	template<typename ... T>
	class OpenGlBuffer : public Internal::OpenGlBufferBase, public Renderer::MultiTypeBuffer<T...> {
		using containerType = Renderer::MultiTypeBuffer<T...>::bufferTy;
	public:

		OpenGlBuffer() = default;
		OpenGlBuffer(OpenGLUtils::Buffer::BufferType type) : Internal::OpenGlBufferBase(type) {}

		void SendDataGPU(OpenGLUtils::Buffer::BufferUsage usage) {
			Bind();
			const auto& container = this->GetContainer();
			const auto& containerByteSize = container.size() * sizeof(containerType);
			const auto& GlBufferType = EnumToGLEnum(mType);
			const auto& GlBufferUsage = EnumToGLEnum(usage);
			//Send all the buffer chunk to the GPU :D 
			glBufferData(GlBufferType, containerByteSize, container.data(), GlBufferUsage);
		}

		/*
		* Inserting helper where it receives a range of type T which is just one of the
		* types of the tuple inside MultiTypeBuffer.
		*
		* This function will insert as many tuples as needed and only modify the value
		* of the same type as the input range
		*
		* Example:
		*	MultiTypeBuffer container type = tuple<int,float, string>
		*	input T range = { 3.f, 2.f, 4.f}
		*
		*	result of the inserting:
		*		MultiTypeBuffer container = [(0, 3.f, "") , (0, 2.f, ""), (0, 4.f, "")]
		*
		*  @return a view of the new inserted elements
		*/
		template<class T> //TODO: Add concept to use this function when T is not a tuple vector
		auto Insert(const T& range)
		{
			const auto& begin = range.begin();
			const auto& end = range.end();
			auto& container = this->GetContainer();
			// back inserter only works with lineal containers such as vector.
			auto iter = std::back_inserter(container);
			std::transform(begin, end, iter, [](auto value) mutable -> containerType {
				return containerType{ value };
			});

			const auto& dropSize = container.size() - range.size();
			return std::ranges::drop_view(container, dropSize);
		}
	};

}