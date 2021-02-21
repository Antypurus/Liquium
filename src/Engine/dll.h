#pragma once

// clang-format off
#ifdef DYNAMIC_ENGINE_BUILD
    #ifdef __INTERNAL_LIQUIUM_ENGINE__
        #define LIQAPI __declspec(dllexport)
    #else
        #define LIQAPI __declspec(dllimport)
    #endif
#else
    #define LIQAPI
#endif
// clang-format on