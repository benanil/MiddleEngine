#include "Device.hpp"

namespace MiddleEngine
{
	namespace Device
	{
		glm::ivec2 MonitorScale;

		void Create(GLFWwindow* window)
		{
			const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			MonitorScale.x = vidMode->width;
			MonitorScale.y = vidMode->height;
			std::cout << "monitor size: " << vidMode->width << " " << vidMode->height << std::endl;
		}

		const glm::ivec2& GetMonitorScale()
		{
			return MonitorScale;
		}
	}
}