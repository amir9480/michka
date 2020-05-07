#include "Memory.h"
#include <iostream>

#undef new

#if MICHKA_DEBUG

void* operator new (size_t _size, const char* _filename, u32 _line)
{
    return Michka::Memory.malloc(_size);
}

void operator delete (void* _ptr)
{
    return Michka::Memory.free(_ptr);
}

void operator delete (void* _ptr, const char* _filename, u32 _line)
{
    return Michka::Memory.free(_ptr);
}

void* operator new[] (size_t _size, const char* _filename, u32 _line)
{
    return Michka::Memory.malloc(_size);
}

void operator delete[] (void* _ptr)
{
    return Michka::MemoryManager::instance().free(_ptr);
}

void operator delete[] (void* _ptr, const char* _filename, u32 _line)
{
    return Michka::MemoryManager::instance().free(_ptr);
}

#endif // MICHKA_DEBUG

#define new MICHKA_NEW
