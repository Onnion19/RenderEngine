#pragma once
#include <cstdint>
#include <string>
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "mat2x2.hpp"
#include "mat3x3.hpp"
#include "mat4x4.hpp"
#include "Core/Handlers.h"

/*******************************
		INTEGER TYPES
*******************************/
typedef std::int8_t int8;
typedef std::int16_t int16;
typedef std::int32_t int32;
typedef std::int64_t int64;
typedef std::uint8_t uint8;
typedef std::uint16_t uint16;
typedef std::uint32_t uint32;
typedef std::uint64_t uint64;

/****		OPENGL		****/
typedef uint32 GLBufferId;
typedef uint32 GlRenderMode;

/*******************************
		ENUMERATIONS
*******************************/

template<class T>
requires std::is_enum<T>::value
auto GetEnumValue(const T& t)
{
	using type = std::underlying_type_t<T>;
	return static_cast<type>(t);
}

/*******************************
		CHAR TYPES
*******************************/

typedef std::string string;


/*******************************
		VECTOR TYPES
*******************************/

typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;

/*******************************
		MATRIX TYPES
*******************************/

typedef glm::mat2 mat2;
typedef glm::mat3 mat3;
typedef glm::mat4 mat4;


/*******************************
		BIT IMPLEMENTATION
*******************************/
typedef int32 BitMask;

constexpr int32 Bit_(int n) { return 1 << n; };

template<int n>
struct Bit { enum { value = 1 << n }; };


template <class ... Bits>
constexpr BitMask BuildBitMask(Bits&& ... bits) {
	return (... | Bit_(bits));
}

template <class ... Bits>
constexpr bool AreBitsSets(int32 number, Bits&& ... bits)
{
	const BitMask b = BuildBitMask(std::forward<Bits>(bits)...);
	const auto n = (number & b);
	return n > 0 && n == b;
}

constexpr bool MaskComparisson(int32 number, BitMask mask)
{
	return number == mask;
}

/*******************************
		CUSTOM TYPES
*******************************/

template<class T>
using Observer = Renderer::Core::ObserverHandler<T>;