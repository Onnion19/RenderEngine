#include "gtest/gtest.h"
#include "Structures/Queue.h"


struct Foo {
	Foo() = default;
	Foo(int i) : x(i) {};
	int x = 0;
};


TEST(Queue, Empty)
{
	const int32 size = 5;
	Queue<Foo, size> myQueue;

	EXPECT_EQ(myQueue.GetSize(), 0);
	EXPECT_EQ(myQueue.MaxSize(), size);
	EXPECT_FALSE(myQueue.SafeDequeue().has_value());
	EXPECT_TRUE(myQueue.Front() == myQueue.End());
}


TEST(Queue, Fill)
{
	const int32 size = 5;
	Queue<Foo, size> myQueue = Queue<Foo,size>(size,2);

	EXPECT_EQ(myQueue.GetSize(), 5);
	EXPECT_EQ(myQueue.MaxSize(),size);
	EXPECT_TRUE(myQueue.SafeDequeue().has_value());
	EXPECT_TRUE(myQueue.Front() != myQueue.End());
}