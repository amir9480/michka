#include "Core/Thread.h"
#define HAVE_STRUCT_TIMESPEC
#include <Windows.h>

namespace Michka
{
    FORCE_INLINE ThreadBase::ThreadBase()
    {
    }

    FORCE_INLINE ThreadBase::~ThreadBase()
    {
        if (mThread)
        {
            join();
            CloseHandle(mThread);
            mThread = nullptr;
        }
    }

    FORCE_INLINE u64 ThreadBase::id()
    {
        return GetCurrentThreadId();
    }

    FORCE_INLINE void ThreadBase::join()
    {
        if (mThread)
        {
            WaitForSingleObject(mThread, INFINITE);
        }
    }

    FORCE_INLINE void ThreadBase::sleep(u32 _milliseconds)
    {
        Sleep(_milliseconds);
    }

    template<typename ReturnType, typename... ArgumentTypes>
    Thread<ReturnType(ArgumentTypes...)>::Thread(const std::function<ReturnType(ArgumentTypes...)>& _function)
    {
        mFunction = _function;
    }

    template<typename ReturnType, typename... ArgumentTypes>
    Thread<ReturnType(ArgumentTypes...)>::Thread(Thread<ReturnType(ArgumentTypes...)>&& _other)
    {
        *this = std::move(_other);
    }

    template<typename ReturnType, typename... ArgumentTypes>
    DWORD WINAPI threadCaller(LPVOID _lpParam)
    {
        Thread<ReturnType(ArgumentTypes...)>* thread = static_cast<Thread<ReturnType(ArgumentTypes...)>*>(_lpParam);
        thread->call();
        return 0;
    }

    template<typename ReturnType, typename... ArgumentTypes>
    bool Thread<ReturnType(ArgumentTypes...)>::start(ArgumentTypes... _arguments)
    {
        mArguments = std::make_tuple<ArgumentTypes...>(std::forward<ArgumentTypes>(_arguments)...);
        join();

        mThread = CreateThread(
            nullptr,
            0,
            threadCaller<ReturnType, ArgumentTypes...>,
            (void*)this,
            0,
            nullptr
        );

        if (mThread == nullptr) {
            return false;
        }

        return true;
    }

    template<typename ReturnType, typename... ArgumentTypes>
    void Thread<ReturnType(ArgumentTypes...)>::call()
    {
        std::apply(mFunction, mArguments);
    }

    template<typename ReturnType, typename... ArgumentTypes>
    Thread<ReturnType(ArgumentTypes...)>& Thread<ReturnType(ArgumentTypes...)>::operator = (Thread<ReturnType(ArgumentTypes...)>&& _other)
    {
        swap(mFunction, _other.mFunction);
        swap(mThread, _other.mThread);
        mArguments = _other.mArguments;
        return *this;
    }
}
