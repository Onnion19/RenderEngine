#pragma once
#include <cstdint>
#include <string>
#include "vec2.hpp"

//Integer types
typedef std::int8_t int8;
typedef std::int16_t int16;
typedef std::int32_t int32;
typedef std::int64_t int64;
typedef std::uint8_t uint8;
typedef std::uint16_t uint16;
typedef std::uint32_t uint32;
typedef std::uint64_t uint64;

typedef std::string string;
typedef int32 BitMask;

template<int n>
struct Bit { enum { value = (1 << n) }; };

constexpr int Bit_(int n) { return 1 << n; }

template <class ... Bits>
constexpr BitMask BuildBitMask(Bits&& ... bits) {
	return (... | static_cast<BitMask>(bits));
}

template <class ... Bits>
constexpr bool BitComparisson(int number, Bits&& ... bits)
{
	const BitMask b = BuildBitMask(std::forward<Bits>(bits)...);
	return (number & b) == b;
}