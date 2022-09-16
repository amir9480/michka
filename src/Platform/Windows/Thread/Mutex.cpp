// ------------------------------------------------------------------------------- //
//                                     Michka                                      //
// ------------------------------------------------------------------------------- //
//                                  MIT License                                    //
//                                                                                 //
// Copyright (c) 2020-2021 amir alizadeh.                                          //
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

#include "Michka/Core/Thread/Mutex.h"
#include "Michka/Core/Exception/Exception.h"
#define HAVE_STRUCT_TIMESPEC
#include <Windows.h>

namespace Michka
{
    Mutex::Mutex()
    {
        mMutex = CreateMutex(
            nullptr,
            false,
            nullptr
        );

        if (mMutex == nullptr)
        {
            throw Exception("Mutex::Mutex : Can not create mutex."); // @NOCOVERAGE
        }
    }

    Mutex::~Mutex()
    {
        CloseHandle(mMutex);
    }

    bool Mutex::lock()
    {
        return WaitForSingleObject(
            mMutex,
            INFINITE
        ) == WAIT_OBJECT_0;
    }

    bool Mutex::unlock()
    {
        return ReleaseMutex(mMutex);
    }

    MutexLock::MutexLock(Mutex& _mutex):
        mMutex(_mutex)
    {
        mMutex.lock();
    }

    MutexLock::~MutexLock()
    {
        mMutex.unlock();
    }
}
