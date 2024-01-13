#pragma once

#include "Core/types.h"
#include "OpenGl/Buffer.h"
#include "OpenGl/OpenGLUtils.h"

namespace Renderer::GL {

	/*
		Helper to compute the offset of a type T inside a tuple. 

		:::WARNING::::
		This implementation is not reliable and might only work under MSVC as 
		I'm trying to get the offset of a tuple assuming that: 
		- std::tuple<T...> is in fact a struct inheritance in reverse order.
		- This asumption is detail assumption and can change per platform and compiler.
	*/
	namespace Internal {

		template<class TupleTy, int i>
		struct AttributeOffsetRecurisve {
			static constexpr unsigned value = sizeof(std::tuple_element_t<std::tuple_size_v<TupleTy> - i, TupleTy>) + AttributeOffsetRecurisve<TupleTy, i - 1>::value;
		};

		template<class TupleTy>
		struct AttributeOffsetRecurisve<TupleTy, 0> {
			static constexpr unsigned value = 0;
		};

		template<class TupleTy, int i>
		struct AttributeOffset {
			static_assert(std::tuple_size_v<TupleTy> > 0 && i <= std::tuple_size_v<TupleTy>);
			static constexpr uint64 value = AttributeOffsetRecurisve<TupleTy, std::tuple_size_v<TupleTy> - i - 1>::value;
		};
	}

	class VertexAtributeObject {
	public:
		template<typename BufferType, typename AttributeType>
		struct AttributePointer {
			AttributePointer(uint8 index, uint8 size, OpenGLUtils::Buffer::GLType type, bool normal)
				:attributeIndex(index)
				, attributeSize(size)
				, elementType(type)
				, normalized(normal) {}

			AttributePointer(const AttributePointer& other) :
				AttributePointer(other.attributeSize, other.attributeSize, other.elementType, other.normalized) {}

			const uint8 attributeIndex;
			const uint8 attributeSize; // for instance vector x,y,z is size 3
			const OpenGLUtils::Buffer::GLType elementType;
			const bool normalized;

			static constexpr auto tupleIndex = TupleHelper::Index<AttributeType, BufferType>::value;
			// not sure about this stride. This is true for tuples with multiple types, but single ones...
			static constexpr auto stride = sizeof(BufferType);
			static constexpr auto offset = Internal::AttributeOffset<BufferType, tupleIndex>::value;			
		};
	public:
		explicit VertexAtributeObject();
		~VertexAtributeObject();
		void Bind();
		void Unbind();
		void Enable(uint8 AttributeId);
		void Disable(uint8 AttributeId);
		template<typename T>
		void EnableAndDefineAttributePointer(T&& properties);
	private:
		GLBufferId id;
	};

	template<typename T>
	void Renderer::GL::VertexAtributeObject::EnableAndDefineAttributePointer(T&& properties)
	{
		glVertexAttribPointer(
			properties.attributeIndex,
			properties.attributeSize,
			OpenGLUtils::EnumToGLEnum(properties.elementType),
			properties.normalized,
			properties.stride,
			reinterpret_cast<const void*>(properties.offset));
		Enable(properties.attributeIndex);
	}
}