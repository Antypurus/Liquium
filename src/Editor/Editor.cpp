#include <Liquium.hpp>
#include <Windows.h>
#include <Core/Windows/Window.hpp>
#include <Core/Common/DataStructures/string.hpp>

int WinMain(HINSTANCE instance, HINSTANCE previnstance, PSTR lpcommand_line, int ncmd_show)
{
    liq::Window::Window(instance);
    return 0;
}