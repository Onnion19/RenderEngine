#include "gtest/gtest.h"
#include "Geometry/BasicShapes.h"
#include "Type/Transform.h"

namespace Renderer::Geometry {
	TEST(Rectangle, Empty)
	{
		Rectangle rect;

		EXPECT_EQ(rect.botRight, vec2{});
		EXPECT_EQ(rect.topLeft, vec2{});
		EXPECT_EQ(rect.GetCenter(), vec2{});
		EXPECT_EQ(rect.GetSizeFromCenter(), vec2{});
	}

	TEST(Rectangle, FromPoints)
	{
		const Point2D topLeft{ 10.f, -10.f };
		const Point2D botLeft{ 20.f, -20.f };

		const vec2 size{ 5.f, 5.f };
		const Point2D center{ 15.f, -15.f };

		Rectangle rect{ topLeft, botLeft };
		EXPECT_EQ(rect.botRight, botLeft);
		EXPECT_EQ(rect.topLeft, topLeft);
		EXPECT_EQ(rect.GetCenter(), center);
		auto s = rect.GetSizeFromCenter();
		EXPECT_EQ(s, size);
	}

	TEST(Rectangle, FromTransform)
	{
		::Core::Transform2D transform{
			vec2 {0.f,0.f},
			vec2{5.f,5.f},
			0.f
		};
		Rectangle rect{ transform };

		const vec2 topLeft{ -5.f, 5.f };
		const vec2 botRight{ 5.f, -5.f };
		const vec2 size{ 5.f,5.f };

		EXPECT_EQ(rect.botRight, botRight);
		EXPECT_EQ(rect.topLeft, topLeft);
		EXPECT_EQ(rect.GetCenter(), vec2{});
		EXPECT_EQ(rect.GetSizeFromCenter(), size);
	}


}