#ifndef __THREAD_H__
#define __THREAD_H__

#include "Defines.h"
#include <tuple>
#include <functional>

namespace Michka
{
    class MICHKA_API ThreadBase
    {
    public:
        ThreadBase(const ThreadBase& _other) = delete;
        virtual ~ThreadBase();

        /**
         * @brief Get thread id
         *
         * @return id
         */
        FORCE_INLINE static u64 id();

        /**
         * @brief Wait for milliseconds.
         *
         * @param _milliseconds
         */
        FORCE_INLINE static void sleep(u32 _milliseconds);

        /**
         * @brief Join to thread and wait until it finishes.
         */
        FORCE_INLINE void join();

        ThreadBase& operator = (const ThreadBase& _other) = delete;
    protected:
        FORCE_INLINE ThreadBase();
        void* mThread = nullptr;
    };


    template<typename T>
    class Thread: public ThreadBase {};

    template<typename ReturnType, typename... ArgumentTypes>
    class Thread<ReturnType(ArgumentTypes...)>: public ThreadBase
    {
    public:
        Thread(const std::function<ReturnType(ArgumentTypes...)>& _function);
        Thread(Thread<ReturnType(ArgumentTypes...)>&& _other);

        /**
         * @brief Call function in thread.
         *
         * @param _arguments
         * @return false if did not started successfully.
         */
        bool start(ArgumentTypes... _arguments);

        /**
         * @brief Call function
         */
        void call();

        Thread<ReturnType(ArgumentTypes...)>& operator = (Thread<ReturnType(ArgumentTypes...)>&& _other);

    private:
        std::function<ReturnType(ArgumentTypes...)> mFunction;
        std::tuple<ArgumentTypes...> mArguments;
    };
}

#include "Platform/Thread.inl"

#endif // __THREAD_H__
