#include "ResizeMode.h"

#include <iostream>

ResizeMode::ResizeMode(const std::string& filter,
	const std::string& folder,
	int width,
	int height) : Mode{ filter, folder }
	, m_Width{ width }
	, m_Height{ height }
{
}

const std::string& ResizeMode::GetModeName() const
{
	static const std::string ResizeModeName = "[Resize]: ";
	return ResizeModeName;
}

void ResizeMode::ResizeImage(const std::filesystem::path& filepath, int newWidth, int newHeight) const
{

}

void ResizeMode::RunImpl()
{
	std::cout << GetModeName() << "Modo..........: Resize" << std::endl;
	std::cout << GetModeName() << "Folder........: " << GetFolder() << std::endl;
	std::cout << GetModeName() << "Filter........: " << GetFilter() << std::endl;
	std::cout << GetModeName() << "Width........: " << m_Width << std::endl;
	std::cout << GetModeName() << "Height.......: " << m_Height << std::endl;

	if (m_Width > 0 && m_Height > 0)
	{
		for (const std::filesystem::path& filepath : GetFiles())
		{
			std::cout << GetModeName() << "Resize " << filepath << std::endl;
			ResizeImage(filepath, m_Width, m_Height);
		}

	}
}