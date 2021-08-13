#include <Liquium.hpp>
#include <Windows.h>
#include <Core/Windows/Window.hpp>
#include <Core/Common/DataStructures/string.hpp>

int WinMain(HINSTANCE instance, HINSTANCE previnstance, PSTR lpcommand_line, int ncmd_show)
{
	using namespace liq;
	
	long_string str = "string1";
	long_string str2 = "string2";
	long_string str3 = str + str2;
	
    bool res = (str == str2);
	
    Window::Window(instance);
    return res;
}