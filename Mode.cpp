#include "Mode.h"

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