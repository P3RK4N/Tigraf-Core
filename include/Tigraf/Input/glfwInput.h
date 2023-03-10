#pragma once
#include "Tigraf/Input/Keycodes.h"

namespace Tigraf
{
	class [[deprecated("Consider using sdlInput")]] glfwInput
	{
	public:
		static const bool isKeyDown(int keycode);
		static const bool isKeyUp(int keycode);
		static const bool isMouseButtonDown(int keycode);
		static const std::pair<int, int> getCursorPos();

	};
}