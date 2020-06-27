#ifndef __THREAD_H__
#define __THREAD_H__

#include "Core/Defines.h"
#include "Core/Container/Map.h"
#include "Mutex.h"
#include <tuple>
#include <functional>

namespace Michka
{
    class MICHKA_API Thread
    {
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
        FORCE_INLINE u64 getId();

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
        virtual void run();

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

#include "Platform/Thread.inl"

#endif // __THREAD_H__
