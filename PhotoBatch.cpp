#include <iostream>
#include<iomanip>
#include<array>
#include<filesystem>

#include "ArgumentParser.h"

namespace Args
{
	namespace Flags
	{
		static constexpr const char* Rename = "rename";
		static constexpr const char* Convert = "convert";
		static constexpr const char* Resize = "resize";
		static constexpr const char* Scale = "scale";
	}

	namespace Opts
	{
		static constexpr const char* Folder = "folder";
		static constexpr const char* Filter = "filter";
	}
}

void ValidadeArguments(const ArgumentParser& argParser)
{
	// Reading the flags that the ArgumentParser identifies
	const bool bRenameMode = argParser.GetFlag(Args::Flags::Rename);
	const bool bConvertMode = argParser.GetFlag(Args::Flags::Convert);
	const bool bResizeMode = argParser.GetFlag(Args::Flags::Resize);
	const bool bScaleMode = argParser.GetFlag(Args::Flags::Scale);

	const std::array<bool, 4> modes = { bRenameMode, bConvertMode, bResizeMode, bScaleMode };
	const std::ptrdiff_t numActiveModes = std::count(std::begin(modes), std::end(modes), true);

	//Check if only a mode PhotoBatch is ativacted
	//if (!(bRenameMode ^ bConvertMode ^ bResizeMode ^ bScaleMode))
	if (numActiveModes != 1)
	{
		throw std::invalid_argument("Only one mode can be activated");
	}

	//Paste Validade --> Folter
	const std::string folder = argParser.GetOptionAs<std::string>(Args::Opts::Folder);

	if( folder.empty())
	{
		throw std::invalid_argument("Folder cannot be blank");
	}

	if (!std::filesystem::exists(folder))
	{
		throw std::invalid_argument("The folder does not exist!");
	}

	//
	const std::string filder = argParser.GetOptionAs<std::string>(Args::Opts::Filter);
	if (!filder.empty())
	{
		const std::string invalidCharacters = "\\/*?\"<>|";
		if(filder.find_first_of(invalidCharacters) != std::string::npos)
		{
			throw std::invalid_argument("The filter does nnot contain: " + invalidCharacters);
		}
	}
}

int main(int argc, char* argv[])
{	
	setlocale(LC_ALL, "portuguese");
	setlocale(LC_ALL, "en_US");
	
	ArgumentParser argParser;
	argParser.RegisterFlag(Args::Flags::Rename);
	argParser.RegisterFlag(Args::Flags::Convert);
	argParser.RegisterFlag(Args::Flags::Resize);
	argParser.RegisterFlag(Args::Flags::Scale);
	
	argParser.RegisterOption(Args::Opts::Folder);
	//argParser.RegisterOption("amount");
	argParser.RegisterOption(Args::Opts::Filter);

	argParser.Parse(argc, argv);

	try
	{
		ValidadeArguments(argParser);
	}
	catch (const std::exception& exception)
	{
		std::cerr << exception.what() << std::endl;
	}

	/*
	std::cout << std::boolalpha <<	"Rename.....: "	
		<< argParser.GetFlag(Args::Flags::Rename) << std::endl;
	
	std::cout << std::boolalpha <<	"Convert....: "	
		<< argParser.GetFlag(Args::Flags::Convert) << std::endl;
	
	std::cout << std::boolalpha <<	"Resize.....: "	
		<< argParser.GetFlag(Args::Flags::Resize)	<< std::endl;
	
	std::cout << std::boolalpha <<	"Scale......: "	
		<< argParser.GetFlag(Args::Flags::Scale)	<< std::endl;
	*/
	//std::cout << "Folder.....: " << argParser.GetOptionAs<std::string>("folder") << std::endl;
	//std::cout << "Amountfloat: " << argParser.GetOptionAs<float>("amount") << std::endl;
	//std::cout << "AmountInt..: " << argParser.GetOptionAs<int>("amount") << std::endl;

	return 0;
}