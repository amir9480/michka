#include "Core/Thread.h"
#define HAVE_STRUCT_TIMESPEC
// #include <Windows.h>

// namespace Michka
// {
//     FORCE_INLINE ThreadBase::ThreadBase()
//     {
//     }

//     FORCE_INLINE ThreadBase::~ThreadBase()
//     {
//         if (mThread)
//         {
//             join();
//             pthread_t* thread = (pthread_t*)mThread;
//             delete thread;
//         }
//     }

//     FORCE_INLINE u64 ThreadBase::id()
//     {
//         pthread_t o = pthread_self();
//         return u64(o.p);
//     }

//     FORCE_INLINE void ThreadBase::join()
//     {
//         if (mThread)
//         {
//             pthread_t* thread = (pthread_t*)mThread;
//             pthread_join(*thread, nullptr);
//         }
//     }

//     FORCE_INLINE void ThreadBase::sleep(u32 _milliseconds)
//     {
//         // Sleep(_milliseconds);
//     }

//     template<typename ReturnType, typename... ArgumentTypes>
//     Thread<ReturnType(ArgumentTypes...)>::Thread(ReturnType(*_function)(ArgumentTypes...))
//     {
//         mFunction = _function;
//     }

//     template<typename ReturnType, typename... ArgumentTypes>
//     Thread<ReturnType(ArgumentTypes...)>::Thread(Thread<ReturnType(ArgumentTypes...)>&& _other)
//     {
//         *this = std::move(_other);
//     }

//     template<typename ReturnType, typename... ArgumentTypes>
//     bool Thread<ReturnType(ArgumentTypes...)>::start(ArgumentTypes... _arguments)
//     {
//         mArguments = std::make_tuple<ArgumentTypes...>(std::forward<ArgumentTypes>(_arguments)...);
//         join();
//         if (mThread == nullptr) {
//             mThread = new pthread_t;
//         }
//         return pthread_create((pthread_t*)mThread, nullptr, &callStatic, (void*)this) == 0;
//     }

//     template<typename ReturnType, typename... ArgumentTypes>
//     void* Thread<ReturnType(ArgumentTypes...)>::callStatic(void* _thread)
//     {
//         Thread<ReturnType(ArgumentTypes...)>* thread = static_cast<Thread<ReturnType(ArgumentTypes...)>*>(_thread);
//         std::apply(thread->mFunction, thread->mArguments);
//         pthread_exit(0);
//         return nullptr;
//     }

//     template<typename ReturnType, typename... ArgumentTypes>
//     Thread<ReturnType(ArgumentTypes...)>& Thread<ReturnType(ArgumentTypes...)>::operator=(Thread<ReturnType(ArgumentTypes...)>&& _other)
//     {
//         swap(mFunction, _other.mFunction);
//         swap(mThread, _other.mThread);
//         mArguments = _other.mArguments;
//         return *this;
//     }
// }
