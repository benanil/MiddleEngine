#include "MiddleEngine.hpp"

const uint32_t WIDTH = 1100;
const uint32_t HEIGHT = 700;

using namespace Rendering;

int main() {
    
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

