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

#ifndef __THREAD_H__
#define __THREAD_H__

#include "Michka/Core/Helpers.h"
#include "Michka/Core/Container/Map.h"
#include "Mutex.h"
#include <tuple>
#include <functional>

namespace Michka
{
    class MICHKA_API Thread
    {
        MICHKA_CLASS();
    public:
        FORCE_INLINE Thread();
        Thread(const Thread& _other) = delete;
        FORCE_INLINE Thread(Thread&& _other);
        virtual ~Thread();

        /**
         * @brief Get current thread instance.
         */
        FORCE_INLINE static Thread* getCurrent();

        /**
         * @brief Get current thread ID.
         */
        FORCE_INLINE static u64 getCurrentId();

        /**
         * @brief Get thread id.
         *
         * @return id
         */
        FORCE_INLINE u64 getId() const;

        /**
         * @brief Check thread running.
         */
        FORCE_INLINE bool isRunning() const;

        /**
         * @brief Join to thread and wait until it finishes.
         */
        FORCE_INLINE void join();

        /**
         * @brief Call thread run function.
         *
         * @param _thread
         */
        FORCE_INLINE static void runThread(Thread* _thread);

        /**
         * @brief Sleep for milliseconds.
         *
         * @param _milliseconds
         */
        FORCE_INLINE static void sleep(u32 _milliseconds);

        /**
         * @brief Start thread.
         *
         * @return false if did not started successfully.
         */
        FORCE_INLINE bool start();

        Thread& operator = (const Thread& _other) = delete;
        FORCE_INLINE Thread& operator = (Thread&& _other);

    protected:
        /**
         * @brief Run thread implementation.
         */
        virtual void run() = 0;

    protected:
        void* mThread = nullptr;
        bool mIsRunning = false;

    private:
        static Map<u64, Thread*> allThreads;
        static Mutex             allThreadsMutex;
    };


    template<typename T>
    class CallbackThread: public Thread {};

    template<typename ReturnType, typename... ArgumentTypes>
    class CallbackThread<ReturnType(ArgumentTypes...)>: public Thread
    {
    public:
        CallbackThread(const std::function<ReturnType(ArgumentTypes...)>& _function);
        CallbackThread(CallbackThread<ReturnType(ArgumentTypes...)>&& _other);

        /**
         * Run function.
         */
        virtual void run() override;

        /**
         * @brief Call function in thread.
         *
         * @param _arguments
         * @return false if did not started successfully.
         */
        bool start(ArgumentTypes... _arguments);

        CallbackThread<ReturnType(ArgumentTypes...)>& operator = (CallbackThread<ReturnType(ArgumentTypes...)>&& _other);

    private:
        std::function<ReturnType(ArgumentTypes...)> mFunction;
        std::tuple<ArgumentTypes...> mArguments;
    };
}

#include "Platform/Thread/Thread.inl"

#endif // __THREAD_H__
