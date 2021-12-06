#pragma once 

#include "Core/types.h"
#include <iostream>

namespace Renderer::Input {

	enum class KeyboardCode : BitMask
	{
		None = Bit<0>::value,
		A = Bit<1>::value,
		B = Bit<2>::value,
		C = Bit<3>::value,
		D = Bit<4>::value,
		E = Bit<5>::value,
		F = Bit<6>::value,
		G = Bit<7>::value,
		H = Bit<8>::value,
		I = Bit<9>::value,
		J = Bit<10>::value,
		K = Bit<11>::value,
		L = Bit<12>::value,
		M = Bit<13>::value,
		N = Bit<14>::value,
		O = Bit<15>::value,
		P = Bit<16>::value,
		Q = Bit<17>::value,
		R = Bit<18>::value,
		S = Bit<19>::value,
		T = Bit<20>::value,
		U = Bit<21>::value,
		V = Bit<22>::value,
		W = Bit<23>::value,
		X = Bit<24>::value,
		Y = Bit<25>::value,
		Z = Bit<26>::value,
		Shift = Bit<27>::value,
		Alt = Bit<28>::value,
		Cntrl = Bit<29>::value,
	};

	template<class ... KeyboardCodes>
	BitMask BuildBitMaskFromKeyboardCode(KeyboardCodes && ...kc)
	{
		return (... | static_cast<BitMask>(kc));
	}

	template <class T>
	KeyboardCode GetKeyFromLiteral(T t)
	{
		return static_cast<KeyboardCode>(t);
	}

	enum class ButtonStatus {
		UP = 0, DOWN = 1
	};

	struct KeyInfo {
		ButtonStatus status;
		KeyboardCode code;
		KeyboardCode modifier = KeyboardCode::None;
	};


}