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
            throw Exception("Mutex::Mutex : Can not create mutex.");
        }
    }

    Mutex::~Mutex()
    {
        CloseHandle(mMutex);
    }
}
