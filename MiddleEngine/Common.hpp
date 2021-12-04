#pragma once
#include <filesystem>

#define MD_ASSETS_PATH(x) std::filesystem::current_path().parent_path().append("Assets").append(x).u8string()