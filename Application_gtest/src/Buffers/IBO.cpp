#include "gtest/gtest.h"
#include "OpenGl/Buffer.h"
#include "Context/GLFWContext.h"
#include <array>

namespace Renderer::GL::Test {

	TEST(IBO, AddSingleQuad)
	{
		std::array<uint32, 4> quad = { 1,2,3,4 };
		IndexBuffer ibo;
		ibo.AddIndices(quad);

		int i = 0;
		for (const auto& index : ibo)
		{
			EXPECT_EQ(index, quad[i]); i++;
		}

		ibo.RemoveIndicesAt(ibo.begin(), ibo.end());
		EXPECT_TRUE(ibo.empty());
	}

	TEST(IBO, MultipleQuad)
	{
		std::array<uint32, 4> quad1 = { 1,2,3,4 };
		std::array<uint32, 4> quad2 = { 5,6,7,8 };
		std::array<uint32, 4> quad3 = { 9,10,11,12 };
		IndexBuffer ibo;
		ibo.AddIndices(quad1);
		ibo.AddIndices(quad2);
		ibo.AddIndices(quad3);

		int i = 0;
		for (const auto& index : ibo)
		{
			if (i / 4 == 0)
				EXPECT_EQ(index, quad1[i % 4]);
			if (i / 4 == 1)
				EXPECT_EQ(index, quad2[i % 4]);
			if (i / 4 == 2)
				EXPECT_EQ(index, quad3[i % 4]);

			i++;
		}

		// remove middle quad
		ibo.RemoveIndicesAt(ibo.begin()+4, ibo.begin()+8);
		EXPECT_EQ(ibo.size(), 8u);

		i = 0;
		for (const auto& index : ibo)
		{
			if (i / 4 == 0)
				EXPECT_EQ(index, quad1[i % 4]);
			if (i / 4 == 1)
				EXPECT_EQ(index, quad3[i % 4]);

			i++;
		}

	}


}