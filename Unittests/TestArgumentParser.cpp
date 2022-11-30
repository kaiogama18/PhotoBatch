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

TEST(TestArgumentParser, RegisterOption)
{
	ArgumentParser argParser;

	argParser.RegisterOption("MyOption");

	EXPECT_TRUE(argParser.IsOptionRegistered("MyOption"));
}

TEST(TestArgumentParser, RegisterOption_Whitespace)
{
	ArgumentParser argParser;

	argParser.RegisterOption("My Option");
	EXPECT_FALSE(argParser.IsOptionRegistered("My Option"));
}