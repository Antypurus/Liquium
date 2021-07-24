#include <Liquium.hpp>
#include <Windows.h>
#include <Core/Windows/Window.hpp>
#include <Core/Common/DataStructures/string.hpp>

int WinMain(HINSTANCE instance, HINSTANCE previnstance, PSTR lpcommand_line, int ncmd_show)
{
	using namespace liq;
	
    char arr[] = "hello";
	long_string str(arr);
    Window::Window(instance);
    return 0;
}