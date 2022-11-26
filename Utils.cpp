#include "Utils.h"
#include <algorithm> 

// Utility Function
namespace Utils
{
	std::string ToLower(std::string str)
	{
		//  Best Practice -> transform -> Algorithm
		std::transform(std::begin(str), std::end(str), std::begin(str),
			[](unsigned char c) { return std::tolower(c); });
		
		return str;
	}
}