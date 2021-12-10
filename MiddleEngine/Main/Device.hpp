#pragma once

#include "../MiddleEngine.hpp"

namespace MiddleEngine
{
	namespace Device
	{
		void Create(GLFWwindow* window);
		const glm::ivec2& GetMonitorScale();
	}
}

