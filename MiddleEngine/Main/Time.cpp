#include "Time.hpp"

namespace MiddleEngine
{
	float Time::time = 0;
	float Time::deltaTime = 0;

	void Time::Tick(const float& dt)
	{
		Time::time += dt;
		Time::deltaTime = dt;
	}
}