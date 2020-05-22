#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "Defines.h"
#include "Helpers.h"
#include <cstddef>

namespace Michka
{
    class MICHKA_API MemoryManager
    {
        MICHKA_SINGLETON_CLASS(MemoryManager)
        FORCE_INLINE MemoryManager();
        FORCE_INLINE ~MemoryManager();
    public:
        FORCE_INLINE void* malloc(const std::size_t& _size);
        FORCE_INLINE void* realloc(void* _ptr, const std::size_t& _size);
        FORCE_INLINE void free(void* _ptr);
    };

    static MemoryManager& Memory = MemoryManager::instance();
}

#undef new

#if MICHKA_DEBUG

void* operator new (const std::size_t _size, const char* _filename, u32 _line);
void operator delete (void* _ptr) noexcept;
void operator delete (void* _ptr, const char* _filename, u32 _line) noexcept;

void* operator new[] (const std::size_t _size, const char* _filename, u32 _line);
void operator delete[] (void* _ptr) noexcept;
void operator delete[] (void* _ptr, const char* _filename, u32 _line) noexcept;

#endif // MICHKA_DEBUG

#include "Memory.inl"

#undef new
#define new MICHKA_NEW

#endif // __MEMORY_H__
