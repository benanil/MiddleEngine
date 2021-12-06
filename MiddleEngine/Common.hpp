#pragma once
#include <filesystem>
#include <vector>
#include <array>

static inline std::string MD_ASSETS_PATH(std::string path)
{
	return std::filesystem::current_path().parent_path().append("Assets").append(path).u8string();
}
