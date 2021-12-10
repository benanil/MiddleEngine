#include "MiddleEngine.hpp"
#include "ECS/ECS.hpp"
#include "Graphics/VulkanBackend.hpp"

using namespace MiddleEngine;
    
const uint32_t WIDTH = 1100;
const uint32_t HEIGHT = 700;

int main() 
{
    
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Middle Engine", nullptr, nullptr);

    VulkanBackend::initVulkan(window);
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        VulkanBackend::drawFrame();
    }

    VulkanBackend::cleanup();

    return EXIT_SUCCESS;
}

