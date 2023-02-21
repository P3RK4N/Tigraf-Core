#include "Tigraf/Core/Timer.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <SDL3/SDL.h>

#include <chrono>

namespace Tigraf
{
	static const std::chrono::steady_clock::time_point ChronoStart = std::chrono::high_resolution_clock::now();

	const TimeStep& glfwTimer::advance()
	{
		double totalTime = glfwGetTime();
		m_TimeStep.m_FrameTime = totalTime - m_TimeStep.m_TotalTime;
		m_TimeStep.m_TotalTime = totalTime;
		return m_TimeStep;
	}

	const TimeStep& sdlTimer::advance()
	{
		double totalTime = SDL_GetTicks() / 1000.0;
		m_TimeStep.m_FrameTime = totalTime - m_TimeStep.m_TotalTime;
		m_TimeStep.m_TotalTime = totalTime;
		return m_TimeStep;	
	}

	const TimeStep& ChronoTimer::advance()
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();

		double totalTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - ChronoStart).count() / 1'000'000.0;
		m_TimeStep.m_FrameTime = totalTime - m_TimeStep.m_TotalTime;
		m_TimeStep.m_TotalTime = totalTime;

		return m_TimeStep;
	}

	void glfwTimer::calibrate()
	{
		m_TimeStep.m_TotalTime = glfwGetTime();
	}

	void sdlTimer::calibrate()
	{
		m_TimeStep.m_TotalTime = SDL_GetTicks() / 1000.0;
	}

	void ChronoTimer::calibrate()
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();

		double totalTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - ChronoStart).count() / 1'000'000.0;
		m_TimeStep.m_TotalTime = totalTime;
	}
}