#pragma once
#include "../types.hpp"
#include "../../../dll.h"

namespace liq
{
    
    struct long_string
    {
        char* string;
		uint64 size;
		uint64 capacity;
		
		uint64 GetCapacity() const;
    };
    
    struct short_string
    {
		char string[sizeof(long_string)];
    };
	
	struct string
	{
		union string_internal
		{
			long_string long_str;
			short_string short_str;
		} str;
		
		string();
		string(const string& str);
		string(const char* str);
		
		bool is_short() const;
	};
    
}