#pragma once
#include "Tigraf/Window/Window.h"

#include <SDL3/SDL.h>

namespace Tigraf
{
	class Event;

	class sdlWindow : public Window
	{
	public:
		sdlWindow(int width, int height, const char* name, bool vsyncEnabled, std::function<void(Event&)> eventCallback);
		virtual ~sdlWindow();

		virtual std::pair<int, int> getSize() override;
		virtual void* getWindowHandle() override { return (void*)m_WindowHandle; }

		virtual void setVsync(bool vsyncEnabled) override { Window::setVsync(vsyncEnabled); SDL_GL_SetSwapInterval(vsyncEnabled); }

		virtual void onUpdate(const TimeStep& ts) override;

	protected:
		SDL_Window* m_WindowHandle = nullptr;
		SDL_GLContext m_WindowContext = NULL;

		virtual void setEventCallbacks() override;

	private:
		static void onError(int error, const char* description);

		//Event Callbacks
		static void WindowResizeCallback(sdlWindow* window);
		static void WindowCloseCallback(sdlWindow* window);
	};
}