#pragma once

#include "types.hpp"

//TODO(Tiago): for now everything here is placeholder and needs to be substituted by our own allocator, based on windows memory management i guess. ( we might want to have a win_memory, so that we can also have a linux_mem for server side support)
namespace liq
{
	
	void* alloc(uint64 size);
	void* realloc(void* ptr, uint64 new_size);
	void free(void* ptr);
	
	void memcpy(void* source, void* dest, uint64 amount_to_copy, uint64 offset = 0);
	
}