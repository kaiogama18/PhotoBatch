#include "ScaleMode.h"

#include <stb_image.h>

#include <iostream>


ScaleMode::ScaleMode(const std::string& filder, const std::string& folder, float scaleFactor)
	: ResizeMode{ filder, folder }
	, m_ScaleFactor{ scaleFactor }
{
}

const std::string& ScaleMode::GetModeName() const
{
	static const std::string ScaleModeName = "[Escalar]: ";
	return ScaleModeName;
}

void ScaleMode::RunImpl()
{
	std::cout << GetModeName() << "Modo..........: Escale" << std::endl;
	std::cout << GetModeName() << "Folder........: " << GetFolder() << std::endl;
	std::cout << GetModeName() << "Filter........: " << GetFilter() << std::endl;
	std::cout << GetModeName() << "Scale Factor..: " << m_ScaleFactor << std::endl;

	for (const std::filesystem::path& filepath : GetFiles())
	{
		std::cout << GetModeName() << "Scale " << filepath << std::endl;
		//ResizeImage(filepath, m_Width, m_Height);

		int width = 0;
		int height = 0;
		int numComp = 0;

		stbi_info(filepath.string().c_str(), &width, &height, &numComp);

		const int newWidth = static_cast<int>(width * m_ScaleFactor);
		const int newHeight = static_cast<int>(height * m_ScaleFactor);

		ResizeImage(filepath, newWidth, newHeight);
	}

}