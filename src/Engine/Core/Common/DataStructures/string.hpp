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
		//copy constructor for long_strings
		long_string(const long_string& str);
		//copy constructor for short strings
		long_string(const short_string& str);
		//move constructor
		long_string(long_string&& str) noexcept;
		//destructor
		~long_string();
		
		long_string& operator=(const long_string& str);
		long_string& operator=(long_string&& str) noexcept;
		long_string& operator=(char* str);
		long_string& operator=(const short_string& str);// TODO(Tiago): 
		template<uint64 strlen> long_string& operator=(const char (&str)[strlen]);// TODO(Tiago): 
				
		bool operator==(const long_string& other) const;
		bool operator==(char* other) const;
		bool operator==(const short_string& other) const;
		
		operator bool() const;
		explicit operator const char*();
		
		char& operator[](uint64 index);
		char at(uint64 index) const;
		
		long_string operator+(const long_string& other) const;
		long_string operator+(char* other) const;
		long_string operator+(const short_string& other) const;
		long_string& operator+=(const long_string& other);
		long_string& operator+=(char* other);
		long_string& operator+=(const short_string& other);
		
		bool IsEmpty() const;
		void SetCapacity(uint64 capacity);
		uint64 GetCapacity() const;
		void ResizeStringBuffer(uint64 capacity);
		
		uint64 ComputeRequiredCapacity(uint64 amount_to_store) const;
		
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
		
		template <uint64 other_length> bool operator==(const char (&other)[other_length]) const
		{
            if (this->string == nullptr && other == nullptr)
                return true; // NOTE(Tiago): special case for the default constructor so as to make the following
                             // comparisons safe.
            if (this->string == nullptr || other == nullptr)
                return false;

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
		
		template<uint64 other_length> long_string operator+(const char (&other)[other_length]) const
		{
			const uint64 combined_size = this->size -1 + other_length;
			const uint64 required_capacity = ComputeRequiredCapacity(combined_size);
			
			long_string ret;
			ret.string = (char*)liq::alloc(required_capacity);
			ret.size = combined_size;
			ret.SetCapacity(required_capacity);
			
			liq::memcpy(this->string, ret.string, this->size - 1);
			liq::memcpy((void*)other, ret.string + this->size -1, other_length);
			
			return ret;
		}
		
		template<uint64 other_length> long_string& operator+=(const char (&other)[other_length])
		{
			const uint64 combined_size = this->size -1 + other_length;
			if(combined_size > this->GetCapacity())
			{
				const uint64 required_capacity = ComputeRequiredCapacity(combined_size);
				this->ResizeStringBuffer(required_capacity);
			}
			liq::memcpy(other, this->string+this->size-1, other_length);
			this->size = combined_size;
			
			return *this;
		}
		
    };
    
    struct short_string
    {
		char string[sizeof(long_string)] = {0};
		
		short_string(char* str);// TODO(Tiago): 
		short_string(const short_string& str);// TODO(Tiago): 
		
		template<uint64 strlen> short_string(const char (&str)[strlen])
		{
			// TODO(Tiago): 
		}
		 
		short_string& operator=(char* other);// TODO(Tiago): 
		short_string& operator=(const short_string& other);// TODO(Tiago): 
		template<uint64 strlen> short_string& operator=(const char (&str)[strlen]);// TODO(Tiago): 
		
		bool operator==(const short_string& other) const;// TODO(Tiago): 
		bool operator==(char* other) const;// TODO(Tiago): 
		bool operator==(const long_string& other) const;// TODO(Tiago): 
		template<uint64 strlen> bool operator==(const char (&other)[strlen]) const;// TODO(Tiago): 
		
		short_string operator+(const short_string& other) const;// TODO(Tiago): 
		short_string operator+(char* other) const;// TODO(Tiago): 
		template<uint64 strlen> short_string operator+(const char (&other)[strlen]) const;// TODO(Tiago): 
		
		short_string& operator+=(const short_string& other);// TODO(Tiago): 
		short_string& operator+=(char* other);// TODO(Tiago): 
		template<uint64 strlen> short_string& operator+=(const char (&other)[strlen]);// TODO(Tiago): 
		
		char& operator[](uint64 index);// TODO(Tiago):
		char at(uint64 index) const;// TODO(Tiago): 
		
		explicit operator char*();// TODO(Tiago): 
		operator bool();// TODO(Tiago): 
		
		uint64 size() const;
    };
	
	struct string
	{
		union string_internal
		{
			long_string long_str = long_string::long_string();
			short_string short_str;
			
			string_internal(){};//TODO(Tiago): need to implement this
			bool is_short() const;
			~string_internal();
		} str;
		
		string();
		string(const string& str);
		string(const char* str);
	};
    
}