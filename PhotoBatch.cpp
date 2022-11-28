#include <iostream>
#include<iomanip>

#include "ArgumentParser.h"

int main(int argc, char* argv[])
{	
	setlocale(LC_ALL, "portuguese");
	setlocale(LC_ALL, "en_US");
	
	ArgumentParser argParser;
	argParser.RegisterFlag("rename");
	argParser.RegisterFlag("convert");
	argParser.RegisterFlag("resize");
	argParser.RegisterFlag("scale");
	argParser.RegisterOption("folder");
	argParser.RegisterOption("amount");

	argParser.Parse(argc, argv);

	std::cout << std::boolalpha <<	"Rename.....: "	<< argParser.GetFlag("rename")	<< std::endl;
	std::cout << std::boolalpha <<	"Convert....: "	<< argParser.GetFlag("convert") << std::endl;
	std::cout << std::boolalpha <<	"Resize.....: "	<< argParser.GetFlag("resize")	<< std::endl;
	std::cout << std::boolalpha <<	"Scale......: "	<< argParser.GetFlag("scale")	<< std::endl;
	
	std::cout << "Folder.....: " << argParser.GetOptionAs<std::string>("folder") << std::endl;
	//std::cout << "Amount.....: " << argParser.GetOption("amount") << std::endl;

	std::cout << "Amountfloat: " << argParser.GetOptionAs<float>("amount") << std::endl;
	std::cout << "AmountInt..: " << argParser.GetOptionAs<int>("amount") << std::endl;

	return 0;
}