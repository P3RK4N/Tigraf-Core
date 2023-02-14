#pragma once

namespace Tigraf
{
	class glfwInput
	{
	public:
		static const bool isKeyDown(int keycode);
		static const bool isKeyUp(int keycode);
		static const bool isButtonDown(int keycode);
		static const std::pair<int, int> getCursorPos();

	};
}