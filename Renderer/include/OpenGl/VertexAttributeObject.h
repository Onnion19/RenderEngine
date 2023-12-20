#pragma once

#include "Core/types.h"
#include "OpenGl/Buffer.h"
#include "OpenGl/OpenGLUtils.h"

namespace Renderer::GL {


	namespace Internal {

		template<class TupleTy, int i>
		struct AttributeOffsetRecurisve {
			static constexpr unsigned value = sizeof(std::tuple_element_t<i, TupleTy>) + AttributeOffsetRecurisve<TupleTy, i - 1>::value;
		};

		template<class TupleTy>
		struct AttributeOffsetRecurisve<TupleTy, 0> {
			static constexpr unsigned value = sizeof(std::tuple_element_t<0, TupleTy>);
		};

		template<class TupleTy, int i>
		struct AttributeOffset {
			static_assert(i > 0);
			static constexpr unsigned value = AttributeOffsetRecurisve<TupleTy, i - 1>::value;
		};

		template<class TupleTy>
		struct AttributeOffset<TupleTy, 0> {
			static constexpr unsigned value = 0;
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

			static constexpr auto tupleIndex = TupleHelper::Index< AttributeType, BufferType>::value;
			// not sure about this stride. This is true for tuples with multiple types, but single ones...
			static constexpr auto stride = sizeof(BufferType);
			static constexpr auto offset = Internal::AttributeOffset<BufferType, tupleIndex>::value;
		};
	public:
		explicit VertexAtributeObject();
		void Bind();
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
		Bind();
		Enable(properties.attributeIndex);
		glVertexAttribPointer(
			properties.attributeIndex,
			properties.attributeSize,
			OpenGLUtils::Buffer::EnumToGLEnum(properties.elementType),
			properties.normalized,
			properties.stride,
			reinterpret_cast<const void*>(properties.offset));
	}
}