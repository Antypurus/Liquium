#include "string.hpp"

#include <cmath>
#include "../Math.hpp"

namespace liq
{
	
	static constexpr uint64 string_len(const char* str)
	{
		uint64 len = 1;
		while(*str != 0)
		{
			len++;
			str++;
		}
		return len;
	}
	
	long_string::long_string(const char*)
	{
		
	}
	
	void long_string::SetCapacity(uint64 capacity)
	{
		//capacity must be even, if its uneven we must even it up so that we have the desired capcity at the bare minimum.
		if(capacity % 2 != 0)
		{
			capacity++;
		}
		
		uint64 resulting_capacity = capacity;
		((uint8*)&resulting_capacity)[0] >>= 1;
		((uint8*)&resulting_capacity)[0] |= 0b10000000;
		
		this->capacity = resulting_capacity;
	}
	
	uint64 long_string::GetCapacity() const
	{
		uint64 capacity = this->capacity;
		((uint8*)&capacity)[0] <<= 1;
		return capacity;
	}
	
	uint64 long_string::ComputeRequiredCapacity(uint64 amount_to_store)
	{
		return (uint64)std::ceil(std::pow(growth_factor, std::ceil(log(growth_factor, (float64)amount_to_store))));
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