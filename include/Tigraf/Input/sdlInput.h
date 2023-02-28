#pragma once

#include "Tigraf/Input/sdlKeycodes.h"

namespace Tigraf
{
	class sdlInput
	{
		friend class Window;
		friend class sdlWindow;

	public:
		static const bool isKeyDown(int keycode);
		static const bool isKeyUp(int keycode);
		static const bool isMouseButtonDown(int keycode);
		static const std::pair<int, int>& getCursorAbsPos();
		static const std::pair<int, int>& getCursorRelPos();

	private:
		static std::pair<int, int> s_CursorAbsPos;
		static std::pair<int, int> s_CursorRelPos;
	};
}