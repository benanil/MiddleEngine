#pragma once
#include <iostream>
#include <filesystem>
#include <string>

namespace MiddleEngine
{
	namespace Helper
	{	
		std::filesystem::path AssetsPath();
		bool Contains(const char* compValue, const char** strings, const unsigned char& count);
		bool Contains(const std::string& compValue, const std::string* strings, const unsigned char& count);
		std::string ReadAllText(const std::string& filePath);
		void SkipBOM(std::ifstream& in);
	};
}