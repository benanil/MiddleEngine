#pragma once
#include <filesystem>
#include <vector>
#include <array>
#include <cstdint>
#include <glm/glm.hpp>
#include <string>

#define MD_HAS_STENCIL_FORMAT(format) format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT
// This is because sometimes I don't want to extra tab. with this visual studio ignores, my bad england :>
#define MD_NAMESPACE_START namespace MiddleEngine {
#define MD_NAMESPACE_END }

#define MD_DEFAULT_BUFFER_PROPERTIES VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
#define MD_ASSETS_PATH(path) std::filesystem::current_path().parent_path().append("Assets").append(path).u8string()

