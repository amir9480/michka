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

#ifndef __PLATFORM_UTILITY_H__
#define __PLATFORM_UTILITY_H__

#include "Core/Defines.h"
#include "Core/Container/String.h"

namespace Michka
{
    namespace Platform
    {
        enum class ConsoleColor
        {
            black,
            blue,
            cyan,
            green,
            magenta,
            red,
            white,
            yellow,
        };

        /**
         * @brief Show a message box.
         *
         * @param _text
         * @param _title
         */
        void FORCE_INLINE messageBox(const String& _text, const String& _title = "Michka Game Engine");

        /**
         * @brief Set the Console text output color object.
         *
         * @param _textColor
         * @param _backgroundColor
         */
        void FORCE_INLINE setConsoleColor(const ConsoleColor& _textColor, const ConsoleColor& _backgroundColor = ConsoleColor::black);
    }
}

#if (MICHKA_PLATFORM == MICHKA_PLATFORM_WIN32)
#include "Platform/Windows/Utility.inl"
#endif

#endif // __PLATFORM_UTILITY_H__
