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

TEST(Queue, Enqueue)
{
	const int32 size = 5;
	Queue<Foo, size> myQueue;

	for (int i = 0; i < size; i++)
	{
		myQueue.SafeEnqueue(i);
		EXPECT_EQ(myQueue.GetSize(), i + 1);
		EXPECT_EQ(myQueue.Front()->x, 0);
	}
}


TEST(Queue, Dequeue)
{
	const int32 size = 5;
	Queue<Foo, size> myQueue(size, 2);

	for (int i = 0; i < size; i++)
	{
		[[maybe_unused]] auto t = myQueue.SafeDequeue();
		EXPECT_EQ(myQueue.GetSize(), size - i - 1);
	}
}


TEST(Queue, RandomOperations)
{
	const int32 size = 5;
	Queue<Foo, size> myQueue(size, 2);

	for (int i = 0; i < 3; i++)
	{
		[[maybe_unused]] auto t = myQueue.SafeDequeue();
	}

	EXPECT_EQ(myQueue.GetSize(), 2);
	myQueue.UnsafeEnqueue(3);
	EXPECT_EQ(myQueue.GetSize(), 3);

}


TEST(Queue, Fill)
{
	const int32 size = 5;
	Queue<Foo, size> myQueue = Queue<Foo, size>(size, 2);

	EXPECT_EQ(myQueue.GetSize(), 5);
	EXPECT_TRUE(myQueue.Front() == myQueue.End());
	EXPECT_EQ(myQueue.MaxSize(), size);
	EXPECT_TRUE(myQueue.SafeDequeue().has_value());
}


TEST(Queue, Cycle)
{
	const int32 size = 5;
	Queue<Foo, size> myQueue(size, 10); // fill of 2
	auto front = myQueue.Begin();
	EXPECT_EQ(myQueue.GetSize(), 5);
	[[maybe_unused]] auto t = myQueue.SafeDequeue();
	EXPECT_EQ(myQueue.GetSize(), 4);
	myQueue.SafeEnqueue(2);
	EXPECT_EQ(myQueue.GetSize(), 5);
	auto end = myQueue.End();

	EXPECT_TRUE(++front == end);
}


TEST(Queue, SortOperations)
{
	const int32 size = 5;
	Queue<Foo, size> myQueue;
	auto sorting = [](const Foo& a, const Foo& b) {return a.x < b.x; };
	myQueue.UnsafeSortedEnqueue(sorting, 4);
	EXPECT_EQ(myQueue.Front()->x, 4);

	myQueue.UnsafeSortedEnqueue(sorting, 1);
	EXPECT_EQ(myQueue.Front()->x, 1);


}