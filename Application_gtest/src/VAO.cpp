#include "gtest/gtest.h"
#include "OpenGl/VertexAttributeObject.h"


TEST(VAO, Offset)
{
	struct Vertice { float x; float y; float z; };
	std::tuple<Vertice, int> tuple;

	auto offset = Renderer::GL::Internal::AttributeOffset<decltype(tuple), 0>::value;
	auto offset2 = Renderer::GL::Internal::AttributeOffset<decltype(tuple), 1>::value;

	EXPECT_EQ(offset, 0u);
	EXPECT_EQ(offset2, sizeof(Vertice));
	EXPECT_EQ(offset2, sizeof(float)*3);
}