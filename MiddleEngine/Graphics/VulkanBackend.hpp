#pragma once
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <algorithm>
#include <glm/glm.hpp>

#define MD_MAX_MESH_RENDER 2048UI16


namespace MiddleEngine
{
    namespace VulkanBackend
    {
        void initVulkan(GLFWwindow* _window);
        void drawFrame();
        void cleanup();
        const VkDevice& GetDevice();
        const VkPhysicalDevice& GetPhysicalDevice();
    };
}
