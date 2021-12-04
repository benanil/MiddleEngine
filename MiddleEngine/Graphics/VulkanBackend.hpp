#pragma once
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <optional>
#include <algorithm>

namespace Rendering
{
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;
    
        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };
    
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
    
    class VulkanBackend
    {
    public:
        static void initVulkan(GLFWwindow* _window);
        static void drawFrame();
        static void cleanup();
        static const VkDevice& GetDevice();
    };
}
