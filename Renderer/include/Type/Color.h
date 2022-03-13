#pragma once 

#include "Core/types.h"
#include <array>

namespace Renderer::Type {


	struct ColorRGB {
		ColorRGB() = default;
		explicit ColorRGB(float r, float g, float b) noexcept { colors[0] = r; colors[1] = g; colors[2] = b; }
		explicit ColorRGB(float v) noexcept { colors.fill(v); }

		constexpr float& Red() { return colors[0]; }
		constexpr const float Red() const { return colors[0]; }

		constexpr float& Green() { return colors[1]; }
		constexpr const float Green() const { return colors[1]; }

		constexpr float& Blue() { return colors[2]; }
		constexpr const float Blue() const { return colors[2]; }

		struct ColorHSV ToHSV()const;

	private:
		std::array<float, 3> colors;

	};

	struct ColorRGBA : public ColorRGB {
		ColorRGBA() = default;
		explicit ColorRGBA(float r, float g, float b, float a = 1.0f) noexcept : ColorRGB(r, g, b) { alpha = a; }
		explicit ColorRGBA(float v, float a = 1.0f) noexcept : ColorRGB(v) { alpha = a; }

		constexpr float& Alpha() { return alpha; }
		constexpr const float Alpha() const { return alpha; }

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

	private:
		std::array<float, 3> hsv;
	};
}