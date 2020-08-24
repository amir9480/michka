// ------------------------------------------------------------------------------- //
//                                     Michka                                      //
// ------------------------------------------------------------------------------- //
//                                  MIT License                                    //
//                                                                                 //
// Copyright (c) 2020-2020 amir alizadeh.                                          //
//                                                                                 //
// Permission is hereby granted, free of charge, to any person obtaining a copy    //
// of this software and associated documentation files (the "Software"), to deal   //
// in the Software without restriction, including without limitation the rights    //
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell       //
// copies of the Software, and to permit persons to whom the Software is           //
// furnished to do so, subject to the following conditions:                        //
//                                                                                 //
// The above copyright notice and this permission notice shall be included in all  //
// copies or substantial portions of the Software.                                 //
//                                                                                 //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      //
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     //
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   //
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   //
// SOFTWARE.                                                                       //
// ------------------------------------------------------------------------------- //

#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "Core/Defines.h"
#include "Core/Helpers.h"
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

#if (MICHKA_DEBUG)

void* operator new (const std::size_t _size, const char* _filename, u32 _line) noexcept;
void operator delete (void* _ptr) noexcept;
void operator delete (void* _ptr, const char* _filename, u32 _line) noexcept;

void* operator new[] (const std::size_t _size, const char* _filename, u32 _line) noexcept;
void operator delete[] (void* _ptr) noexcept;
void operator delete[] (void* _ptr, const char* _filename, u32 _line) noexcept;

#endif // MICHKA_DEBUG

#include "Memory.inl"

#undef new
#define new MICHKA_NEW

#endif // __MEMORY_H__
