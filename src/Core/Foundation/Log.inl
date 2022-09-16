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

#include "Michka/Core/Foundation/Log.h"
#include "Michka/Platform/Utility.h"
#include "Michka/Core/Thread/Thread.h"
#include <ctime>

namespace Michka
{
    FORCE_INLINE Log::Log()
    {
        mFile.open("michka.log", File::OpenMode::writeOnly);
        mFile.write("+--------------------------------------------------------------------------------+\n");
        mFile.write("|           .___  ___.  __    ______  __    __   __  ___      ___                |\n");
        mFile.write("|           |   \\/   | |  |  /      ||  |  |  | |  |/  /     /   \\               |\n");
        mFile.write("|           |  \\  /  | |  | |  ,----'|  |__|  | |  '  /     /  ^  \\              |\n");
        mFile.write("|           |  |\\/|  | |  | |  |     |   __   | |    <     /  /_\\  \\             |\n");
        mFile.write("|           |  |  |  | |  | |  `----.|  |  |  | |  .  \\   /  _____  \\            |\n");
        mFile.write("|           |__|  |__| |__|  \\______||__|  |__| |__|\\__\\ /__/     \\__\\           |\n");
        mFile.write("+--------------------------------------------------------------------------------+\n\n");
    }

    FORCE_INLINE Log::~Log()
    {
        mFile.write("\n+------------------------------------ Michka ------------------------------------+\n");
        mFile.close();
    }

    FORCE_INLINE void Log::abort(const char* _message, const char* _file, const u32& _line)
    {
        instance().add(Log::Level::critical, _message, _file, _line);
        Platform::messageBox(_message, "Error");
        throw Exception(_message);
    }

    FORCE_INLINE void Log::abort(const String& _message, const String& _file, const u32& _line)
    {
        instance().add(Log::Level::critical, _message, _file, _line);
        Platform::messageBox(_message, "Error");
        throw Exception(_message.toUtf8().cstr());
    }

    FORCE_INLINE void Log::add(const Log::Level& _level, const char* _message, const char* _file, const u32& _line)
    {
        static char* levels[] = {"Debug", "Info", "Warning", "Error", "Critical"};

        mMutex.lock();

        switch (_level)
        {
        case Log::Level::debug:
            Platform::setConsoleColor(Platform::ConsoleColor::white);
            break;
        case Log::Level::info:
            Platform::setConsoleColor(Platform::ConsoleColor::cyan);
            break;
        case Log::Level::warning:
            Platform::setConsoleColor(Platform::ConsoleColor::yellow);
            break;
        case Log::Level::error:
            Platform::setConsoleColor(Platform::ConsoleColor::red);
            break;
        case Log::Level::critical:
            Platform::setConsoleColor(Platform::ConsoleColor::black, Platform::ConsoleColor::red);
            break;
        }

        char message[8192];

        if (_file && _line)
        {
            char fileName[1024];
            strcpy(fileName, _file);
            u64 fileNameSize = strlen(fileName);
            for (u64 i = 0; i < fileNameSize; i++)
            {
                if (fileName[i] == '\\')
                {
                    fileName[i] = '/';
                }
            }

            if (MICHKA_DEBUG == false && strstr(fileName, MICHKA_SRC_PATH) != 0)
            {
                strncpy(fileName, fileName + strlen(MICHKA_SRC_PATH) + 1, strlen(fileName) - strlen(MICHKA_SRC_PATH)); // @NOCOVERAGE
            }

            sprintf(
                message,
                "[%02d:%02d:%02d.%03d] [%s]: %s  (%s:%d) {%llu}\n",
                clock()/3600000,
                (clock()/60000)%60,
                (clock()/1000)%60,
                clock()%1000,
                levels[(int)_level],
                _message,
                fileName,
                _line,
                Thread::getCurrentId()
            );
        }
        else
        {
            sprintf(
                message,
                "[%02d:%02d:%02d.%03d] [%s]: %s  {%llu}\n",
                clock()/3600000,
                (clock()/60000)%60,
                (clock()/1000)%60,
                clock()%1000,
                levels[(int)_level],
                _message,
                Thread::getCurrentId()
            );
        }
        printf(message);
        mFile.write(message);
        mFile.flush();

        Platform::setConsoleColor(Platform::ConsoleColor::white);
        mMutex.unlock();
    }

    FORCE_INLINE void Log::add(const Level& _level, const String& _message, const String& _file, const u32& _line)
    {
        if (_file.isNotEmpty())
        {
            return add(_level, _message.toUtf8().cstr(), _file.toUtf8().cstr(), _line);
        }
        else
        {
            return add(_level, _message.toUtf8().cstr(), nullptr, _line);
        }
    }

    FORCE_INLINE void Log::critical(const char* _message, const char* _file, const u32& _line)
    {
        instance().add(Log::Level::critical, _message, _file, _line);
    }

    FORCE_INLINE void Log::critical(const String& _message, const String& _file, const u32& _line)
    {
        instance().add(Log::Level::critical, _message, _file, _line);
    }

    FORCE_INLINE void Log::debug(const char* _message, const char* _file, const u32& _line)
    {
        instance().add(Log::Level::debug, _message, _file, _line);
    }

    FORCE_INLINE void Log::debug(const String& _message, const String& _file, const u32& _line)
    {
        instance().add(Log::Level::debug, _message, _file, _line);
    }

    FORCE_INLINE void Log::error(const char* _message, const char* _file, const u32& _line)
    {
        instance().add(Log::Level::error, _message, _file, _line);
    }

    FORCE_INLINE void Log::error(const String& _message, const String& _file, const u32& _line)
    {
        instance().add(Log::Level::error, _message, _file, _line);
    }

    FORCE_INLINE void Log::info(const char* _message, const char* _file, const u32& _line)
    {
        instance().add(Log::Level::info, _message, _file, _line);
    }

    FORCE_INLINE void Log::info(const String& _message, const String& _file, const u32& _line)
    {
        instance().add(Log::Level::info, _message, _file, _line);
    }

    FORCE_INLINE void Log::raw(const char* _message, const bool& _display)
    {
        Platform::setConsoleColor(Platform::ConsoleColor::white);
        mFile.write(_message);
        mFile.write("\n");
        mFile.flush();

        if (_display)
        {
            printf(_message);
            printf("\n");
        }
    }

    FORCE_INLINE void Log::raw(const String& _message, const bool& _display)
    {
        raw(_message.toUtf8().cstr(), _display);
    }

    FORCE_INLINE void Log::warning(const char* _message, const char* _file, const u32& _line)
    {
        instance().add(Log::Level::warning, _message, _file, _line);
    }

    FORCE_INLINE void Log::warning(const String& _message, const String& _file, const u32& _line)
    {
        instance().add(Log::Level::warning, _message, _file, _line);
    }
}
