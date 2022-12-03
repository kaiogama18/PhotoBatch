#include "Mode.h"

#include "ArgumentParser.h"
#include "RenameMode.h"
#include "ConvertMode.h"

#include <iostream>
#include <array>
#include <filesystem>
#include <chrono>


Mode::Mode(const std::string& filter, const std::string& folder)
	: m_Filter{ filter }
	, m_Folder{ folder }
{

}

const std::string& Mode::GetFilter() const
{
	return m_Filter;
}

const std::string& Mode::GetFolder() const
{
	return m_Folder;
}



void Mode::Run()
{
	using ClockT = std::chrono::high_resolution_clock;

	ClockT::time_point startTime = ClockT::now();
	RunImpl();
	ClockT::time_point endTime = ClockT::now();

	ClockT::duration elapsedTime = endTime - startTime;
	std::chrono::milliseconds elapsedTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime);

	std::cout << GetModeName() << "Completed Operation in: " << elapsedTimeMs.count() << " ms" << std::endl;


}

std::vector<std::filesystem::path> Mode::GetFiles(const std::filesystem::path& extension) const
{
	std::vector<std::filesystem::path> files;
	int numSkippedFiles = 0;

	//  Take every folder that matches of the especific filter 
	for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(GetFolder()))
	{
		const bool bIsFile = std::filesystem::is_regular_file(entry.path());
		const bool bMatchFilter = GetFilter().empty() || (entry.path().string().find(GetFilter()) != std::string::npos);
		const bool bMatchExtension = extension.empty() || (entry.path().extension() == extension);

		if (bIsFile && bMatchFilter)
		{
			files.push_back(entry.path());
		}
		else
		{
			numSkippedFiles;
		}
		//std::cout << entry << std::endl;
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

std::unique_ptr<Mode> CreateMode(const ArgumentParser& argParser)
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

	if (folder.empty())
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

		return std::make_unique<RenameMode>(filter, folder, prefix, startNumer);
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

		const std::map<std::string, ConvertMode::Format> convertOptionsMap = {
			{"jpg", ConvertMode::Format::JPG},
			{"png", ConvertMode::Format::PNG}
		};

		return std::make_unique<ConvertMode>(filter, folder, convertOptionsMap.at(from), convertOptionsMap.at(to));
	}

	return nullptr;
}

