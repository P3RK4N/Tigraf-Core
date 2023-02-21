#include "Tigraf/Input/sdlInput.h"

#include "Tigraf/Window/sdlWindow.h"
#include "Tigraf/Core/Application.h"

namespace Tigraf
{
	const bool sdlInput::isKeyDown(int keycode) 
	{	
		return SDL_GetKeyboardState(NULL)[keycode];
	}

	const bool sdlInput::isKeyUp(int keycode)
	{	
		return !SDL_GetKeyboardState(NULL)[keycode];	
	}

	const bool sdlInput::isMouseButtonDown(int keycode)
	{
		return SDL_GetMouseState(NULL, NULL) && keycode;
	}

	const std::pair<int, int> sdlInput::getCursorPos()
	{
		float x, y;
		SDL_GetMouseState(&x, &y);

		return { (int)x, (int)y };
	}

	//TODO: Add other functions
}