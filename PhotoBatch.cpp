#include <iostream>
#include<iomanip>
#include<array>
#include<filesystem>

#include "ArgumentParser.h"
#include "Mode.h"

namespace Args
{
	namespace Flags
	{
		static constexpr const char* Rename = "rename";
		static constexpr const char* Convert = "convert";
		static constexpr const char* Resize = "resize";
		static constexpr const char* Scale = "scale";
		static constexpr const char* Help = "help";
	}

	namespace Opts
	{
		static constexpr const char* Folder = "folder";
		static constexpr const char* Filter = "filter";
		static constexpr const char* Width = "width";
		static constexpr const char* Height = "height";
		static constexpr const char* Amount = "amount";
		static constexpr const char* Prefix = "prefix";
		static constexpr const char* StartNumber = "startnumber";
		static constexpr const char* From = "from";
		static constexpr const char* To = "to";

	}
}

const std::string& GetInvalidChars()
{
	static const std::string invalidCharacters = "\\/*?\"<>|:";
	return invalidCharacters;
}

bool HasInvalidChars(const std::string& str)
{
	const bool bHasInvalidChars = str.find_first_of(GetInvalidChars()) != std::string::npos;
	return bHasInvalidChars;
	
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

	//Validate if the filter is a valid string
	const std::string filter = argParser.GetOptionAs<std::string>(Args::Opts::Filter);
	if (!filter.empty() && HasInvalidChars(filter))
	{
		throw std::invalid_argument("The filter does not contain: " + GetInvalidChars());
	}

	//Validate the Risize mode
	if (bResizeMode)
	{
		int width = 0;
		int height = 0;

		try
		{
			width = argParser.GetOptionAs<int>(Args::Opts::Width);
			height = argParser.GetOptionAs<int>(Args::Opts::Height);
		}
		catch (const std::invalid_argument&)
		{
			throw std::invalid_argument("The entered value is not a valid number!");
		}



		if (width <= 0 || height <= 0)
		{
			throw std::invalid_argument("Width e Height devem ser maiores que zero");
		}

		if (filter.empty())
		{
			throw std::invalid_argument("Filter cannot be blank in mode relize");
		}
	}

	// Scale Mode Validaded
	if (bScaleMode)
	{
		float amount = 0.0f;

		try
		{
			amount = argParser.GetOptionAs<float>(Args::Opts::Amount);
		}
		catch (const std::invalid_argument&)
		{
			throw std::invalid_argument("Amount value is not a valid number");
		}


		//In scale mode, 'amount' must be greater to be zero
		if (amount <= 0.0f)
		{
			throw std::invalid_argument("Amount must be greater to be zero ");

		}

		if (filter.empty())
		{
			throw std::invalid_argument("Filter cannot be blank in mode scale");
		}

	}

	// Rename Mode Validaded
	if (bRenameMode)
	{

		int startNumer = -1;
		try
		{
			startNumer = argParser.GetOptionAs<int>(Args::Opts::StartNumber);
		}
		catch (const std::invalid_argument&)
		{
			throw std::invalid_argument("StartNumber value is not a valid number");
		}

		std::string prefix = argParser.GetOptionAs<std::string>(Args::Opts::Prefix);

		if (startNumer < 0)
		{
			throw std::invalid_argument("StartNumber  must be greater to be zero");
		}


		if (!prefix.empty() && HasInvalidChars(prefix))
		{
			throw std::invalid_argument("The Prefix does not contain: " + GetInvalidChars());
		}
	
	}

	// Convert Mode Validaded
	if (bConvertMode)
	{
		const std::string from = argParser.GetOptionAs<std::string>(Args::Opts::From);
		const std::string to = argParser.GetOptionAs<std::string>(Args::Opts::To);
		const std::array<std::string, 2> convertOptions = { "jpg","png" };
		
		const bool bIsFromValid = std::find(std::begin(convertOptions), std::end(convertOptions), from) != std::end(convertOptions);
		const bool bIsToValid = std::find(std::begin(convertOptions), std::end(convertOptions), to) != std::end(convertOptions);
		

		if (!bIsFromValid || !bIsToValid)
		{
			throw std::invalid_argument("From and To must be greater to be jpg or png");
		}
		if (from == to)
		{
			throw std::invalid_argument("From and To must be different");
		}
	}

		
}

