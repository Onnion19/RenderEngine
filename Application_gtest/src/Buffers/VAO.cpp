#include "gtest/gtest.h"
#include "OpenGl/VertexAttributeObject.h"


TEST(VAO, Offset)
{
	struct Vertice { float x; float y; float z; };
	std::tuple<Vertice, int, char> tuple;

	auto offset = Renderer::GL::Internal::AttributeOffset<decltype(tuple), 0>::value;
	auto offset2 = Renderer::GL::Internal::AttributeOffset<decltype(tuple), 1>::value;
	auto offset3 = Renderer::GL::Internal::AttributeOffset<decltype(tuple), 2>::value;

	EXPECT_EQ(offset, sizeof(int) + sizeof(char));
	EXPECT_EQ(offset2, sizeof(char));
	EXPECT_EQ(offset3, 0);
}