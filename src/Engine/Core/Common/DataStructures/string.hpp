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
	
	bool strcmp(const char* first, uint64 first_len, const char* second, uint64 second_len);
	
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
		long_string& operator=(const short_string& str); 
		template<uint64 strlen> long_string& operator=(const char (&str)[strlen])
		{
			const uint64 required_capacity = ComputeRequiredCapacity(strlen);
			
			if(this->string != nullptr)
			{
				liq::free(this->string);
			}
			this->string = (char*)liq::alloc(required_capacity);
			liq::memcpy((void*)str.string, this->string, strlen);
			
			this->size = strlen;
			this->SetCapacity(required_capacity);
			
			return *this;
		}
				
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
            return strcmp(this->string, this->size, other, other_length);
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
		
		short_string();
		short_string(char* str);
		short_string(const short_string& str);
		template<uint64 strlen> short_string(const char (&str)[strlen])
		{
			static_assert(strlen <= sizeof(short_string), "Short sttrings must be at most 24 bytes)");
			liq::memcpy(str, this->string, strlen);
			this->SetSize(strlen);
		}
		 
		short_string& operator=(char* other);
		short_string& operator=(const short_string& other);
		template<uint64 strlen> short_string& operator=(const char (&str)[strlen])
		{
			if(this->string == str) return *this;
			static_assert(strlen <= sizeof(short_string), "Short sttrings must be at most 24 bytes)");
			
			liq::memcpy(str, this->string, strlen);
			this->SetSize(strlen);
			
			return *this;
		}
		
		bool operator==(const short_string& other) const;
		bool operator==(char* other) const;
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
		void SetSize(uint64 size);
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