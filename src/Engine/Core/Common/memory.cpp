#include "memory.hpp"

#include <stdlib.h>
#include <string.h>
#include <immintrin.h>

#define _AMD64_
#include <debugapi.h>

namespace liq
{
	
	void* alloc(uint64 size)
	{
		return malloc(size);
	}
	
	void* realloc(void* ptr, uint64 new_size)
	{
		// TODO(Tiago): we might want to have some checks for null here
		return ::realloc(ptr, new_size);
	}
	
	void free(void* ptr)
	{
		// TODO(Tiago): might wanna have some checks for null here
		::free(ptr);
	}
	
	void memcpy(void* source, void* dest, uint64 amount_to_copy, uint64 offset)
	{
		// TODO(Tiago): fix variable sizes to not always be unneedde u64
		if(amount_to_copy >= 32) //256-bit(AVX2) path
		{
			OutputDebugStringA("Using AVX2 Path\n");
			uint64 out_of_alignment_section = amount_to_copy % 32;
			uint64 issuable_loops = (amount_to_copy - out_of_alignment_section)/32;
			for(uint64 i = 0; i < issuable_loops; ++i)
			{
				__m256 buffer = _mm256_load_ps((float*)((char*)source+(i*32)));
				_mm256_store_ps((float*)((char*)dest+(i*32)), buffer);
			}
			source = (char*)source + issuable_loops*32;
			dest = (char*)dest + issuable_loops*32;
			
			if(out_of_alignment_section >= 16)
			{
				amount_to_copy -= issuable_loops * 32;
				out_of_alignment_section = amount_to_copy % 16;
				issuable_loops = (amount_to_copy - out_of_alignment_section)/16;
				for(uint64 i = 0; i < issuable_loops; ++i)
				{
					__m128 buffer = _mm_load_ps((float*)((char*)source+(i*16)));
					_mm_store_ps((float*)((char*)dest+(i*16)), buffer);
				}
				source = (char*)source + issuable_loops*16;
				dest = (char*)dest + issuable_loops*16;
			}
			// TODO(Tiago): add 64-bit & 32-bit special copy blocks
			for(uint64 i = 0; i < out_of_alignment_section; ++i)
			{
				((char*)dest)[i] = ((char*)source)[i];
			}
		}
		else if(amount_to_copy >=16) //128-bit(AVX1) path
		{
			OutputDebugStringA("Using AVX1 Path\n");
			uint64 out_of_alignment_section = amount_to_copy % 16;
			uint64 issuable_loops = (amount_to_copy - out_of_alignment_section)/16;
			for(uint64 i = 0; i < issuable_loops; ++i)
			{
				__m128 buffer = _mm_load_ps((float*)((char*)source+(i*16)));
				_mm_store_ps((float*)((char*)dest+(i*16)), buffer);
			}
			// TODO(Tiago): add 64-bit & 32-bit special copy blocks
			for(uint64 i = 0; i < out_of_alignment_section; ++i)
			{
				((char*)dest + issuable_loops*16)[i] = ((char*)source + issuable_loops*16)[i];
			}
		}
		else if(amount_to_copy >= 8) //64-bit(uint64) path
		{
			OutputDebugStringA("Using 64bit Path\n");
			const uint64 out_of_alignment_section = amount_to_copy % 8;
			const uint64 issuable_loops = (amount_to_copy - out_of_alignment_section)/8;
			for(uint64 i = 0; i < issuable_loops; ++i)
			{
				((uint64*)dest)[i] = ((uint64*)source)[i];
			}
			// TODO(Tiago): add 32-bit copy block before going down to 8-bit copy
			for(uint64 i = 0; i < out_of_alignment_section; ++i)
			{
				((char*)dest + issuable_loops * 8)[i] = ((char*)source + issuable_loops * 8)[i];
			}
		}
		else if(amount_to_copy >= 4) //32-bit(uint32) path
		{
			OutputDebugStringA("Using 32bit Path\n");
			const uint64 out_of_alignment_section = amount_to_copy % 4;
			const uint64 issuable_loops = (amount_to_copy - out_of_alignment_section)/4;
			for(uint64 i = 0; i < issuable_loops; ++i)
			{
				((uint32*)dest)[i] = ((uint32*)source)[i];
			}
			for(uint64 i = 0; i < out_of_alignment_section; ++i)
			{
				((char*)dest+issuable_loops*4)[i] = ((char*)source+issuable_loops*4)[i];
			}
		}
		else // 16-bit and 8-bit simple loop path
		{
			OutputDebugStringA("Using 8bit Path\n");
			for(uint64 i = 0; i < amount_to_copy; ++i)
			{
				((char*)dest)[i] = ((char*)source)[i];
			}
		}
	}
	
}
