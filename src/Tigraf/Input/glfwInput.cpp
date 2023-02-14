#include "Tigraf/Input/glfwInput.h"

#include "Tigraf/Window/glfwWindow.h"
#include "Tigraf/Core/Application.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Tigraf
{
	const bool glfwInput::isKeyDown(int keycode) 
	{	
		return glfwGetKey((GLFWwindow*)Application::s_Instance->getWindow()->getWindowHandle(), keycode) == GLFW_PRESS;		
	}

	const bool glfwInput::isKeyUp(int keycode)
	{	
		return glfwGetKey((GLFWwindow*)Application::s_Instance->getWindow()->getWindowHandle(), keycode) == GLFW_RELEASE;	
	}

	const bool glfwInput::isButtonDown(int keycode)
	{
		return glfwGetMouseButton((GLFWwindow*)Application::s_Instance->getWindow()->getWindowHandle(), keycode) == GLFW_PRESS;	
	}

	const std::pair<int, int> glfwInput::getCursorPos()
	{
		double x, y;
		glfwGetCursorPos((GLFWwindow*)Application::s_Instance->getWindow()->getWindowHandle(), &x, &y);

		return { (int)x, (int)y };
	}
}