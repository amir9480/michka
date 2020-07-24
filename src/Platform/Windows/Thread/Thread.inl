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

#include "Core/Thread/Thread.h"
#define HAVE_STRUCT_TIMESPEC
#include <Windows.h>

namespace Michka
{
    namespace Private
    {
        FORCE_INLINE DWORD WINAPI threadRunner(LPVOID _lpParam)
        {
            Thread* thread = static_cast<Thread*>(_lpParam);
            Thread::runThread(thread);
            return 0;
        }
    }

    FORCE_INLINE Thread::Thread()
    {
    }

    FORCE_INLINE Thread::Thread(Thread&& _other)
    {
        *this = std::move(_other);
    }

    FORCE_INLINE Thread::~Thread()
    {
        if (mThread)
        {
            join(); // @NOCOVERAGE
        }
    }

    FORCE_INLINE Thread* Thread::getCurrent()
    {
        MutexLock lock(allThreadsMutex);
        if (allThreads.hasKey(getCurrentId()))
        {
            return allThreads[getCurrentId()];
        }
        return nullptr; // @NOCOVERAGE
    }

    FORCE_INLINE u64 Thread::getCurrentId()
    {
        return GetCurrentThreadId();
    }

    FORCE_INLINE u64 Thread::getId() const
    {
        if (mThread)
        {
            return GetThreadId(mThread);
        }
        return 0;
    }

    FORCE_INLINE bool Thread::isRunning() const
    {
        return mIsRunning;
    }

    FORCE_INLINE void Thread::join()
    {
        if (mThread)
        {
            WaitForSingleObject(mThread, INFINITE);
            if (allThreadsMutex.lock())
            {
                allThreads.remove(getId());
                allThreadsMutex.unlock();
            }
            CloseHandle(mThread);
            mThread = nullptr;
        }
    }

    FORCE_INLINE void Thread::runThread(Thread* _thread)
    {
        _thread->mIsRunning = true;
        _thread->run();
        _thread->mIsRunning = false;
    }

    FORCE_INLINE bool Thread::start()
    {
        join();

        mThread = CreateThread(
            nullptr,
            0,
            Private::threadRunner,
            (void*)this,
            0,
            nullptr
        );

        if (mThread == nullptr)
        {
            return false; // @NOCOVERAGE
        }

        if (allThreadsMutex.lock())
        {
            allThreads.insert(getId(), this);
            allThreadsMutex.unlock();
        }

        return true;
    }

    FORCE_INLINE void Thread::sleep(u32 _milliseconds)
    {
        Sleep(_milliseconds);
    }

    FORCE_INLINE Thread& Thread::operator = (Thread&& _other)
    {
        join();
        if (allThreadsMutex.lock())
        {
            mThread = _other.mThread;
            _other.mThread = nullptr;
            allThreads[getId()] = this;
            allThreadsMutex.unlock();
        }

        return *this;
    }

    template<typename ReturnType, typename... ArgumentTypes>
    CallbackThread<ReturnType(ArgumentTypes...)>::CallbackThread(const std::function<ReturnType(ArgumentTypes...)>& _function)
    {
        mFunction = _function;
    }

    template<typename ReturnType, typename... ArgumentTypes>
    CallbackThread<ReturnType(ArgumentTypes...)>::CallbackThread(CallbackThread<ReturnType(ArgumentTypes...)>&& _other)
    {
        *this = std::move(_other);
    }

    template<typename ReturnType, typename... ArgumentTypes>
    void CallbackThread<ReturnType(ArgumentTypes...)>::run()
    {
        if (mFunction)
        {
            std::apply(mFunction, mArguments);
        }
    }

    template<typename ReturnType, typename... ArgumentTypes>
    bool CallbackThread<ReturnType(ArgumentTypes...)>::start(ArgumentTypes... _arguments)
    {
        join();
        mArguments = std::make_tuple<ArgumentTypes...>(std::forward<ArgumentTypes>(_arguments)...);

        return Thread::start();
    }

    template<typename ReturnType, typename... ArgumentTypes>
    CallbackThread<ReturnType(ArgumentTypes...)>& CallbackThread<ReturnType(ArgumentTypes...)>::operator = (CallbackThread<ReturnType(ArgumentTypes...)>&& _other)
    {
        join();
        mFunction = std::move(_other.mFunction);
        mArguments = std::move(_other.mArguments);
        Thread::operator=(std::move(_other));
        return *this;
    }
}
