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

	// The Flag is Registered?
	bool IsFlagRegistered(const std::string& flag) const;

	// The Option is Registered?
	bool IsOptionRegistered(const std::string& option) const;

	// Get a value from the Flag get during Parser
	bool GetFlag(const std::string& flag) const;

	template<typename T>
	T GetOptionAs(const std::string& option) const;

	template<>
	std::string GetOptionAs(const std::string& option) const
	{
		return GetOption(option);
	}

	template<>
	float GetOptionAs(const std::string& option) const 
	{
		return GetOptionAsFloat(option);
	}

	template<>
	int GetOptionAs(const std::string& option) const
	{
		return GetOptionAsInt(option);
	}

	// Passes a List of arguments in the Parser to the argv
	void Parse(int argc, char* argv[]);

	void ArgumentParser::SetHelpMessage(const std::string& helpMessage)
	{
		m_HelpMessage = helpMessage;
	}

	const std::string& ArgumentParser::SetHelpMessage() const
	{
		return m_HelpMessage;
	}

private:

	// Get the read value of the option during the parser 
	const std::string& GetOption(const std::string& option) const;

	//Get the read value of the option converted to float
	float GetOptionAsFloat(const std::string& option) const;

	//Get the read value of the option converted to Integer
	int GetOptionAsInt(const std::string& option) const;

	// m_Falsgs --> todo nome que tem m_ -> é membro da classe
	std::map<std::string, bool > m_Flags; //container do Sql
	std::map<std::string, std::string> m_Options;
	std::string m_HelpMessage;
};
