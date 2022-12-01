#include "RenameMode.h"

#include<iostream>
#include<filesystem>
#include<vector>


RenameMode::RenameMode(const std::string& filter, const std::string& folder, const std::string& prefix, int startNumber)
	: Mode{ filter, folder }
	, m_Prefix{ prefix }
	, m_StartNumber{ startNumber }
{
}

const std::string& RenameMode::GetModeName() const
{
	static const std::string RenameModeName = "[Rename]: ";
	return RenameModeName;
}

void RenameMode::RunImpl()
{
	std::cout << GetModeName() << "Mode.............: Rename" << std::endl;
	std::cout << GetModeName() << "Folder...........: " << GetFolder() << std::endl;
	std::cout << GetModeName() << "Filder...........: " << GetFilter() << std::endl;
	std::cout << GetModeName() << "Prefix...........: " << m_Prefix << std::endl;
	std::cout << GetModeName() << "Start Number.....: " << m_StartNumber << std::endl;
	//std::cout << GetModeName() << " IS Working";

	std::vector<std::filesystem::path> filesToRename;
	int numSkippedFiles = 0;

	//  Take every folder that matches of the especific filter 
	for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(GetFolder()))
	{
		const bool bIsFile = std::filesystem::is_regular_file(entry.path());
		const bool bMatchFilter = GetFilter().empty() || (entry.path().string().find(GetFilter()) != std::string::npos);

		if (bIsFile && bMatchFilter)
		{
			filesToRename.push_back(entry.path());
		}
		else
		{
			numSkippedFiles;
		}
		//std::cout << entry << std::endl;
	}

	std::cout << GetModeName() << "N�mero de arquivos encontrados: " << filesToRename.size() << std::endl;

	std::cout << GetModeName() << "N�mero de arquivos ignorados: " << numSkippedFiles << std::endl;

	// Begins Rename Process 
	int currentNumber = m_StartNumber;
	for (const std::filesystem::path& filepath : filesToRename)
	{
		const std::filesystem::path extension = filepath.extension();
		const std::string newFileName = m_Prefix + std::to_string(currentNumber) + extension.string();

		std::filesystem::path newFilepath = filepath;
		newFilepath.replace_filename(newFileName);


		try
		{
			std::filesystem::rename(filepath, newFileName);
			std::cout << GetModeName() << filepath << " -> " << newFileName << std::endl;

		}
		catch (const std::exception& exception)
		{
			std::cout << " Error to Rename \"" << filepath << "\": " << exception.what() << std::endl;
		}



		currentNumber++;
	}

}