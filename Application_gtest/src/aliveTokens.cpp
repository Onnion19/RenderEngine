#include "gtest/gtest.h"
#include "Core/AliveToken.h"

using namespace Renderer::Core;


TEST(AliveTokenTest, AllAlive)
{
	TokenOwner owner; 
	TokenObserver observer(owner);
	
	EXPECT_TRUE(observer);
}

TEST(AliveTokenTest, OwnerCancel)
{
	TokenOwner owner;
	TokenObserver observer(owner);
	owner.Cancel();

	EXPECT_FALSE(observer);
}


TEST(AliveTokenTest, OutOfScope)
{
	TokenOwner owner;
	TokenObserver observer(owner);
	{
		TokenOwner owner2; 
		TokenObserver observer2(owner2);
		observer = std::move(observer2);
	}

	EXPECT_FALSE(observer);
}