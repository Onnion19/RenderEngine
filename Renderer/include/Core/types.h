#pragma once
#include <cstdint>
#include <string>
#include "vec2.hpp"
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

/*******************************
		CHAR TYPES
*******************************/

typedef std::string string;

/*******************************
		BIT IMPLEMENTATION
*******************************/
typedef int32 BitMask;

template<int n>
struct Bit { enum { value = (1 << n) }; };

constexpr int32 Bit_(int n) { return 1 << n; }

template <class ... Bits>
constexpr BitMask BuildBitMask(Bits&& ... bits) {
	return (... | Bit_(bits));
}

template <class ... Bits>
constexpr bool AreBitsSets(int32 number, Bits&& ... bits)
{
	const BitMask b = BuildBitMask(std::forward<Bits>(bits)...);
	const auto n = (number & b);
	return n>0 && n == number;
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