#pragma once
#include "../types.hpp"

namespace liq
{
    
#define SMALL_STRING_OPTIMIZATION_SIZE 56 //NOTE(Tiago) if the whole struct can be packed into 64bytes it will fit into a cache line when using small string optimizations
    
    struct string
    {
        union string_internal
        {
            uint8* large_string;
            uint8 small_string[SMALL_STRING_OPTIMIZATION_SIZE];
        };
        size_t length = 0;
    };
    
}