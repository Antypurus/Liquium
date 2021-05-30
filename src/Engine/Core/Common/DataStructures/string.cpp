#include "string.hpp"

#include <stdio.h>

namespace liq
{
	
	uint64 long_string::GetCapacity() const
	{
		uint64 capacity = this->capacity;
		((uint8*)&capacity)[0] <<= 1;
		return capacity;
	}
	
	string::string()
	{
		this->str.short_str.string[0] = 0;
		this->str.short_str.string[sizeof(long_string) - 1] = sizeof(long_string) - 1;
	}
	
	string::string(const string& str)
	{
		
	}
	
	string::string(const char* str)
	{
		
	}
	
	bool string::is_short() const
	{
		// so bit 7 is the flag, this means that for long strings when getting the capacity we must recosntrcut it from the
		// next 7 bits, this can be done by taking this bit and shifting it left by 1
		return (((char*)&this->str)[sizeof(long_string) - 1] && 0b10000000) == 0;
	}
	
}