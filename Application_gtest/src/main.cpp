#include "gtest/gtest.h"
#include "Context/GLFWContext.h"

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	Renderer::GLFW::GLFWContext context;
	auto window = context.CreateNewWindow(1, 1, "Test");
	return RUN_ALL_TESTS();
}