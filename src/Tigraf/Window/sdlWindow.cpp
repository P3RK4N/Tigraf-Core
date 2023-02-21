#include "sdlWindow.h"

#include <glad/glad.h>

//#include <SDL3/SDL_syswm.h>
#include <SDL3/SDL_events.h>

namespace Tigraf
{
	static int status = 0;

	sdlWindow::sdlWindow(int width, int height, const char* name, bool vsyncEnabled, std::function<void(Event&)> eventCallback)
	{
		m_WindowHandle = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_FOCUS);
		m_WindowData.m_Vsync = vsyncEnabled;
		m_WindowData.m_EventCallback = eventCallback;

		TIGRAF_CORE_ASSERT(m_WindowHandle, "Window creation failed!");

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		m_WindowContext = SDL_GL_CreateContext(m_WindowHandle);

		TIGRAF_CORE_ASSERT(m_WindowContext, "Failed to create OpenGL context!");

		SDL_GL_MakeCurrent(m_WindowHandle, m_WindowContext);

		m_GraphicsContext.init = []()
		{
			status = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
			TIGRAF_CORE_ASSERT(status, "Could not initialize graphics context!");

			//-------------
			CORE_INFO("GRAPHICS CONTEXT");
			CORE_INFO("\tVendor: {0}", (char*)glGetString(GL_VENDOR));
			CORE_INFO("\tRenderer: {0}", (char*)glGetString(GL_RENDERER));
			CORE_INFO("\tVersion: {0}\n", (char*)glGetString(GL_VERSION));
			//-------------

			//------------------------
			CORE_INFO("UNIFORM BUFFERS:");
			
			glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &status);
			CORE_INFO("\tMAX UNIFORM BLOCK SIZE: {0}", status);

			glGetIntegerv(GL_MAX_COMBINED_UNIFORM_BLOCKS, &status);
			CORE_INFO("\tMAX COMBINED UNIFORM BLOCKS: {0}\n", status);
			//-------------------------

			//-------------------------
			CORE_INFO("TEXTURES:");

			glGetIntegerv(GL_MAX_TEXTURE_SIZE, &status);
			CORE_INFO("\tMAX TEXTURE SIZE: {0}x{0}", status);

			glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &status);
			CORE_INFO("\tMAX COMBINED TEXTURE IMAGE UNITS: {0}\n", status);
			//--------------------------
		};

		m_GraphicsContext.swapBuffers = [this]()
		{
			SDL_GL_SwapWindow(m_WindowHandle);
		};
		

		m_GraphicsContext.init();	//TODO: Maybe isn't semantically correct

		SDL_GL_SetSwapInterval(vsyncEnabled);
	}

	sdlWindow::~sdlWindow()
	{
		SDL_GL_MakeCurrent(m_WindowHandle, NULL);
		SDL_GL_DeleteContext(m_WindowContext);
		
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		SDL_Quit();

		m_WindowHandle = nullptr;
		m_WindowContext = nullptr;
	}

	std::pair<int,int> sdlWindow::getSize()
	{
		int width, height;
		SDL_GetWindowSizeInPixels(m_WindowHandle, &width, &height);
		return { width,height };
	}

	void sdlWindow::onError(int error, const char* description)
	{
		fprintf(stderr, "Error: %s\n", description);
	}

	void sdlWindow::onUpdate(const TimeStep& ts)
	{
		static float timer = 0.0f;
		static float frames = 0;

		timer += ts;
		frames += (bool)(ts > 0.0f);

		if(timer > 1.0f)
		{
			std::string title = std::format("Tigraf - Frame: {}FPS / {}ms", frames, 1.0f/frames, ts.m_TotalTime);
			timer -= 1.0f;
			frames = 0;
			SDL_SetWindowTitle(m_WindowHandle, title.c_str());
		}

		m_GraphicsContext.swapBuffers(); 
		
		//TODO: Event loop and function callback
		SDL_Event e;
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case SDL_EVENT_QUIT: 
					[&e, this]()
					{
						Event e{ EVENT_TYPE::CLOSE, nullptr };
						m_WindowData.m_EventCallback(e);
					}();
					break;

				case SDL_EVENT_WINDOW_RESIZED:
					[&e, this]()
					{
						auto [w, h] = getSize();
						ResizeData data{ w, h };
						Event e{ EVENT_TYPE::RESIZE, &data };
						m_WindowData.m_EventCallback(e);
					}();
					break;

			}
		}
	}

	void sdlWindow::setEventCallbacks()
	{

	}

	void sdlWindow::WindowCloseCallback(sdlWindow* window)
	{
		Event e{ EVENT_TYPE::CLOSE, nullptr };

		window->m_WindowData.m_EventCallback(e);
	}

	void sdlWindow::WindowResizeCallback(sdlWindow* window)
	{
	
	}
}