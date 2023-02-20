#pragma once

#include "Tigraf/Renderer/GraphicsContext.h"
#include "Tigraf/Event/Event.h"

namespace Tigraf
{
	class Window
	{
		friend class Application;

	public:
		Window() = default;
		virtual ~Window() {}

		virtual std::pair<int, int> getSize() = 0;
		virtual void* getWindowHandle() = 0;

		bool isVsyncEnabled() { return m_WindowData.m_Vsync;}
		virtual void setVsync(bool enableVsync) { m_WindowData.m_Vsync = enableVsync; }

		virtual void onUpdate(const TimeStep& ts) = 0;

	public:
		static Scope<Window> createWindow
		(
			int width = 1280, 
			int height = 720, 
			const char* name = "Tigraf", 
			bool enableVsync = true, 
			std::function<void(Event&)> eventCallback = [](Event& e) { return; }
		);

	protected:

		struct WindowData
		{
			bool m_Vsync = true;
			std::function<void(Event&)> m_EventCallback = nullptr;
		};

		WindowData m_WindowData{};
		GraphicsContext m_GraphicsContext{};

		virtual void setEventCallbacks() {}
		virtual void swapBuffers() {}
	};
}