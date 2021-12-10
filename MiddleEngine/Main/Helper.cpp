#include "Helper.hpp"
#include <filesystem>
#include <spdlog/spdlog.h>
#include <stdio.h>
#include <fstream>
#include <string>

namespace MiddleEngine
{
	std::string Helper::ReadAllText(const std::string& filePath)
	{
		if (!std::filesystem::exists(filePath)) {
			spdlog::warn("file is not exist! {0} ", filePath);
		}

		std::ifstream f(filePath, std::ios::in | std::ios::binary | std::ios::failbit);
		SkipBOM(f);
		const auto sz = std::filesystem::file_size(filePath);
		std::string result(sz, '\0');
		f.read(result.data(), sz);

		return result;
	}

	// byte order mask veierd thing at start of the text file
	void Helper::SkipBOM(std::ifstream& in)
	{
		char test[3] = { 0 };
		in.read(test, 3);
		if ((unsigned char)test[0] == 0xEF &&
			(unsigned char)test[1] == 0xBB &&
			(unsigned char)test[2] == 0xBF)
		{
			return;
		}
		in.seekg(0);
	}

	bool Helper::Contains(const std::string& compValue, const std::string* strings, const unsigned char& count)
	{
		for (unsigned char i = 0; i < 2; i++)
		{
			if (strings[i] == compValue) return true;
		}
		return false;
	}
	
	bool Helper::Contains(const char* compValue, const char** strings, const unsigned char& count)
	{
		for (unsigned char i = 0; i < 2; i++)
		{
			if (strcmp(strings[i], compValue) == 0) return true;
		}
		return false; 
	}
}