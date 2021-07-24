#pragma once

#include <Windows.h>

#include "../types.hpp"
#include "../../../dll.h"
#include "../memory.hpp"

namespace liq
{	
	
	struct long_string;
	struct short_string;
	struct string;
	
	// TODO(Tiago): Implement move constructor
	// TODO(Tiago): Implement destructor
	// TODO(Tiago): Implement Assignment operator
	// TODO(Tiago): Implement Move operatorions
	// TODO(Tiago): Implement operator+ (concatenation)
	struct long_string
    {
		static inline const float64 growth_factor = 1.5;
		
        char* string = nullptr;
		uint64 size = 0;
		uint64 capacity = 0;
		
		//default constructor
		long_string();
		//c-string constructor
		long_string(char* str);
		//copy constructor
		long_string(const long_string& str);
		//move constructor
		long_string(long_string&& str) noexcept;
		
		void SetCapacity(uint64 capacity);
		uint64 GetCapacity() const;
		
		uint64 ComputeRequiredCapacity(uint64 amount_to_store);
		
		//string literal constructor
		template<uint64 length> long_string(const char (&str)[length])
			:size(length)
		{
			OutputDebugStringA("string literal constructor\n");
			const uint64 required_capacity = this->ComputeRequiredCapacity(this->size);
			this->SetCapacity(required_capacity);
			
			this->string = (char*)liq::alloc(required_capacity);
			liq::memcpy((void*)str, (void*)this->string, this->size);
		}
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