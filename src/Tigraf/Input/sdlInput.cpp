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

	std::pair<int, int> sdlInput::s_CursorAbsPos = { 0, 0 };
	std::pair<int, int> sdlInput::s_CursorRelPos = { 0, 0 };

	const std::pair<int, int>& sdlInput::getCursorAbsPos()
	{
		return s_CursorAbsPos;
	}

	const std::pair<int, int>& sdlInput::getCursorRelPos()
	{
		return s_CursorRelPos;
	}

	//TODO: Add other functions
}