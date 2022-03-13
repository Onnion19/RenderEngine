#include "gtest/gtest.h"
#include "Core/types.h"



TEST(Types, BitMask_SingleBit)
{
	BitMask bitmask = BuildBitMask(1); //2

	EXPECT_TRUE(AreBitsSets(2, 1));
	EXPECT_TRUE(MaskComparisson(2, bitmask));
}


TEST(Types, BitMask_MultpleBits)
{

	BitMask bitmask = BuildBitMask(1, 4);
	BitMask bitmask2 = BuildBitMask(4,1);
	BitMask bitmask3 = BuildBitMask(1,4 ,4);
	BitMask bitmask4 = BuildBitMask(1,4 ,5);

	EXPECT_TRUE(MaskComparisson(18, bitmask));
	EXPECT_TRUE(MaskComparisson(bitmask2, bitmask));
	EXPECT_TRUE(MaskComparisson(bitmask3, bitmask));
	EXPECT_FALSE(MaskComparisson(bitmask4, bitmask));
}

TEST(Types, BitMask_Filter)
{
	const auto bit1 = Bit<1>::value; // 2
	const auto bit2 = Bit<4>::value; // 16
	BitMask bitmask = BuildBitMask(bit1, bit2);

	EXPECT_TRUE(AreBitsSets(18, 1, 4));
	EXPECT_TRUE(AreBitsSets(19, 1, 4));

	EXPECT_FALSE(AreBitsSets(2, 1, 4));
	EXPECT_FALSE(AreBitsSets(16, 1, 4));

}