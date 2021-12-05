#pragma once
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>

#include <iostream>
#include <optional>
#include <algorithm>

namespace Rendering
{
    class VulkanBackend
    {
    public:
        static void initVulkan(GLFWwindow* _window);
        static void drawFrame();
        static void cleanup();
        static const VkDevice& GetDevice();
    };
}
