#pragma once

#include <string>
#include <map>

/*
* Class use to read the arguments from the comand line
* 
* Example:
*	ArgumentParser argParser;
*	argParser.RegisterFlag("rename");
*	argParser.Parse(argc, argv)
*	argParser.GetFlag("rename")
* 
*/
class ArgumentParser
{
public:
	// Register a flag to use in the Parser 
	void RegisterFlag(const std::string& flag);

	// Register an option to use during the parser
	void RegisterOption(const std::string& option);

	// Get a value from the Flag get during Parser
	bool GetFlag(const std::string& flag) const;

	// Get the read value of the option during the parser 
	const std::string& GetOption(const std::string& option) const;

	// Passes a List of arguments in the Parser to the argv
	void Parse(int argc, char* argv[]);

private:
	// m_Falsgs --> todo nome que tem m_ -> é membro da classe
	std::map<std::string, bool > m_Flags; //container do Sql
	std::map<std::string, std::string> m_Options;
};
