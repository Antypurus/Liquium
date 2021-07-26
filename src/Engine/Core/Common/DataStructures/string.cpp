#include "string.hpp"

#include <cmath>
#include <stdio.h>

#include "../Math.hpp"

namespace liq
{
	
	constexpr uint64 string_len(const char* str)
	{
		uint64 len = 1;
		while(*str != 0)
		{
			len++;
			str++;
		}
		return len;
	}
	
	long_string::long_string()
		:string(nullptr),size(0)
	{
		this->SetCapacity(0);
	}
	
	long_string::long_string(char* str)
		:size(string_len(str))
	{
		OutputDebugString("regular c-string constructor\n");
		
		const uint64 required_capacity = ComputeRequiredCapacity(this->size);
		this->SetCapacity(required_capacity);
		
		this->string = (char*)liq::alloc(required_capacity);
		liq::memcpy((void*)str, (void*)this->string, this->size);
	}
	
	long_string::long_string(const long_string& str)
	{
		OutputDebugString("copy constructor\n");
		this->size = str.size;
		this->capacity = str.capacity;
		
		uint64 required_capacity = this->GetCapacity();
		
		this->string = (char*)liq::alloc(required_capacity);
		liq::memcpy(str.string, this->string, this->size);
	}
	
	long_string::long_string(long_string&& str) noexcept
	{
		OutputDebugString("move constructor\n");
		
		this->size = str.size;
		this->capacity = str.capacity;
		this->string = str.string;
		
		str.string = nullptr;
		str.capacity = 0;
		str.size = 0;
	}
	
	long_string::~long_string()
	{
		this->size = 0;
		this->capacity = 0;
		if(this->string != nullptr)
		{
			liq::free((void*)this->string);
		}
	}
	
	void long_string::SetCapacity(uint64 p_capacity)
	{
		//capacity must be even, if its uneven we must even it up so that we have the desired capcity at the bare minimum.
		if(p_capacity % 2 != 0)
		{
			// TODO(Tiago): check for potential overflow. Realistically it should never happen with a 63bit value, but its prolly better to be safe than sorry.
			p_capacity++;
		}
		
		uint64 resulting_capacity = p_capacity >> 1;
		((uint8*)&resulting_capacity)[7] |= 0b10000000;
		
		this->capacity = resulting_capacity;
	}
	
	// TODO(Tiago): the flag bit has to be stored in offset 3, dont be an idiot
	uint64 long_string::GetCapacity() const
	{
		uint64 reconstructed_capacity = this->capacity;
		reconstructed_capacity <<= 1;
		return reconstructed_capacity;
	}
	
	uint64 long_string::ComputeRequiredCapacity(uint64 amount_to_store)
	{
		return (uint64)std::ceil(std::pow(growth_factor, std::ceil(log(growth_factor, (float64)amount_to_store))));
	}
	
	
	string::string_internal::~string_internal()
	{
		if(this->is_short())
		{
			this->short_str.~short_string();
		}
		else
		{
			this->long_str.~long_string();
		}
	}
	
	string::string()
	{
		this->str.short_str.string[0] = 0;
		this->str.short_str.string[sizeof(long_string) - 1] = sizeof(long_string) - 1;
	}
	
	bool string::string_internal::is_short() const
	{
		// so bit 7 is the flag, this means that for long strings when getting the capacity we must recosntrcut it from the
		// next 7 bits, this can be done by taking this bit and shifting it left by 1
		return (((char*)this)[sizeof(long_string) - 1] && 0b10000000) == 0;
	}
	
}