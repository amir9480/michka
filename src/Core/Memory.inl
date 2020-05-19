#include "Memory.h"
#include <stdlib.h>

namespace Michka
{
    FORCE_INLINE MemoryManager::MemoryManager()
    {
    }

    FORCE_INLINE MemoryManager::~MemoryManager()
    {
    }

    FORCE_INLINE void* MemoryManager::malloc(size_t _size)
    {
        return ::malloc(_size);
    }

    FORCE_INLINE void* MemoryManager::realloc(void* _ptr, size_t _size)
    {
        return ::realloc(_ptr, _size);
    }

    FORCE_INLINE void MemoryManager::free(void* _ptr)
    {
        ::free(_ptr);
    }
}
