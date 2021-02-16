#include <Liquium.hpp>
#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CLOSE:
        {
            DestroyWindow(hwnd);
            return 0;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        default:return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}


int WinMain(HINSTANCE instance, HINSTANCE prev_instance, PSTR lp_command_line, int n_cmd_show)
{
    // Register the window class.
    const char CLASS_NAME[]  = "Sample Window Class";
    
    WNDCLASS wc = {};
    
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = instance;
    wc.lpszClassName = CLASS_NAME;
    
    RegisterClass(&wc);
    
    // Create the window.
    
    HWND hwnd = CreateWindowEx(
                               0,                              // Optional window styles.
                               CLASS_NAME,                     // Window class
                               "Learn to Program Windows",    // Window text
                               WS_OVERLAPPEDWINDOW,            // Window style
                               
                               // Size and position
                               CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                               
                               NULL,       // Parent window    
                               NULL,       // Menu
                               instance,  // Instance handle
                               NULL        // Additional application data
                               );
    
    if (hwnd == NULL)
    {
        return 0;
    }
    
    ShowWindow(hwnd, n_cmd_show);
    
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    PostQuitMessage(0);
    
    return 0;
}