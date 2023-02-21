#pragma once

#include "Tigraf/Input/sdlKeycodes.h"

namespace Tigraf
{
	class sdlInput
	{
	public:
		static const bool isKeyDown(int keycode);
		static const bool isKeyUp(int keycode);
		static const bool isMouseButtonDown(int keycode);
		static const std::pair<int, int> getCursorPos();

	};
}