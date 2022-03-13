#include "gtest/gtest.h"
#include "Type/Color.h"

namespace {
	template<typename T>
	bool AlmostEqual(const T& a, const T& b, const T& t)
	{
		return std::abs(a - b) < t;
	}
}

TEST(ColorTest, RGBtoHSV_RED)
{
	using namespace Renderer::Type;

	ColorRGB rgb(1.f, 0.f, 0.f);
	ColorHSV hsv = rgb.ToHSV();
	EXPECT_FLOAT_EQ(hsv.Hue(), 0.f);
	EXPECT_FLOAT_EQ(hsv.Saturation(), 1.f);
	EXPECT_FLOAT_EQ(hsv.Value(), 1.f);
}


TEST(ColorTest, RGBtoHSV_GREEN)
{
	using namespace Renderer::Type;

	ColorRGB rgb(0.f, 1.f, 0.f);
	ColorHSV hsv = rgb.ToHSV();
	EXPECT_FLOAT_EQ(hsv.Hue(), 120.f);
	EXPECT_FLOAT_EQ(hsv.Saturation(), 1.f);
	EXPECT_FLOAT_EQ(hsv.Value(), 1.f);
}

TEST(ColorTest, RGBtoHSV_BLUE)
{
	using namespace Renderer::Type;

	ColorRGB rgb(0.f, 0.f, 1.f);
	ColorHSV hsv = rgb.ToHSV();
	EXPECT_FLOAT_EQ(hsv.Hue(), 240.f);
	EXPECT_FLOAT_EQ(hsv.Saturation(), 1.f);
	EXPECT_FLOAT_EQ(hsv.Value(), 1.f);
}


TEST(ColorTest, RGBtoHSV_MIXED)
{
	using namespace Renderer::Type;

	ColorRGB rgb(.704f, .187f, .897f);
	ColorHSV hsv = rgb.ToHSV();
	EXPECT_TRUE(AlmostEqual(hsv.Hue(), 283.7f, 0.01f));
	EXPECT_TRUE(AlmostEqual(hsv.Saturation(), .792f, 0.01f));
	EXPECT_TRUE(AlmostEqual(hsv.Value(), .9f, 0.01f));
}

TEST(ColorTest, HSVtoRGB_RED)
{
	using namespace Renderer::Type;

	ColorHSV hsv = ColorHSV(0.f,1.f,1.f);
	ColorRGB rgb = hsv.ToRGB();
	EXPECT_FLOAT_EQ(rgb.Red(), 1.f);
	EXPECT_FLOAT_EQ(rgb.Green(), 0.f);
	EXPECT_FLOAT_EQ(rgb.Blue(), 0.f);
}


TEST(ColorTest, HSVtoRGB_GREEN)
{
	using namespace Renderer::Type;

	ColorHSV hsv = ColorHSV(120.f, 1.f, 1.f);
	ColorRGB rgb = hsv.ToRGB();
	EXPECT_FLOAT_EQ(rgb.Red(), 0.f);
	EXPECT_FLOAT_EQ(rgb.Green(), 1.f);
	EXPECT_FLOAT_EQ(rgb.Blue(), 0.f);
}

TEST(ColorTest, HSVtoRGB_BLUE)
{
	using namespace Renderer::Type;

	ColorHSV hsv = ColorHSV(240.f, 1.f, 1.f);
	ColorRGB rgb = hsv.ToRGB();
	EXPECT_FLOAT_EQ(rgb.Red(), 0.f);
	EXPECT_FLOAT_EQ(rgb.Green(), 0.f);
	EXPECT_FLOAT_EQ(rgb.Blue(), 1.f);
}


TEST(ColorTest, HSVtoRGB_MIXED)
{
	using namespace Renderer::Type;

	ColorHSV hsv = ColorHSV(283.7f,0.792f, .9f);
	ColorRGB rgb = hsv.ToRGB();
	EXPECT_TRUE(AlmostEqual(rgb.Red(), .704f,0.1f));
	EXPECT_TRUE(AlmostEqual(rgb.Green(), 0.187f,0.1f));
	EXPECT_TRUE(AlmostEqual(rgb.Blue(), 0.897f,0.1f));
}