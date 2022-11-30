#include "Mode.h"

#include <iostream>


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
	RunImpl();
}

RenameMode::RenameMode(const std::string& filter, const std::string& folder, const std::string prefix, int startNumber)
	: Mode{ filter, folder }
	, m_Prefix{ prefix }
	, m_StartNumber{ startNumber }
{}

const std::string& RenameMode::GetModeName() const
{
	static const std::string RenameModeName = "[Rename]: ";
	return RenameModeName;
}

void RenameMode::RunImpl()
{
	std::cout << GetModeName() << " IS Working";
}