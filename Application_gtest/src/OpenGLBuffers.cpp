#include "gtest/gtest.h"
#include "OpenGl/Buffer.h"
#include "Context/GLFWContext.h"

namespace Renderer::GL::Test {

	struct Vertice {
		float x, y, z;
		bool operator==(const Vertice& o) const { return x == o.x && y == o.y && z == o.z; };
	};
	struct Color {
		uint8 r, g, b, a;
		bool operator==(const Color& o) const { return r == o.r && g == o.g && b == o.b && a == o.a; }
	};
	struct UV {
		float x, y;
		bool operator==(const UV& o) const { return x == o.x && y == o.y; }
	};


	using MultiBuffer = MultiTypeBuffer<Vertice, Color, UV>;

	TEST(OpenGLBuffer, Empty)
	{
		MultiBuffer buffer;
		EXPECT_EQ(buffer.GetContainer().size(), 0);
	}

	TEST(OpenGLBuffer, OneElement)
	{
		Vertice v{ 1,2,3 };
		Color c{ 4,5,6,7 };
		UV u{ 8,9 };

		MultiBuffer buffer;
		buffer.GetContainer().emplace_back(v, c, u);
		EXPECT_EQ(buffer.GetContainer().size(), 1);


		auto VerticeList = buffer.GetDataAs<Vertice>();
		auto ColorList = buffer.GetDataAs<Color>();
		auto UVList = buffer.GetDataAs<UV>();
		//Size check
		{
			EXPECT_TRUE(VerticeList.size() == ColorList.size());
			EXPECT_TRUE(VerticeList.size() == UVList.size());
		}

		// Contents check
		{
			EXPECT_EQ(VerticeList[0], v);
			EXPECT_EQ(ColorList[0], c);
			EXPECT_EQ(UVList[0], u);
		}

		//Modify Contents 
		{
			Vertice v2 = { 0,0,0 };
			VerticeList[0] = v2;
			VerticeList = buffer.GetDataAs<Vertice>();
			EXPECT_NE(VerticeList[0], v);
			EXPECT_EQ(VerticeList[0], v2);
		}
	}


}