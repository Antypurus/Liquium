#pragma once
#include "../types.hpp"
#include "../../../dll.h"

namespace liq
{
    
    struct long_string
    {
		static inline const float64 growth_factor = 1.5;
		
        char* string;
		uint64 size;
		uint64 capacity;
		
		void SetCapacity(uint64 capacity);
		uint64 GetCapacity() const;
		
//		private:
		uint64 ComputeRequiredCapacity(uint64 amount_to_store);
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