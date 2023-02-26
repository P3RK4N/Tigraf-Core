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

		virtual const std::pair<int, int> getSize() = 0;

		/**
			Gets SDL_Window*
		*/
		virtual void* getNativeHandle() = 0;

		/**
			Gets you native graphics context. In case of OpenGL, it will return SDL_GLContext*
		*/
		virtual void* getNativeContext() = 0;

		/**
			You can set this function from a client side which will take native event (SDL_Event*). 
			If it returns true, event will be considered finished and will not be propagated trough Engine.
		*/
		void setNativeEventCallback(std::function<bool(void*)> nativeCallback) { m_NativeEventCallback = nativeCallback; }

		/**
			Makes context of this window current again in case client made other context current previously.
		*/
		virtual void makeCurrent() = 0;

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

		std::function<bool(void*)> m_NativeEventCallback = nullptr;

		virtual void setEventCallbacks() {}
		virtual void swapBuffers() {}
	};
}