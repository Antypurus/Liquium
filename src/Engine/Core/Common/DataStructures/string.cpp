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
	
	long_string::long_string(const short_string& str)
	{
		OutputDebugString("constructor from short strign\n");
		this->size = str.size();
		
		const uint64 required_capacity = ComputeRequiredCapacity(this->size);
		this->SetCapacity(required_capacity);
		
		this->string = (char*)liq::alloc(required_capacity);
		liq::memcpy((void*)str.string, this->string, this->size);
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
	
	char& long_string::operator[](uint64 index)
	{
		return this->string[index];
	}
	
	char long_string::at(uint64 index) const
	{
		return this->string[index];
	}

    long_string long_string::operator+(const long_string& other) const
	{
		const uint64 combined_size = this->size -1 + other.size;
		const uint64 required_capacity = ComputeRequiredCapacity(combined_size);
		
		long_string ret;
		ret.string = (char*)liq::alloc(required_capacity);
		ret.size = combined_size;
		ret.SetCapacity(required_capacity);
		
		liq::memcpy(this->string, ret.string, this->size - 1);
		liq::memcpy(other.string, ret.string + this->size -1, other.size);
		
		return ret;
	}
	
	long_string long_string::operator+(char* other) const
	{
		const uint64 other_size = string_len(other);
		const uint64 combined_size = this->size -1 + other_size;
		const uint64 required_capacity = ComputeRequiredCapacity(combined_size);
		
		long_string ret;
		ret.string = (char*)liq::alloc(required_capacity);
		ret.size = combined_size;
		ret.SetCapacity(required_capacity);
		
		liq::memcpy(this->string, ret.string, this->size - 1);
		liq::memcpy(other, ret.string + this->size -1, other_size);
		
		return ret;
	}
	
	long_string long_string::operator+(const short_string& other) const
	{
		const uint64 combined_size = this->size -1 + other.size();
		const uint64 required_capacity = ComputeRequiredCapacity(combined_size);
		
		long_string ret;
		ret.string = (char*)liq::alloc(required_capacity);
		ret.size = combined_size;
		ret.SetCapacity(required_capacity);
		
		liq::memcpy(this->string, ret.string, this->size - 1);
		liq::memcpy((void*)other.string, ret.string + this->size -1, other.size());
		
		return ret;
	}
	
	long_string& long_string::operator+=(const long_string& other)
	{
		// TODO(Tiago): 
		const uint64 combined_size = this->size -1 + other.size;
		if(combined_size > this->GetCapacity())
		{
			const uint64 required_capacity = ComputeRequiredCapacity(combined_size);
			this->ResizeStringBuffer(required_capacity);
		}
		liq::memcpy(other.string, this->string+this->size-1, other.size);
		this->size = combined_size;
		
		return *this;
	}
	
	long_string& long_string::operator+=(char* other)
	{
		const uint64 other_size = string_len(other);
		const uint64 combined_size = this->size -1 + other_size;
		if(combined_size > this->GetCapacity())
		{
			const uint64 required_capacity = ComputeRequiredCapacity(combined_size);
			this->ResizeStringBuffer(required_capacity);
		}
		liq::memcpy(other, this->string+this->size-1, other_size);
		this->size = combined_size;
		
		return *this;
	}
	
	long_string& long_string::operator+=(const short_string& other)
	{
		const uint64 combined_size = this->size -1 + other.size();
		if(combined_size > this->GetCapacity())
		{
			const uint64 required_capacity = ComputeRequiredCapacity(combined_size);
			this->ResizeStringBuffer(required_capacity);
		}
		liq::memcpy((void*)other.string, this->string+this->size-1, other.size());
		this->size = combined_size;
		
		return *this;
	}
	
	long_string& long_string::operator=(const long_string& str)
	{
		this->size = str.size;
		this->capacity = str.capacity;
		
		const uint64 required_capacity = str.GetCapacity();
		this->string = (char*)liq::alloc(required_capacity);
		
		liq::memcpy(str.string, this->string, str.size);
		
		return *this;
	}
	
	long_string& long_string::operator=(long_string&& str) noexcept
	{
		if(&str == this) return *this;
		this->string = str.string;
		this->size = str.size;
		this->capacity = str.capacity;
		
		str.string = nullptr;
		str.size = 0;
		str.capacity = 0;
		
		return *this;
	}
	
	bool long_string::IsEmpty() const
	{
		return this->size == 0;
	}
	
	long_string::operator bool() const
	{
		return this->IsEmpty();
	}
	
	long_string::operator const char*()
	{
		return this->string;
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
	
	bool long_string::operator==(const long_string& other) const
	{
		if(this->string == nullptr && other.string == nullptr) return true;// NOTE(Tiago): special case for the default constructor so as to make the following comparisons safe.
		if(this->string == nullptr || other.string == nullptr) return false;

		if(this->size != other.size) return false;
		if(this->string[0] != other.string[0]) return false;
		if(this->string[this->size - 1] != other.string[other.size - 1]) return false; // NOTE(Tiago): isnt this always the null terminator, meaning we need to check one back from that. Might need to add some extra length checking.
		
		// TODO(Tiago): i can probably vectorize this to check multiple indices at once, then again the compiler might have enough info to that on his own in this case. Need to check disassembly.
		// TODO(Tiago): additionally i should be able to reduce concurrent cache line usage from 4 to 2 for strings that span multiple cache lines. This might lead to less cache line misses as things go in and out of cache due to things outside of this classes responsability.
		for(uint64 i = 0;i < this->size/2; ++i)
		{
			if(this->string[i] != other.string[i]) return false;
			if(this->string[this->size - 1 - i] != other.string[this->size - 1 - i]) return false;
		}
		if(this->size%2!=0)
		{
			const uint64 middle_index = (this->size - 1)/2 + 1;
			if(this->string[middle_index] != other.string[middle_index]) return false;
		}
		
		return true;
	}
	
	bool long_string::operator==(char* other) const
	{
		if (this->string == nullptr && other == nullptr)
			return true; // NOTE(Tiago): special case for the default constructor so as to make the following
		// comparisons safe.
		if (this->string == nullptr || other == nullptr)
			return false;
		
		uint64 other_length = strlen(other);
		
		if (this->size != other_length)
			return false;
		if (this->string[0] != other[0])
			return false;
		if (this->string[this->size - 1] != other[other_length - 1])
			return false; // NOTE(Tiago): isnt this always the null terminator, meaning we need to check one back
		// from that. Might need to add some extra length checking.
		
		// TODO(Tiago): i can probably vectorize this to check multiple indices at once, then again the compiler
		// might have enough info to that on his own in this case. Need to check disassembly.
		// TODO(Tiago): additionally i should be able to reduce concurrent cache line usage from 4 to 2 for strings
		// that span multiple cache lines. This might lead to less cache line misses as things go in and out of
		// cache due to things outside of this classes responsability.
		for (uint64 i = 0; i < this->size / 2; ++i)
		{
			if (this->string[i] != other[i])
				return false;
			if (this->string[this->size - 1 - i] != other[this->size - 1 - i])
				return false;
		}
		if (this->size % 2 != 0)
		{
			const uint64 middle_index = (this->size - 1) / 2 + 1;
			if (this->string[middle_index] != other[middle_index])
				return false;
		}
		
		return true;
	}
	
	bool long_string::operator==(const short_string& other) const
	{
		if (this->string == nullptr)
			return false;
		
		uint64 other_length = other.size();
		
		if (this->size != other_length)
			return false;
		if (this->string[0] != other.string[0])
			return false;
		if (this->string[this->size - 1] != other.string[other_length - 1])
			return false; // NOTE(Tiago): isnt this always the null terminator, meaning we need to check one back
		// from that. Might need to add some extra length checking.
		
		// TODO(Tiago): i can probably vectorize this to check multiple indices at once, then again the compiler
		// might have enough info to that on his own in this case. Need to check disassembly.
		// TODO(Tiago): additionally i should be able to reduce concurrent cache line usage from 4 to 2 for strings
		// that span multiple cache lines. This might lead to less cache line misses as things go in and out of
		// cache due to things outside of this classes responsability.
		for (uint64 i = 0; i < this->size / 2; ++i)
		{
			if (this->string[i] != other.string[i])
				return false;
			if (this->string[this->size - 1 - i] != other.string[this->size - 1 - i])
				return false;
		}
		if (this->size % 2 != 0)
		{
			const uint64 middle_index = (this->size - 1) / 2 + 1;
			if (this->string[middle_index] != other.string[middle_index])
				return false;
		}
		
		return true;
	}

	uint64 long_string::GetCapacity() const
	{
		uint64 reconstructed_capacity = this->capacity;
		reconstructed_capacity <<= 1;
		return reconstructed_capacity;
	}
	
	void long_string::ResizeStringBuffer(uint64 p_capacity)
	{
		char* new_buffer = (char*)liq::alloc(p_capacity);
		if(new_buffer == nullptr)
		{
			// TODO(Tiago): failed to allocate buffer
			printf("failed to allocate");
		}
		liq::memcpy(this->string, new_buffer, this->size);
		
		liq::free(this->string);
		
		this->SetCapacity(p_capacity);
		this->string = new_buffer;
	}
	
	uint64 long_string::ComputeRequiredCapacity(uint64 amount_to_store) const
	{
		return (uint64)std::ceil(std::pow(growth_factor, std::ceil(log(growth_factor, (float64)amount_to_store))));
	}
	
	uint64 short_string::size() const
	{
		return (sizeof(short_string) - this->string[sizeof(short_string) -1]);
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