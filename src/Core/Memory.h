#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "Defines.h"
#include "Helpers.h"

#if MICHKA_DEBUG
#   define MICHKA_NEW new(__FILE__, __LINE__)
#else
#   define MICHKA_NEW new
#endif // MICHKA_DEBUG

namespace Michka
{
    class MICHKA_API MemoryManager
    {
        MICHKA_SINGLETON_CLASS(MemoryManager)
        FORCE_INLINE MemoryManager();
        FORCE_INLINE ~MemoryManager();
    public:
        FORCE_INLINE void* malloc(size_t _size);
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

#define new MICHKA_NEW

#include "Memory.inl"

#endif // __MEMORY_H__
