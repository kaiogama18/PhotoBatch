#include <iostream>
#include<iomanip>

#include "ArgumentParser.h"
#include "Mode.h"

#include <stb_image.h>

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

    O PhotoBatch possui 4 modos de opera��o. Somente um modo pode estar ativo.
    Para ativar um modo escolha uma das seguintes flags:

    --Rename  : Ativa o modo para renomear arquivos
    --Convert : Ativa o modo para converter arquivos
    --Resize  : Ativa o modo para redimensionar arquivos
    --Scale   : Ativa o modo para escalar arquivos

As seguintes op��es s�o comuns a todos os modos:
    --Folder  : Especifica a pasta onde o PhotoBatch ir� atuar
    --Filter  : Especifica o filtro usado para selecionar arquivos

Op��es do modo Rename:

    No modo Rename, cada arquivo selecionado ser� renomeado para o formato
    <Prefix>_<N>.<ext>, onde <Prefix> e <N> s�o especificados atrav�s de op��es.
    <ext> � a extens�o do arquivo que permanece inalterada.

    --Prefix=<Prefix> : Prefixo usado ao renomear os arquivos
    --StartNumber=<N> : N�mero inicial a ser adicionado em cada arquivo que for renomeado

Op��es do modo Convert:

    No modo Convert, cada arquivo selecionado ser� convertido do formato <from> para
    o formato <to>. <from> e <to> n�o podem ser iguais. O nome do arquivo permanece
    inalterado.

    --From=<jpg|png> : Extens�o de origem para convers�o
    --To=<jpg|png>   : Extens�o de destino para convers�o

Op��es do modo Resize:

    No modo Resize, cada arquivo selecionado ser� redimensionado para as dimens�es
    especificadas nas seguintes op��es. Note que N >= 1.

    --Width=<N>  : Novo comprimento da imagem
    --Height=<N> : Nova altura da imagem

Op��es do modo Scale:

    No modo Scale, cada arquivo selecionado ser� escalado uniformemente pelo
    fator especificado pelas seguintes op��es. Note que N > 0 e ser� interpretado
    como um n�mero em ponto flutuante.

    --Amount=<N> : Fator de escala a ser aplicado em cada imagem selecionada.

Exemplos de uso:

    Renomear todos os arquivos da pasta "C:\Viagem" com a extens�o ".png" para Viagem_N.png, onde N come�a do 0

	    PhotoBatch --Rename --Folder="C:\Viagem" --Filter=".png" --StartNumber=0

    Redimensionar todos os arquivos na pasta "C:\Viagem" com a extens�o ".jpg" para o tamanho 500x500

        PhotoBatch --Resize --Folder="C:\Viagem" --Filter=".jpg" --Width=500 --Height=500

    Converter todos os arquivos da pasta "C:\Viagem" de "png" para "jpg"

        PhotoBatch --Convert --Folder="C:\Viagem" --From=png --To=jpg

    Reduzir o pela metade o tamanho de todos os arquivos "png" da pasta "C:\Viagem"

        PhotoBatch --Scale --Folder="C:\Viagem" --Filter=".png" --Amount=0.5
)"); //String escapada

	//argParser.Parse(argc, argv);

	if (argParser.GetFlag(Args::Flags::Help))
	{
		std::cout << argParser.SetHelpMessage() << std::endl;
	}
	else
	{
		try
		{
			if (std::unique_ptr<Mode> PhotoBatchMode = CreateMode(argParser))
			{
				PhotoBatchMode->Run();
			}
		}
		catch (const std::exception& exception)
		{
			std::cerr << exception.what() << std::endl;
			std::cerr << "More Information use: --help";
		}
	}
	return 0;
}