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

#ifndef __MUTEX_H__
#define __MUTEX_H__

#include "Core/Helpers.h"
#include "MichkaGenerated/Core/Thread/Mutex.generated.h"

namespace Michka
{
    class MICHKA_API Mutex
    {
        MICHKA_CLASS();
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
        MICHKA_NON_COPYABLE_CLASS(MutexLock);
    public:
        explicit MutexLock(Mutex& _mutex);
        ~MutexLock();

    protected:
        Mutex& mMutex;
    };
}


#endif // __MUTEX_H__
