#pragma once
#include "../types.hpp"

namespace liq
{
    
#define SMALL_STRING_OPTIMIZATION_SIZE 56 //NOTE(Tiago) if the whole struct can be packed into 64bytes it will fit into a cache line when using small string optimizations
    
    static union string_internal
    {
        uint8* string = nullptr;
        uint8[SMALL_STRING_OPTIMIZATION_SIZE] small_string = {};
    }
    
    struct string
    {
        uint64 lenght = 0;
        string_internal string;
    }
    
}