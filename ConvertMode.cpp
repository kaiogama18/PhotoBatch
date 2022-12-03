#include "ConvertMode.h"

#include<iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>




std::ostream& operator << (std::ostream& out, ConvertMode::Format format)
{
	switch (format)
	{
	case ConvertMode::Format::JPG:
		out << "jpg";
		break;
	case ConvertMode::Format::PNG:
		out << "png";
		break;
	default:
		break;
	}

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
	std::cout << GetModeName()	<< "Modo..........: Convert"				<< std::endl;
	std::cout << GetModeName()	<< "Folder........: " << GetFolder()		<< std::endl;
	std::cout << GetModeName()	<< "Filter........: " << GetFilter()		<< std::endl;
	std::cout << GetModeName()	<< "Origin........: " << m_FromFormat		<< std::endl;
	std::cout << GetModeName()	<< "Destiny.......: " << m_ToFormat			<< std::endl;
}