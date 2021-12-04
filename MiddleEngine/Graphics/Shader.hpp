#pragma once
#include "VulkanBackend.hpp"

namespace Rendering
{
	namespace Shader
	{
		VkShaderModule CreateShaderModule(const std::string& path, const VkDevice& device);
	}
}

