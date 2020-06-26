#include "Thread.h"

namespace Michka
{
    Map<u64, Thread*> Thread::allThreads;
    Mutex             Thread::allThreadsMutex;

    void Thread::run()
    {
    }
}
