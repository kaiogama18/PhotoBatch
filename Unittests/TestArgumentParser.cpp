#include<gtest/gtest.h>

#include <ArgumentParser.h>

#include <array>


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

TEST(TestArgumentParser, Parse)
{
	ArgumentParser argParser;

	std::array<const char*, 5> args =
	{
		"TestArgumentParser",
		"--flag",
		"--string=AaBbCcDd",
		"--number=42",
		"--float=4.2"
	};

	argParser.RegisterFlag("flag");
	argParser.RegisterOption("string");
	argParser.RegisterOption("number");
	argParser.RegisterOption("float");


	argParser.Parse(static_cast<int>(args.size()), args.data());

	EXPECT_FALSE(argParser.GetFlag("unregisteredFlag"));
	EXPECT_TRUE(argParser.GetFlag("flag"));
	EXPECT_EQ(argParser.GetOptionAs<std::string>("string"), "aabbccdd");
	EXPECT_EQ(argParser.GetOptionAs<int>("number"), 42);
	EXPECT_EQ(argParser.GetOptionAs<float>("float"), 4.2f);
}

TEST(TestArgumentParser, Parse_InvalidArguments)
{
	ArgumentParser argParser;

	argParser.Parse(0, nullptr);
	argParser.Parse(42, nullptr);
	argParser.Parse(-1, nullptr);
}