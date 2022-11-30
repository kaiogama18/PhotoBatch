#include<gtest/gtest.h>

#include <ArgumentParser.h>


TEST(TestArgumentParser, RegisterFlag)
{
	ArgumentParser argParser;

	// Status check before operation
	EXPECT_FALSE(argParser.IsFlagRegistered("MyFlag"));

	// Register Flag
	argParser.RegisterFlag("MyFlag");

	// Status check after operation
	EXPECT_TRUE(argParser.IsFlagRegistered("MyFlag"));
}

TEST(TestArgumentParser, RegisterFlag_Whitespace)
{
	ArgumentParser argParser;

	argParser.RegisterFlag("My Flag");
	EXPECT_FALSE(argParser.IsFlagRegistered("My Flag"));
}
/*
TEST(MyFirstTest, ASimpleTest)
{
	EXPECT_TRUE(true);
}
*/
