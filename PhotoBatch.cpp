#include <iostream>
#include<iomanip>
#include<map>

class ArgumentParser
{
public:
	//Verificar
	void RegisterFlag(const std::string& flag)
	{
		if (!flag.empty())
		{
			//Acessar um mebro do mapa --> default is false
			m_Flags[flag] == false;
		}
	}

	//
	bool GetFlag(const std::string& flag)
	{
		if (!flag.empty())
		{
			// 'auto' return the deduction of type
			auto flagIt = m_Flags.find(flag); //Return iterator
			if (flagIt != std::end(m_Flags))
			{
				return flagIt->second;
			}
		}
		return false;
	}

	void Parse(int argc, char* argv[])
	{

	}


private:
	// m_Falsgs --> todo nome que tem m_ -> é membro da classe
	std::map<std::string, bool > m_Flags; //container do Sql
};

int main(int argc, char* argv[])
{	
	setlocale(LC_ALL  , "portuguese");
	
	ArgumentParser argParser;
	argParser.RegisterFlag("rename");
	argParser.RegisterFlag("convert");
	argParser.RegisterFlag("resize");
	argParser.RegisterFlag("scale");

	argParser.Parse(argc, argv);

	std::cout << std::boolalpha << "Rename: " << argParser.GetFlag("rename") << std::endl;
	std::cout << std::boolalpha << "Convert: " << argParser.GetFlag("convert") << std::endl;
	std::cout << std::boolalpha << "Resize: " << argParser.GetFlag("resize") << std::endl;
	std::cout << std::boolalpha << "Scale: " << argParser.GetFlag("scale") << std::endl;


	return 0;
}