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

#ifndef __LOG_H__
#define __LOG_H__

#include "Core/Defines.h"
#include "Core/Helpers.h"
#include "Core/Exception/Exception.h"
#include "Core/Foundation/File.h"
#include "Core/Thread/Mutex.h"
#include "Core/Reflection/ReflectionClass.h"

#define MICHKA_ABORT(_MESSAGE) \
{ \
    Michka::Log::abort(_MESSAGE, __FILE__, __LINE__); \
}

#define MICHKA_ASSERT(_CONDITION, _MESSAGE) \
if (! (_CONDITION)) \
{ \
    Michka::Log::abort(_MESSAGE, __FILE__, __LINE__); \
}

#define MICHKA_LOG(_MESSAGE) \
{ \
    Michka::Log::debug(_MESSAGE, __FILE__, __LINE__); \
}

#define MICHKA_INFO(_MESSAGE) \
{ \
    Michka::Log::info(_MESSAGE, __FILE__, __LINE__); \
}

#define MICHKA_WARNING(_MESSAGE) \
{ \
    Michka::Log::warning(_MESSAGE, __FILE__, __LINE__); \
}

#define MICHKA_ERROR(_MESSAGE) \
{ \
    Michka::Log::error(_MESSAGE, __FILE__, __LINE__); \
}

#define MICHKA_CRITICAL(_MESSAGE) \
{ \
    Michka::Log::critical(_MESSAGE, __FILE__, __LINE__); \
}

namespace Michka
{
    class MICHKA_API Log
    {
        MICHKA_CLASS(Log);
        MICHKA_SINGLETON_CLASS(Log);
        FORCE_INLINE Log();
        FORCE_INLINE ~Log();
    public:
        enum class Level
        {
            debug,
            info,
            warning,
            error,
            critical
        };
    public:

        /**
         * @brief Log an error message and close program.
         *
         * @param _message
         * @param _file
         * @param _line
         */
        FORCE_INLINE static void abort(const char* _message, const char* _file = nullptr, const u32& _line = 0);
        FORCE_INLINE static void abort(const String& _message, const String& _file = String(), const u32& _line = 0);

        /**
         * @brief Add record to log.
         *
         * @param _level
         * @param _message
         * @param _file
         * @param _line
         */
        FORCE_INLINE void add(const Level& _level, const char* _message, const char* _file = nullptr, const u32& _line = 0);
        FORCE_INLINE void add(const Level& _level, const String& _message, const String& _file = String(), const u32& _line = 0);

        /**
         * @brief Add critical message to log.
         *
         * @param _level
         * @param _message
         * @param _file
         * @param _line
         */
        FORCE_INLINE static void critical(const char* _message, const char* _file = nullptr, const u32& _line = 0);
        FORCE_INLINE static void critical(const String& _message, const String& _file = String(), const u32& _line = 0);

        /**
         * @brief Add debug message to log.
         *
         * @param _level
         * @param _message
         * @param _file
         * @param _line
         */
        FORCE_INLINE static void debug(const char* _message, const char* _file = nullptr, const u32& _line = 0);
        FORCE_INLINE static void debug(const String& _message, const String& _file = String(), const u32& _line = 0);

        /**
         * @brief Add error message to log.
         *
         * @param _level
         * @param _message
         * @param _file
         * @param _line
         */
        FORCE_INLINE static void error(const char* _message, const char* _file = nullptr, const u32& _line = 0);
        FORCE_INLINE static void error(const String& _message, const String& _file = String(), const u32& _line = 0);

        /**
         * @brief Add info message to log.
         *
         * @param _level
         * @param _message
         * @param _file
         * @param _line
         */
        FORCE_INLINE static void info(const char* _message, const char* _file = nullptr, const u32& _line = 0);
        FORCE_INLINE static void info(const String& _message, const String& _file = String(), const u32& _line = 0);

        /**
         * @brief Add a raw message to log without extra informations.
         *
         * @param _message
         * @param _display
         */
        FORCE_INLINE void raw(const char* _message, const bool& _display = true);
        FORCE_INLINE void raw(const String& _message, const bool& _display = true);

        /**
         * @brief Add warning message to log.
         *
         * @param _level
         * @param _message
         * @param _file
         * @param _line
         */
        FORCE_INLINE static void warning(const char* _message, const char* _file = nullptr, const u32& _line = 0);
        FORCE_INLINE static void warning(const String& _message, const String& _file = String(), const u32& _line = 0);

    protected:
        Mutex mMutex;
        File mFile;
    };
}

#include "Log.inl"

#endif // __LOG_H__
