#include "gtest/gtest.h"
#include "Core/Handlers.h"



namespace {
	struct Foo {};
}

using namespace Renderer::Core;

TEST(Handlers, EmptyHandle)
{
	ObserverHandler<Foo> handler;
	EXPECT_FALSE(handler.Valid());
	EXPECT_FALSE(handler.get());
}


TEST(Handlers, MakeObserver)
{
	std::unique_ptr<Foo> f(new Foo());
	ObserverHandler<Foo> handler = MakeObserver(f.get());
	EXPECT_TRUE(handler.Valid());
	EXPECT_TRUE(handler.get());
}


TEST(Handlers, MoveSemantics)
{
	std::unique_ptr<Foo> f(new Foo());
	ObserverHandler<Foo> handler = MakeObserver(f.get());
	EXPECT_TRUE(handler.Valid());
	EXPECT_TRUE(handler.get());

	auto handler2 = std::move(handler);
	EXPECT_FALSE(handler.Valid());
	EXPECT_FALSE(handler.get());
	EXPECT_TRUE(handler2.Valid());
	EXPECT_TRUE(handler2.get());
}

TEST(Handlers, CopySemantics)
{
	std::unique_ptr<Foo> f(new Foo());
	ObserverHandler<Foo> handler = MakeObserver(f.get());
	EXPECT_TRUE(handler.Valid());
	EXPECT_TRUE(handler.get());

	auto handler2 = handler;
	EXPECT_TRUE(handler.Valid());
	EXPECT_TRUE(handler.get());
	EXPECT_TRUE(handler2.Valid());
	EXPECT_TRUE(handler2.get());
	EXPECT_TRUE(handler2.get() == handler.get());
}