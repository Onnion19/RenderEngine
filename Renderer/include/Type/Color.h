#pragma once 

#include "Core/types.h"
#include <array>

namespace Renderer::Type {

	struct RawColor {
		float r, g, b, a;
	};

	struct ColorRGB {
		ColorRGB() = default;
		constexpr explicit ColorRGB(float r, float g, float b) noexcept : colors({ r,g,b }) {}
		constexpr explicit ColorRGB(float v) noexcept : colors({ v,v,v }) {}

		constexpr float& Red() { return colors[0]; }
		constexpr const float Red() const { return colors[0]; }

		constexpr float& Green() { return colors[1]; }
		constexpr const float Green() const { return colors[1]; }

		constexpr float& Blue() { return colors[2]; }
		constexpr const float Blue() const { return colors[2]; }
		constexpr operator RawColor()const { return { colors[0] , colors[1], colors[2], 1.f }; }
		struct ColorHSV ToHSV()const;

	protected:
		std::array<float, 3> colors;

	};

	struct ColorRGBA : public ColorRGB {
		ColorRGBA() = default;
		constexpr explicit ColorRGBA(float r, float g, float b, float a = 1.0f) noexcept : ColorRGB(r, g, b), alpha(a) {}
		constexpr explicit ColorRGBA(float v, float a = 1.0f) noexcept : ColorRGB(v), alpha(a) {}

		constexpr float& Alpha() { return alpha; }
		constexpr const float Alpha() const { return alpha; }
		constexpr operator RawColor()const { return { colors[0] , colors[1], colors[2], alpha }; }
	private:
		float alpha;

	};

	struct ColorHSV {

		ColorHSV() = default;
		explicit ColorHSV(float h, float s, float v) noexcept { hsv[0] = h; hsv[1] = s; hsv[2] = v; }

		constexpr float& Hue() { return hsv[0]; }
		constexpr const float Hue() const { return hsv[0]; }

		constexpr float& Saturation() { return hsv[1]; }
		constexpr const float Saturation() const { return hsv[1]; }

		constexpr float& Value() { return hsv[2]; }
		constexpr const float Value() const { return hsv[2]; }

		ColorRGB ToRGB()const;
		constexpr operator RawColor()const { return ToRGB(); }
	private:
		std::array<float, 3> hsv;
	};

	constexpr ColorRGBA WHITE{ 1.f,1.f,1.f,1.f };
	constexpr ColorRGBA BLACK{ 0.f,0.f,0.f,1.f };
	constexpr ColorRGBA RED{ 1.f,0.f,0.f,1.f };
	constexpr ColorRGBA GREEN{ 0.f,1.f,0.f,1.f };
	constexpr ColorRGBA BLUE{ 0.f,0.f,1.f,1.f };

}