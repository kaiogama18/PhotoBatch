#include <iostream>
#include<iomanip>
#include<map>
#include<algorithm>

// Utility Function
std::string ToLower(std::string str)
{
	//  Best Practice -> transform -> Algorithm
	std::transform(std::begin(str), std::end(str), std::begin(str),
		[](unsigned char c) { return std::tolower(c); });
	
	return str;
}

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
		if (argc > 1)
		{
			for (int i = 1; i < argc; ++i)
			{
				//std::string arg = argv[i];
				std::string arg = ToLower(argv[i]);

				// Argument needs the minimum three letter
				// "--" [0,1] and the three letter
				if (arg.length() >= 3)
				{
					if (arg[0] == '-' && arg[1] == '-')
					{
						//Remove [0,1] "--" [0,1]
						arg = arg.substr(2);

						//After arg.substr: "rename"
						if (arg.find_first_of('-') != std::string::npos)
						{
							//Is option
						}
						else
						{
							// Is flag

							auto flagIt = m_Flags.find(arg);
							if (flagIt != std::end(m_Flags))
							{
								// We found a registered flag
								flagIt->second = true;
							}
						}
					}
				}
			}
		}
	}


private:
	// m_Falsgs --> todo nome que tem m_ -> é membro da classe
	std::map<std::string, bool > m_Flags; //container do Sql
};

int main(int argc, char* argv[])
{	
	setlocale(LC_ALL, "portuguese");
	
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