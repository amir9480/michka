#ifndef __MUTEX_H__
#define __MUTEX_H__

#include "../Defines.h"

namespace Michka
{
    class MICHKA_API Mutex
    {
    public:
        Mutex();
        ~Mutex();

        /**
         * @brief Lock mutex.
         *
         * @return false if failed.
         */
        bool lock();

        /**
         * @brief Unlock mutex.
         *
         * @return false if failed.
         */
        bool unlock();

    protected:
        void* mMutex = nullptr;
    };

    class MICHKA_API MutexLock
    {
        MICHKA_NON_COPYABLE_CLASS(MutexLock)
    public:
        explicit MutexLock(Mutex& _mutex);
        ~MutexLock();

    protected:
        Mutex& mMutex;
    };
}


#endif // __MUTEX_H__
