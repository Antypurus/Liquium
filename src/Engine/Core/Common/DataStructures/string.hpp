#pragma once
#include "../types.hpp"
#include "../../../dll.h"

namespace liq
{
    
	static constexpr uint64 string_len(const char* str);
	
	// TODO(Tiago): Implement default constructor
	// TODO(Tiago): Implement string literal constructor
	// TODO(Tiago): Implement non-literal string constructor
	// TODO(Tiago): Implement copy constructor
	// TODO(Tiago): Implement move constructor
    struct long_string
    {
		static inline const float64 growth_factor = 1.5;
		
        char* string = nullptr;
		uint64 size = 0;
		uint64 capacity = 0;
		
		long_string() = default;// NOTE(Tiago): There is no such thing as a default constructore because we need to set the flag.
		long_string(const char* str);
		long_string(const long_string& str);
		~long_string() = default;
		
		void SetCapacity(uint64 capacity);
		uint64 GetCapacity() const;
		
//		private:
		uint64 ComputeRequiredCapacity(uint64 amount_to_store);
    };
    
    struct short_string
    {
		char string[sizeof(long_string)] = {0};
    };
	
	struct string
	{
		union string_internal
		{
			long_string long_str = long_string::long_string();
			short_string short_str;
		} str;
		
		string();
		string(const string& str);
		string(const char* str);
		
		bool is_short() const;
	};
    
}