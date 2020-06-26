#include "Core/Thread/Thread.h"
#define HAVE_STRUCT_TIMESPEC
#include <Windows.h>

namespace Michka
{
    namespace Private
    {
        DWORD WINAPI threadRunner(LPVOID _lpParam)
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
            join();
        }
    }

    FORCE_INLINE u64 Thread::id()
    {
        return GetCurrentThreadId();
    }

    FORCE_INLINE void Thread::join()
    {
        if (mThread)
        {
            WaitForSingleObject(mThread, INFINITE);
            CloseHandle(mThread);
            mThread = nullptr;
        }
    }

    void Thread::run()
    {
    }

    FORCE_INLINE void Thread::runThread(Thread* _thread)
    {
        _thread->run();
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
            return false;
        }

        return true;
    }

    FORCE_INLINE void Thread::sleep(u32 _milliseconds)
    {
        Sleep(_milliseconds);
    }

    Thread& Thread::operator = (Thread&& _other)
    {
        join();
        mThread = _other.mThread;
        _other.mThread = nullptr;

        return *this;
    }

    // template<typename ReturnType, typename... ArgumentTypes>
    // Thread<ReturnType(ArgumentTypes...)>::Thread(const std::function<ReturnType(ArgumentTypes...)>& _function)
    // {
    //     mFunction = _function;
    // }

    // template<typename ReturnType, typename... ArgumentTypes>
    // Thread<ReturnType(ArgumentTypes...)>::Thread(Thread<ReturnType(ArgumentTypes...)>&& _other)
    // {
    //     *this = std::move(_other);
    // }

    // template<typename ReturnType, typename... ArgumentTypes>
    // DWORD WINAPI threadCaller(LPVOID _lpParam)
    // {
    //     Thread<ReturnType(ArgumentTypes...)>* thread = static_cast<Thread<ReturnType(ArgumentTypes...)>*>(_lpParam);
    //     thread->call();
    //     return 0;
    // }

    // template<typename ReturnType, typename... ArgumentTypes>
    // bool Thread<ReturnType(ArgumentTypes...)>::start(ArgumentTypes... _arguments)
    // {
    //     mArguments = std::make_tuple<ArgumentTypes...>(std::forward<ArgumentTypes>(_arguments)...);
    //     join();

    //     mThread = CreateThread(
    //         nullptr,
    //         0,
    //         threadCaller<ReturnType, ArgumentTypes...>,
    //         (void*)this,
    //         0,
    //         nullptr
    //     );

    //     if (mThread == nullptr)
    //     {
    //         return false;
    //     }

    //     return true;
    // }

    // template<typename ReturnType, typename... ArgumentTypes>
    // void Thread<ReturnType(ArgumentTypes...)>::call()
    // {
    //     std::apply(mFunction, mArguments);
    // }

    // template<typename ReturnType, typename... ArgumentTypes>
    // Thread<ReturnType(ArgumentTypes...)>& Thread<ReturnType(ArgumentTypes...)>::operator = (Thread<ReturnType(ArgumentTypes...)>&& _other)
    // {
    //     swap(mFunction, _other.mFunction);
    //     swap(mThread, _other.mThread);
    //     swap(mArguments, _other.mArguments);
    //     return *this;
    // }
}
