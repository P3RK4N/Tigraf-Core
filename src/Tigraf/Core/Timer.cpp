#include "Tigraf/Core/Timer.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Tigraf
{
	const TimeStep& glfwTimer::advance()
	{
		double totalTime = glfwGetTime();
		m_TimeStep.m_FrameTime = totalTime - m_TimeStep.m_TotalTime;
		m_TimeStep.m_TotalTime = totalTime;
		return m_TimeStep;
	}
}