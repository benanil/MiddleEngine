#include "../MiddleEngine.hpp"
#include <Windows.h>
#include "Device.hpp"

namespace MiddleEngine
{
	namespace Input
	{
		void _SetCursorPos(const float& x, const float& y);

		bool GetKey(int key)
		{
			return true;//; glfwGetKey(GetWindow(), key) == GLFW_PRESS;
		}
	
		void InfiniteMouse()
		{
			POINT point;
			GetCursorPos(&point);
			const glm::ivec2 monitorScale = Device::GetMonitorScale();

			if (point.x > monitorScale.x - 2) { _SetCursorPos(2, point.y); }
			if (point.y > monitorScale.y - 2) { _SetCursorPos(point.x, 2); }
			if (point.x < 2) { _SetCursorPos(monitorScale.x - 3, point.y); }
			if (point.y < 2) { _SetCursorPos(point.x, monitorScale.y - 3); }
		}

		void _SetCursorPos(const float& x, const float& y)
		{
			// glfwSetCursorPos(GetWindow(), x, y);
			SetCursorPos(x, y);
		}

		bool GetMouseButton(int key)
		{
			return true;//;glfwGetMouseButton(GetWindow(), key);
		}

	    glm::ivec2& GetMouseRaw()
		{
			POINT point;
			GetCursorPos(&point);
			glm::ivec2 vec((int)point.x, (int)point.y);
			return vec;
		}
	}
}