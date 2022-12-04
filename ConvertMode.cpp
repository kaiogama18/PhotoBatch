#include "ConvertMode.h"

#include<iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

std::string ToString(ConvertMode::Format format)
{
	switch (format)
	{
	case ConvertMode::Format::JPG:
		return "jpg";
		break;
	case ConvertMode::Format::PNG:
		return "png";
		break;
	default:
		break;
	}
	return "";
}

std::ostream& operator << (std::ostream& out, ConvertMode::Format format)
{
	out << ToString(format);
	return out;
}

ConvertMode::ConvertMode(const std::string& filter,
	const std::string& folder,
	Format fromFormat,
	Format toFormat)
	: Mode{ filter, folder }
	, m_FromFormat{ fromFormat }
	, m_ToFormat{ toFormat }
{
}

const std::string& ConvertMode::GetModeName() const
{
	static const std::string ConvertMode = "[Converter]: ";
	return ConvertMode;

}

void ConvertMode::RunImpl()
{
	std::cout << GetModeName() << "Modo..........: Convert" << std::endl;
	std::cout << GetModeName() << "Folder........: " << GetFolder() << std::endl;
	std::cout << GetModeName() << "Filter........: " << GetFilter() << std::endl;
	std::cout << GetModeName() << "Origin........: " << m_FromFormat << std::endl;
	std::cout << GetModeName() << "Destiny.......: " << m_ToFormat << std::endl;

	const std::filesystem::path fromExtension = "." + ToString(m_FromFormat);

	for (const std::filesystem::path& filepath : GetFiles(fromExtension))
	{
		std::cout << GetModeName() << "Convert: " << filepath << std::endl;

		int width = 0;
		int height = 0;
		int numComp = 0;
		const int numReqComp = 3;

		if (unsigned char* data = stbi_load(filepath.string().c_str(), &width, &height, &numComp, numReqComp))
		{
			std::filesystem::path destFilepath = filepath;
			destFilepath.replace_extension(ToString(m_ToFormat));

			int writeResult = 0;
			switch (m_ToFormat)
			{
			case Format::PNG:
				writeResult = stbi_write_png(destFilepath.string().c_str(), width, height, numComp, data, 0);
				break;
			case Format::JPG:
				writeResult = stbi_write_jpg(destFilepath.string().c_str(), width, height, numComp, data, 50);
				break;
			default:
				break;
			}

			if (writeResult == 0)
			{
				std::cout << GetModeName() << "Error to conect! " << filepath << std::endl;
			}

			stbi_image_free(data);
		}
		else
		{
			std::cout << GetModeName() << " Error Connecting " << filepath << std::endl;
		}
	}
}