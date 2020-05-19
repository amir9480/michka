#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "Defines.h"
#include "Helpers.h"

namespace Michka
{
    class MICHKA_API MemoryManager
    {
        MICHKA_SINGLETON_CLASS(MemoryManager)
        FORCE_INLINE MemoryManager();
        FORCE_INLINE ~MemoryManager();
    public:
        FORCE_INLINE void* malloc(size_t _size);
        FORCE_INLINE void* realloc(void* _ptr, size_t _size);
        FORCE_INLINE void free(void* _ptr);
    };

    static MemoryManager& Memory = MemoryManager::instance();
}

#if MICHKA_DEBUG

void* operator new (size_t _size, const char* _filename, u32 _line);
void operator delete (void* _ptr);
void operator delete (void* _ptr, const char* _filename, u32 _line);

void* operator new[] (size_t _size, const char* _filename, u32 _line);
void operator delete[] (void* _ptr);
void operator delete[] (void* _ptr, const char* _filename, u32 _line);

#endif // MICHKA_DEBUG

#include "Memory.inl"

#endif // __MEMORY_H__
