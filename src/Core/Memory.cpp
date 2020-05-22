#include "Memory.h"
#include <iostream>

#undef new

#if MICHKA_DEBUG

void* operator new (const size_t _size, const char* _filename, u32 _line)
{
    return Michka::Memory.malloc(_size);
}

void operator delete (void* _ptr) noexcept
{
    return Michka::Memory.free(_ptr);
}

void operator delete (void* _ptr, const char* _filename, u32 _line) noexcept
{
    return Michka::Memory.free(_ptr);
}

void* operator new[] (const size_t _size, const char* _filename, u32 _line)
{
    return Michka::Memory.malloc(_size);
}

void operator delete[] (void* _ptr) noexcept
{
    return Michka::MemoryManager::instance().free(_ptr);
}

void operator delete[] (void* _ptr, const char* _filename, u32 _line) noexcept
{
    return Michka::MemoryManager::instance().free(_ptr);
}

#define new MICHKA_NEW

#endif // MICHKA_DEBUG
