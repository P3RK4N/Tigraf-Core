#pragma once
#include "Tigraf/Window/Window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Tigraf
{
	class Event;

	class glfwWindow : public Window
	{
	public:
		glfwWindow(int width, int height, const char* name, bool vsyncEnabled, std::function<void(Event&)> eventCallback);
		virtual ~glfwWindow();

		virtual const std::pair<int, int>& getSize() override;
		virtual void* getNativeHandle() override { return (void*)m_WindowHandle; }

		virtual void setVsync(bool vsyncEnabled) override { Window::setVsync(vsyncEnabled); glfwSwapInterval(vsyncEnabled); }

		virtual void onUpdate(const TimeStep& ts) override;

	protected:
		GLFWwindow* m_WindowHandle = nullptr;

		virtual void setEventCallbacks() override;

	private:
		static void onError(int error, const char* description);
	};
}