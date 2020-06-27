#include "Core/Thread/Mutex.h"
#include "Core/Exception/Exception.h"
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