int main(int argc, char* argv[])
{	
	setlocale(LC_ALL, "portuguese");
	setlocale(LC_ALL, "en_US");
	
	ArgumentParser argParser;

	// Register as flags do PhotoBatch
	argParser.RegisterFlag(Args::Flags::Rename);
	argParser.RegisterFlag(Args::Flags::Convert);
	argParser.RegisterFlag(Args::Flags::Resize);
	argParser.RegisterFlag(Args::Flags::Scale);
	argParser.RegisterFlag(Args::Flags::Help);
	
	argParser.RegisterOption(Args::Opts::Folder);
	argParser.RegisterOption(Args::Opts::Amount);
	argParser.RegisterOption(Args::Opts::Filter);
	argParser.RegisterOption(Args::Opts::Width);
	argParser.RegisterOption(Args::Opts::Height);
	argParser.RegisterOption(Args::Opts::Prefix);
	argParser.RegisterOption(Args::Opts::StartNumber);
	argParser.RegisterOption(Args::Opts::From);
	argParser.RegisterOption(Args::Opts::To);

	argParser.SetHelpMessage(R"( [USO]: PhotoBatch --[Rename|Scale|Convert|Resize] [Option]

    O PhotoBatch possui 4 modos de operação. Somente um modo pode estar ativo.
    Para ativar um modo escolha uma das seguintes flags:

    --Rename  : Ativa o modo para renomear arquivos
    --Convert : Ativa o modo para converter arquivos
    --Resize  : Ativa o modo para redimensionar arquivos
    --Scale   : Ativa o modo para escalar arquivos

As seguintes opções são comuns a todos os modos:
    --Folder  : Especifica a pasta onde o PhotoBatch irá atuar
    --Filter  : Especifica o filtro usado para selecionar arquivos

Opções do modo Rename:

    No modo Rename, cada arquivo selecionado será renomeado para o formato
    <Prefix>_<N>.<ext>, onde <Prefix> e <N> são especificados através de opções.
    <ext> é a extensão do arquivo que permanece inalterada.

    --Prefix=<Prefix> : Prefixo usado ao renomear os arquivos
    --StartNumber=<N> : Número inicial a ser adicionado em cada arquivo que for renomeado

Opções do modo Convert:

    No modo Convert, cada arquivo selecionado será convertido do formato <from> para
    o formato <to>. <from> e <to> não podem ser iguais. O nome do arquivo permanece
    inalterado.

    --From=<jpg|png> : Extensão de origem para conversão
    --To=<jpg|png>   : Extensão de destino para conversão

Opções do modo Resize:

    No modo Resize, cada arquivo selecionado será redimensionado para as dimensões
    especificadas nas seguintes opções. Note que N >= 1.

    --Width=<N>  : Novo comprimento da imagem
    --Height=<N> : Nova altura da imagem

Opções do modo Scale:

    No modo Scale, cada arquivo selecionado será escalado uniformemente pelo
    fator especificado pelas seguintes opções. Note que N > 0 e será interpretado
    como um número em ponto flutuante.

    --Amount=<N> : Fator de escala a ser aplicado em cada imagem selecionada.

Exemplos de uso:

    Renomear todos os arquivos da pasta "C:\Viagem" com a extensão ".png" para Viagem_N.png, onde N começa do 0

	    PhotoBatch --Rename --Folder="C:\Viagem" --Filter=".png" --StartNumber=0

    Redimensionar todos os arquivos na pasta "C:\Viagem" com a extensão ".jpg" para o tamanho 500x500

        PhotoBatch --Resize --Folder="C:\Viagem" --Filter=".jpg" --Width=500 --Height=500

    Converter todos os arquivos da pasta "C:\Viagem" de "png" para "jpg"

        PhotoBatch --Convert --Folder="C:\Viagem" --From=png --To=jpg

    Reduzir o pela metade o tamanho de todos os arquivos "png" da pasta "C:\Viagem"

        PhotoBatch --Scale --Folder="C:\Viagem" --Filter=".png" --Amount=0.5
)"); //String escapada

	argParser.Parse(argc, argv);

	if (argParser.GetFlag(Args::Flags::Help))
	{
		std::cout << argParser.SetHelpMessage() << std::endl;
	}
	else
	{
		try
		{
			ValidadeArguments(argParser);
		}
		catch (const std::exception& exception)
		{
			std::cerr << exception.what() << std::endl;
			std::cerr << "More Information use: --help";
		}
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