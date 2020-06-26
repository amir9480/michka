#ifndef __MUTEX_H__
#define __MUTEX_H__

#include "../Defines.h"

namespace Michka
{
    class MICHKA_API Mutex
    {
    public:
        Mutex();
        virtual ~Mutex();

    protected:
        void* mMutex = nullptr;
    };
}


#endif // __MUTEX_H__
