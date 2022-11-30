#pragma once

#include<string>

class Mode
{
public:
	Mode(const std::string& filter, const std::string& folder);

	const std::string& GetFilter() const;
	const std::string& GetFolder() const;

	virtual const std::string& GetModeName() const = 0;

	void Run();

protected:
	virtual void RunImpl() = 0;

	std::string m_Filter;
	std::string m_Folder;
};