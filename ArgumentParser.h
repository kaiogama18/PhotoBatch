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

	// Get a value from the Flag get during Parser
	bool GetFlag(const std::string& flag) const;

	// Passes a List of arguments in the Parser to the argv
	void Parse(int argc, char* argv[]);

private:
	// m_Falsgs --> todo nome que tem m_ -> é membro da classe
	std::map<std::string, bool > m_Flags; //container do Sql
};
