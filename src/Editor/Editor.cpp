#include <Liquium.hpp>
#include <Windows.h>

constexpr int strlen_(const char* str)
{
    unsigned int len = 0;
    for(unsigned int i = 0; str[i] != 0; ++i)
    {
        len++;
    }
    return len;
}

int WinMain(HINSTANCE instance, HINSTANCE previnstance, PSTR lpcommand_line, int ncmd_show)
{
    int ret = strlen_("Hello there");
    ret += 5;
    return ret;
}