#include "Tigraf/Window/Window.h"

#include "glfwWindow.h"
#include "sdlWindow.h"

namespace Tigraf
{
    Scope<Window> Tigraf::Window::createWindow(int width, int height, const char* name, bool enableVsync, std::function<void(Event&)> eventFunc)
    {
        return createScope<sdlWindow>(width, height, name, enableVsync, eventFunc);
    }
}
