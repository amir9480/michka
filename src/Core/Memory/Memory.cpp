#include "Memory.h"
#include <iostream>

#undef new

#if MICHKA_DEBUG

void* operator new (const size_t _size, const char* _filename, u32 _line) noexcept
{
    return Michka::Memory.malloc(_size);
}

void operator delete (void* _ptr) noexcept
{
    return Michka::Memory.free(_ptr);
}

void operator delete (void* _ptr, const char* _filename, u32 _line) noexcept
{                                                                               // @NOCOVERAGE
    return Michka::Memory.free(_ptr);                                           // @NOCOVERAGE
}                                                                               // @NOCOVERAGE

void* operator new[] (const size_t _size, const char* _filename, u32 _line) noexcept
{
    return Michka::Memory.malloc(_size);
}

void operator delete[] (void* _ptr) noexcept
{
    return Michka::MemoryManager::instance().free(_ptr);
}

void operator delete[] (void* _ptr, const char* _filename, u32 _line) noexcept
{                                                                               // @NOCOVERAGE
    return Michka::MemoryManager::instance().free(_ptr);                        // @NOCOVERAGE
}                                                                               // @NOCOVERAGE

#define new MICHKA_NEW

#endif // MICHKA_DEBUG
